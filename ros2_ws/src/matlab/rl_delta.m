function ur_dela
% UR5e, seguimento cartesiano em XY com Z e orientação fixos.
% Requisitos: Robotics System Toolbox + ROS 2 Toolbox.

  % === 1) Nó, publisher e subs ===
  node = ros2node("ur5e_joints_publisher");
  pub  = ros2publisher(node, "/ur5e_controller/joint_trajectory", "trajectory_msgs/JointTrajectory");
  subState = ros2subscriber(node, "/joint_states", "sensor_msgs/JointState");

  % Sniffer opcional para drenar trajetórias no reset
  subTrajSniff = ros2subscriber(node, "/ur5e_controller/joint_trajectory", "trajectory_msgs/JointTrajectory");

  % Ordem canónica das juntas
  jointOrder = {'shoulder_pan_joint','shoulder_lift_joint','elbow_joint', ...
                'wrist_1_joint','wrist_2_joint','wrist_3_joint'};

  % Modelo e IK
  ur5e = loadrobot('universalUR5e','DataFormat','column');
  ik   = inverseKinematics('RigidBodyTree', ur5e);

  % Pesos IK [wx wy wz wroll wpitch wyaw] -> Z e orientação bem rígidos
  weights = [1 1 100 100 100 100];

  % Limites articulares
  [lower, upper] = jointLimits(ur5e);

  % Parâmetros temporais e suavização
  dt          = 0.005;   % 50 Hz
  dq_max_step = 0.06;   % rad/step por junta (0.02–0.06)

  % Debounce do reset
  min_reset_gap = 0.30;         % s
  last_reset_wall = [0 0 0 0 0 0];

  % === 2) Arranque com estado real ===
  q_real   = readQBlocking(subState, jointOrder);
  Tcur     = getTransform(ur5e, q_real, 'tool0');
  Tdesired = Tcur;
  z_hold   = Tcur(3,4);
  R_hold   = Tcur(1:3,1:3);
  accept_cmds = true;

  % Subs de comando e reset (só após Tdesired existir)
  subDelta = ros2subscriber(node, "/rl_delta", "geometry_msgs/Vector3", @deltaCb);
  subReset = ros2subscriber(node, "/rl_reset", "std_msgs/Bool",        @resetCb);

  % Hold inicial
  doHold(pub, jointOrder, q_real, 3, 0.05);

  % === 3) Loop principal ===
  r = rateControl(round(1/dt));
  while true
      % Estado real (tolerante a timeouts)
      q_real = tryReadQ(subState, jointOrder, q_real);

      % Reforço: travar Z e orientação em TODAS as iterações
      Tdesired(3,4)     = z_hold;
      Tdesired(1:3,1:3) = R_hold;

      % IK com semente = estado real
      q_ik = ik('tool0', Tdesired, weights, q_real);

      % Limite de passo articular (o env aplica positions diretamente)
      dq = q_ik - q_real;
      step = dq_max_step;
      for i = 1:numel(dq)
          if dq(i) >  step, dq(i) =  step; end
          if dq(i) < -step, dq(i) = -step; end
      end
      q_cmd = q_real + dq;

      % --- Anti-drift em Z (correção mínima, sem rodar o TCP) ---
      Tchk = getTransform(ur5e, q_cmd, 'tool0');
      ez = z_hold - Tchk(3,4);
      if abs(ez) > 5e-5   % 0.05 mm de tolerância
          Jcmd = geometricJacobian(ur5e, q_cmd, 'tool0');  % 6x6: [omega; v]
          jvz  = Jcmd(6,:);                                % linha da velocidade Z
          % passo mínimo LS para reduzir o erro em Z
          alpha = 0.5;                                     % ganho suave
          dq_fix = (jvz'/(jvz*jvz' + 1e-8)) * (alpha*ez);  % 6x1
          % limitar correção por junta
          for i = 1:numel(dq_fix)
              if dq_fix(i) >  step, dq_fix(i) =  step; end
              if dq_fix(i) < -step, dq_fix(i) = -step; end
          end
          q_cmd = q_cmd + dq_fix;
      end
      % -----------------------------------------------------------

      % Clamp por limites de junta
      q_cmd = max(min(q_cmd, upper), lower);

      % Envia 1 ponto (tempo é ilustrativo para o teu env.py)
      traj = ros2message(pub); traj.joint_names = jointOrder;
      pt = ros2message("trajectory_msgs/JointTrajectoryPoint");
      pt.positions = q_cmd;
      pt.time_from_start.sec     = int32(0);
      pt.time_from_start.nanosec = uint32(dt*1e9);
      traj.points = pt; send(pub, traj);

      waitfor(r);
  end

  % ====== Callbacks ======
  function deltaCb(msg)
      if ~accept_cmds, return, end
      % sanity check (evita NaN/Inf a entrar)
      dx = double(msg.x); dy = double(msg.y);
      if ~isfinite(dx) || ~isfinite(dy), return, end

      d_base = [dx; dy; 0.0];
      Tdesired(1:3,4) = Tdesired(1:3,4) + d_base;
      % reforços
      Tdesired(3,4)     = z_hold;
      Tdesired(1:3,1:3) = R_hold;
  end

  function resetCb(msg)
      if ~msg.data, return, end
      % Debounce: ignora resets demasiado próximos
      if last_reset_wall(1) ~= 0 && etime(clock, last_reset_wall) < min_reset_gap
          return
      end
      last_reset_wall = clock;

      accept_cmds = false;

      % 🧹 Drenar possíveis mensagens antigas ~300 ms
      drainTopic(subDelta,     0.30);
      drainTopic(subTrajSniff, 0.30);

      % Reancorar a estado real
      q_real   = readQBlocking(subState, jointOrder);
      Tcur     = getTransform(ur5e, q_real, 'tool0');
      Tdesired = Tcur;
      z_hold   = Tcur(3,4);
      R_hold   = Tcur(1:3,1:3);

      % Hold curto para assentar controlador
      doHold(pub, jointOrder, q_real, 3, 0.05);

      accept_cmds = true;
  end
