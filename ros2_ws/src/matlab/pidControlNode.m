% ========================= PID =========================
% Métricas: Survival time, Episodic return (mesma reward do RL),
%           RMS dos ÂNGULOS (alpha_deg, beta_deg) em janelas de tempo.
% /angles: [alpha_deg, beta_deg] em graus
% /displacements: [dx, dz] em metros (reais, sem escala)

% 1) Create ROS 2 node and comms
node        = ros2node("/pid_control_node");
subDisp     = ros2subscriber(node, "/displacements",    "std_msgs/Float32MultiArray");
subState    = ros2subscriber(node, "/joint_states",     "sensor_msgs/JointState");
subPattern  = ros2subscriber(node, "/pattern_detected", "std_msgs/Bool");
pubTraj     = ros2publisher(node, "/ur5e_controller/joint_trajectory",  "trajectory_msgs/JointTrajectory");
subAngles   = ros2subscriber(node, "/angles",           "std_msgs/Float32MultiArray");

% Prebuild a JointTrajectory message with canonical UR5e joint order
trajMsg = ros2message("trajectory_msgs/JointTrajectory");
trajMsg.joint_names = {'shoulder_pan_joint','shoulder_lift_joint','elbow_joint', ...
                       'wrist_1_joint','wrist_2_joint','wrist_3_joint'};

% 2) Load UR5e rigid body model for Jacobian computation
ur5e = loadrobot('universalUR5e','DataFormat','column');

% 3) PID gains (Cartesian error regulation)
Kp = 4.5 .* [1.0, 1.0, 1.0];
Ki = 0.001.*[1.0, 1.0, 1.0];
Kd = 0.1 .* [1.0, 1.0, 1.0];

% Optional velocity caps (disabled by default)
maxValX = 0.2;   % m/s (vx)
maxValZ = 0.2;   % m/s (vz)

% PID memory
int_x = 0; prev_x = 0;
int_y = 0; prev_y = 0; 
int_z = 0; prev_z = 0;

% Loop timing and Jacobian guard
dt = 0.007;       % ~140 Hz
threshold = 1e-4; % naive singularity guard

fprintf("\n📘 PID Control started\n");

% === RL-like reward parameters (MATCH your RL env exactly) ===
limit_deg  = 5.0;    % ±band in degrees used by the env
alive_in   = 0.3;    % bonus when inside the band
alive_out  = 0.1;    % smaller bonus quando fora da banda
k_reward   = 0.002;  % penalty weight for excess over the band

% Reward accumulators
R_sum      = 0.0;    % episodic return = sum of rewards per step
reward_log = [];     % optional logging
alpha_deg  = 0.0;    % last seen angles (DEGREES)
beta_deg   = 0.0;

% ===== Logs para RMS (agora com ÂNGULOS) =====
t_log     = [];      % [s] relativo ao início
alpha_log = [];      % [deg]
beta_log  = [];      % [deg]
rms_windows = [1 2 5 10 20 40];   % janelas (s)

% Initial state and Cartesian reference (hold current TCP as reference)
Msg = receive(subState);
q = Msg.position;
T = getTransform(ur5e, q, "tool0");
ref = T(1:3,4);

t0 = tic;

while true
    % Stop the episode if the visual pattern is not detected
    patternMsg = receive(subPattern, 2);  % 2 s timeout
    if isempty(patternMsg) || ~patternMsg.data
        disp("🔄 Pattern not detected, stopping control");
        break;
    end

    % === Read latest angles (non-blocking) for reward in DEGREES ===
    angMsg = subAngles.LatestMessage;
    if ~isempty(angMsg) && numel(angMsg.data) >= 2
        alpha_deg = double(angMsg.data(1));  % θx [deg]
        beta_deg  = double(angMsg.data(2));  % θz [deg]
    end

    % ---------- Reward (igual ao Python; aqui u=None) ----------
    r_t = compute_reward(alpha_deg, beta_deg, limit_deg, alive_in, alive_out, k_reward, []);
    R_sum = R_sum + r_t;
    reward_log(end+1,1) = r_t;

    % ===== PID control =====
    dispMsg = receive(subDisp);
    dx_raw = double(dispMsg.data(1));   % [m] deslocamento REAL (sem escala)
    dz_raw = double(dispMsg.data(2));   % [m]

    % ----- LOGS p/ RMS (ÂNGULOS) -----
    t_rel = toc(t0);
    t_log(end+1,1)     = t_rel;
    alpha_log(end+1,1) = alpha_deg;
    beta_log(end+1,1)  = beta_deg;

    % A partir daqui, ESCALA apenas para o controlador (não para métricas)
    dx = 40 * dx_raw;
    dz = 2  * dz_raw;

    % Cartesian error relative to initial reference (forma de controlo)
    T = getTransform(ur5e, q, "tool0");
    err_x = ref(1) - T(1,4) - dz;  % usa dz escalado (só para o PID)
    err_y = ref(2) - T(2,4) + dx;  % usa dx escalado (só para o PID)
    err_z = ref(3) - T(3,4);

    err_norm = norm([err_x, err_y, err_z]);

    fprintf("ex %g ey %g ez %g |e| %g  |  α %.3f° β %.3f°  r_t %.4f\n", ...
            err_x, err_y, err_z, err_norm, alpha_deg, beta_deg, r_t);

    % PID updates
    int_x = int_x + err_x*dt;  der_x = (err_x - prev_x)/dt;  prev_x = err_x;
    int_y = int_y + err_y*dt;  der_y = (err_y - prev_y)/dt;  prev_y = err_y;
    int_z = int_z + err_z*dt;  der_z = (err_z - prev_z)/dt;  prev_z = err_z;

    vx = Kp(1)*err_x + Ki(1)*int_x + Kd(1)*der_x;
    vy = Kp(2)*err_y + Ki(2)*int_y + Kd(2)*der_y;
    vz = Kp(3)*err_z + Ki(3)*int_z + Kd(3)*der_z;

    % Optional caps (disabled)
    % vx = max(min(vx, maxValX), -maxValX);
    % vz = max(min(vz, maxValZ), -maxValZ);

    % Jacobian and guard
    J = geometricJacobian(ur5e, q, 'tool0');  % 6x6
    if abs(det(J)) < threshold
        warning("Jacobian near singularity, skipping correction");
        pause(dt);
        break; 
    end

    % Map Cartesian twist [0 0 0  vx vy vz] to joint velocities
    dq = pinv(J) * [0; 0; 0; vx; vy; vz];

    % Integrate in joint space
    q_new = q + dq*dt;
    q = q_new;

    % Publish as a single-pt JointTrajectory
    pt = ros2message("trajectory_msgs/JointTrajectoryPoint");
    pt.positions = q_new;
    pt.time_from_start.sec = int32(0);
    pt.time_from_start.nanosec = uint32(0);
    trajMsg.points = pt;

    send(pubTraj, trajMsg);

    pause(dt);
