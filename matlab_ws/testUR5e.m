% 1) Cria nó e subscreve
node     = ros2node("/pid_control_node");
subDisp  = ros2subscriber(node, "/displacements",    "std_msgs/Float32MultiArray");
subState = ros2subscriber(node, "/joint_states",     "sensor_msgs/JointState");
pubTraj  = ros2publisher(node, "/ur5e_controller/joint_trajectory",  "trajectory_msgs/JointTrajectory");

% 2) Carrega modelo para Jacobiana
ur5e = loadrobot('universalUR5e','DataFormat','column');

% Intervalos para grid-search
Kp_vals = 2:0.5:7;
Ki_vals = 0.01:0.01:0.1;
dx_vals = 15:2:35;

% Parâmetros fixos
Kd        = 0.01 .* [1,1,1];
dz_factor = 2;
dt        = 0.01;    % 100 Hz
threshold = 1e-4;
tol       = 0.5e-4;
csv_file   = 'results.csv';

fid = fopen(csv_file,'w');
fprintf(fid, 'Kp,Ki,dx_factor,time_recognized\n');
fclose(fid);

best_time = 0;
best_cfg  = struct();

% Loop sobre parâmetros
for Kp_v = Kp_vals
  for Ki_v = Ki_vals
    for dx_f = dx_vals

      fprintf('\n--- Teste: Kp=%.2f  Ki=%.2f  dx_f=%.1f ---\n', Kp_v, Ki_v, dx_f);

      % reset da simulação (será disparado pelo Python no teu nó de visão)
      system('ros2 service call /reset_simulation std_srvs/srv/Trigger > /dev/null');
      pause(0.5);

      % configurações PID desta iteração
      Kp = Kp_v .* [1,1,1];
      Ki = Ki_v .* [1,1,1];

      % zera estados do PID
      int_x = 0; prev_x = 0;
      int_y = 0; prev_y = 0;
      int_z = 0; prev_z = 0;

      % lê estado inicial e referência
      msgJS = receive(subState,1.0);
      q     = double(msgJS.position(:));
      T0    = getTransform(ur5e, q, "tool0");
      ref   = T0(1:3,4);

      % início da contagem
      tstart = tic;
      max_test = 20;
      pattern_lost = false;

      % loop principal até pattern lost ou convergência muito rápida
      while toc(tstart) < max_test
        % tenta ler deslocamentos; se vazio → perde pattern
        dmsg = receive(subDisp, 0.5);
        if isempty(dmsg)
          pattern_lost = true;  
          break;
        end


        dx = dx_f * double(dmsg.data(1));
        dz = dz_factor * double(dmsg.data(2));

        % pose atual e erro
        T     = getTransform(ur5e, q, "tool0");
        err_x = ref(1) - T(1,4) + dz;
        err_y = ref(2) - T(2,4) + dx;
        err_z = ref(3) - T(3,4);
        err_norm = norm([err_x; err_y; err_z]);
        if err_norm < tol
          % convergiu muito depressa — ainda conta como tempo até perdre
          break;
        end

        % PID completo
        int_x = int_x + err_x*dt;  der_x = (err_x - prev_x)/dt;  prev_x = err_x;
        int_y = int_y + err_y*dt;  der_y = (err_y - prev_y)/dt;  prev_y = err_y;
        int_z = int_z + err_z*dt;  der_z = (err_z - prev_z)/dt;  prev_z = err_z;
        vx = Kp(1)*err_x + Ki(1)*int_x + Kd(1)*der_x;
        vy = Kp(2)*err_y + Ki(2)*int_y + Kd(2)*der_y;
        vz = Kp(3)*err_z + Ki(3)*int_z + Kd(3)*der_z;

        % Jacobiana → q update
        J  = geometricJacobian(ur5e, q, 'tool0');
        if abs(det(J))<threshold, break; end
        dq = pinv(J)*[0;0;0;vx;vy;vz];
        q  = q + dq*dt;

        % publica comando de trajetória (mantém teu método original)  
        trajMsg = ros2message("trajectory_msgs/JointTrajectory");
        trajMsg.joint_names = {'shoulder_pan_joint','shoulder_lift_joint','elbow_joint', ...
                               'wrist_1_joint','wrist_2_joint','wrist_3_joint'};
        pt = ros2message("trajectory_msgs/JointTrajectoryPoint");
        pt.positions = q;
        pt.time_from_start.sec = int32(0);
        pt.time_from_start.nanosec = uint32(0);
        trajMsg.points = pt;
        send(pubTraj, trajMsg);

        pause(dt);
      end

      % mede duração até pattern lost
      t_elapsed = toc(tstart);
      if pattern_lost
        fprintf('→ padrão perdido em %.2f s\n', t_elapsed);
      else
        fprintf('→ padrão mantido os %.2f s completos\n', max_test);
        t_elapsed = max_test;
      end

      fid = fopen(csv_file,'a');
      fprintf(fid, '%.2f,%.2f,%.1f,%.2f\n', Kp_v, Ki_v, dx_f, t_elapsed);
      fclose(fid);
   
      if t_elapsed > best_time
        best_time = t_elapsed;
        best_cfg  = struct('Kp',Kp_v,'Ki',Ki_v,'dx_f',dx_f,'time',t_elapsed);
      end


      end

    end
end

% resultado final
fprintf('\n*** Melhor configuração encontrada ***\n');
fprintf(' Kp = %.2f\n Ki = %.2f\n dx_factor = %.1f\n Tempo = %.2f s\n', ...
        best_cfg.Kp, best_cfg.Ki, best_cfg.dx_f, best_cfg.time);

fprintf('Todos os resultados em %s\n', csv_file);