end  % fim da função principal

% ====== Utilitários ======
function q = readQBlocking(subState, jointOrder)
    fprintf("A aguardar /joint_states do simulador");
    while true
        try, msg = receive(subState, 0.5); catch, msg = []; end
        if ~isempty(msg), break, end
        fprintf(".");
    end
    fprintf(" ok\n");
    q = reorderQ(msg, jointOrder);
end

function q = tryReadQ(subState, jointOrder, q_fallback)
    try
        msg = receive(subState, 0.05);
        if isempty(msg), q = q_fallback; return, end
        q = reorderQ(msg, jointOrder);
    catch
        q = q_fallback;
    end
end

function q = reorderQ(msg, jointOrder)
    names = cellstr(msg.name);
    q = zeros(6,1);
    for i = 1:6
        idx = find(strcmp(names, jointOrder{i}), 1);
        if isempty(idx)
            error("Junta %s não encontrada em /joint_states", jointOrder{i});
        end
        q(i) = double(msg.position(idx));
    end
end

function [lower, upper] = jointLimits(robot)
    bodies = robot.Bodies; lower = []; upper = [];
    for i = 1:numel(bodies)
        j = bodies{i}.Joint;
        if strcmp(j.Type, "fixed"), continue, end
        lim = j.PositionLimits; if isempty(lim), lim = [-inf, inf]; end
        lower(end+1,1) = lim(1); %#ok<AGROW>
        upper(end+1,1) = lim(2); %#ok<AGROW>
    end
end

function doHold(pub, jointOrder, q_hold, n, dt)
    for k = 1:n
        msg = ros2message(pub); msg.joint_names = jointOrder;
        pt = ros2message("trajectory_msgs/JointTrajectoryPoint");
        pt.positions = q_hold;
        pt.time_from_start.sec     = int32(0);
        pt.time_from_start.nanosec = uint32(5e7); % 50 ms
        msg.points = pt; send(pub, msg); pause(dt);
    end
end

function drainTopic(sub, duration)
    t0 = tic; n=0;
    while toc(t0) < duration
        try
            m = receive(sub, 0.01);
            if ~isempty(m), n = n+1; end
        catch
        end
    end
    fprintf("🧹 Drenadas %d mensagens de %s\n", n, class(sub));
end