end

% ===== Episode results =====
tempo = toc(t0);  % survival time
avg_reward_step = mean(reward_log);

fprintf("✅ PID finished in %.2f s | Return (sum r_t) = %.4f | Avg r/step = %.4f\n", ...
        tempo, R_sum, avg_reward_step);

% ===== RMS dos ÂNGULOS (alpha,beta) em janelas =====
rms_until = @(x,t,limit) sqrt(mean(x(t<limit).^2,'omitnan'));
rms_alpha = arrayfun(@(w) rms_until(alpha_log, t_log, w), rms_windows);   % [deg]
rms_beta  = arrayfun(@(w) rms_until(beta_log,  t_log, w), rms_windows);   % [deg]
rms_tilt  = arrayfun(@(w) sqrt( mean( (alpha_log(t_log<w)).^2 + (beta_log(t_log<w)).^2, 'omitnan' ) ), rms_windows); % magnitude angular [deg]

% imprimir (graus)
fprintf("RMS alpha (deg): "); fprintf("%8.3f", rms_alpha); fprintf("\n");
fprintf("RMS beta  (deg): "); fprintf("%8.3f", rms_beta);  fprintf("\n");
fprintf("RMS |tilt|(deg): "); fprintf("%8.3f", rms_tilt);  fprintf("\n");

% ===== Persist results (usar um ficheiro separado p/ não misturar campos) =====
results_file = "tempos_pid_angles.mat";
res.tempo           = tempo;              % survival time
res.return_sum      = R_sum;              % episodic return (sum of r_t)
res.avg_reward_step = avg_reward_step;    % average per step
res.limit_deg       = limit_deg;          % store params para traceability
res.alive_in        = alive_in;
res.alive_out       = alive_out;
res.k_reward        = k_reward;
res.rms_win_s       = rms_windows;
% RMS Ângulos
res.rms_alpha_deg   = rms_alpha;   % 1xW [deg]
res.rms_beta_deg    = rms_beta;    % 1xW [deg]
res.rms_tilt_deg    = rms_tilt;    % 1xW [deg]
res.timestamp       = datestr(now,'yyyy-mm-dd HH:MM:SS');

if isfile(results_file)
    S = load(results_file, "resultados");
    resultados = S.resultados;
    resultados(end+1) = res; %#ok<AGROW>
else
    resultados = res;
end
save(results_file, "resultados");

% ===== Quick plots (across all recorded episodes) =====
tempos_all  = [resultados.tempo];
returns_all = [resultados.return_sum];

figure; tiledlayout(1,2);
nexttile; plot(tempos_all,'-o','LineWidth',2);
grid on; xlabel('Episode'); ylabel('Time [s]'); title('PID: survival time');
nexttile; plot(returns_all,'-o','LineWidth',2);
grid on; xlabel('Episode'); ylabel('Sum r_t'); title('PID: episodic return');

% =================== Função local: reward (igual ao Python) ===================
function r = compute_reward(alpha_deg, beta_deg, limit_deg, alive_in, alive_out, k_reward, u)
    % excesso acima da banda em cada eixo (0 se dentro)
    alpha_excess = max(0.0, abs(alpha_deg) - limit_deg);
    beta_excess  = max(0.0, abs(beta_deg)  - limit_deg);
    in_interval  = (alpha_excess == 0.0 && beta_excess == 0.0);

    if in_interval
        % bónus extra dentro da banda, 0..0.2
        % normaliza ângulos à banda: 0.0 no centro, 1.0 no limite
        a = abs(alpha_deg) / limit_deg;
        b = abs(beta_deg)  / limit_deg;
        % bónus quadrático, máximo 0.2 no centro, 0.0 no limite
        r_shape = 0.2 * max(0.0, 1.0 - 0.5 * (a*a + b*b));
        r = alive_in + r_shape;  % 0.3 + [0..0.2] → [0.3..0.5]
    else
        % fora da banda: bónus menor - penalização do excesso
        angle_penalty = alpha_excess*alpha_excess + beta_excess*beta_excess;
        r = alive_out - k_reward * angle_penalty;  % p.ex. 0.1 - 0.002*excesso^2
    end

    % penalização de ação (opcional) — igual ao Python se u não for vazio
    if ~isempty(u)
        u = u(:);  % garante vetor coluna
        r = r - 0.05 * (u.' * u);  % 0.05 * ||u||^2
    end

    r = double(r);
end
