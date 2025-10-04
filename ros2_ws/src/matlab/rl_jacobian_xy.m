function ur5e_publish_joints
  % 1) Cria nó e publisher de trajectória
  node = ros2node("ur5e_joints_publisher");
  pub  = ros2publisher(node, ...
        "/ur5e_controller/joint_trajectory", ...
        "trajectory_msgs/JointTrajectory");

  % 2) Estado inicial e robot para Jacobiana
  ur5e = loadrobot('universalUR5e','DataFormat','column');
  q0   = [0; -1.745; -2.27; 0.93; 1.53; 0.0];
  dt   = 0.1;               % tempo entre comandos (s)
  lambda = 0.01;            % amortecimento para DLS

  % 3) Variáveis globais de estabilização
  ignore_deltas = false;
  steps_since_reset = 0;
  has_reset_stabilized = false;

  % 4) Subscreve os tópicos
  subDelta = ros2subscriber(node, "/rl_delta", "geometry_msgs/Vector3", @deltaCb);
  subReset = ros2subscriber(node, "/rl_reset", "std_msgs/Bool", @resetCb);
  subStab  = ros2subscriber(node, "/rl_stabilized", "std_msgs/Bool", @stabilizedCb);
  subState = ros2subscriber(node, "/joint_states", "sensor_msgs/JointState");

  % 5) Variáveis persistentes
  persistent qLast

  disp("*** MATLAB: nó pronto, à espera de /rl_delta, /rl_reset e /rl_stabilized ***");

  while true
    pause(0.1);
  end

  % ---- Callback do reset ----
  function resetCb(msg)
    if msg.data
      disp(">>> Reset recebido — estado reinicializado.");
      clear deltaCb
      disp("[CONFIRMAÇÃO] Variáveis persistentes apagadas.");

      ignore_deltas = true;
      steps_since_reset = 0;
      has_reset_stabilized = false;

      qLast = [];
    end
  end

  % ---- Callback do stabilized ----
  function stabilizedCb(msg)
    if msg.data
      ignore_deltas = false;
      has_reset_stabilized = true;

      % Espera até o /joint_states tiver uma mensagem válida
      tries = 0;
      while isempty(subState.LatestMessage) && tries < 10
        pause(0.1);
        tries = tries + 1;
      end

      if isempty(subState.LatestMessage)
        warning("Não foi possível obter /joint_states após estabilização.");
        return;
      end

      q_now = subState.LatestMessage.position;
      qLast = q_now(:);

      disp("[MATLAB] Estabilização concluída — comandos RL reativados.");
      disp("q_now = "); disp(q_now');
    end
  end

  % ---- Callback do delta ----
  function deltaCb(msg)
    if ignore_deltas || ~has_reset_stabilized || isempty(qLast)
      steps_since_reset = steps_since_reset + 1;
      disp("[MATLAB] Estabilização ativa ou qLast não definido — q = q0. Passo " + steps_since_reset);

      traj = ros2message(pub);
      traj.joint_names = {
          'shoulder_pan_joint','shoulder_lift_joint','elbow_joint', ...
          'wrist_1_joint','wrist_2_joint','wrist_3_joint'};
      pt = ros2message("trajectory_msgs/JointTrajectoryPoint");
      pt.positions = q0;
      pt.time_from_start.sec = int32(0);
      pt.time_from_start.nanosec = uint32(5e8);
      traj.points = pt;
      send(pub, traj);
      return;
    end

    % velocidades recebidas no frame da base
    v_tcp = [msg.x; msg.y; msg.z];
    disp(">>> velocidades recebidas: " + mat2str(v_tcp'));

    % Jacobiana geométrica no TCP
    J = geometricJacobian(ur5e, qLast, 'tool0');
    Jv = J(4:6,:); % parte linear

    % Cálculo de qdot usando Damped Least Squares
    qdot = Jv' * ((Jv*Jv' + (lambda^2)*eye(3)) \ v_tcp);

    % Integração para obter nova posição
    qSol = qLast + qdot * dt;

    disp("Δq = " + mat2str(qSol' - qLast', 5));
    qLast = qSol;

    % Publicar trajetória
    traj = ros2message(pub);
    traj.joint_names = {
        'shoulder_pan_joint','shoulder_lift_joint','elbow_joint', ...
        'wrist_1_joint','wrist_2_joint','wrist_3_joint'};
    pt = ros2message("trajectory_msgs/JointTrajectoryPoint");
    pt.positions = qSol;
    pt.time_from_start.sec = int32(0);
    pt.time_from_start.nanosec = uint32(dt*1e9);
    traj.points = pt;
    send(pub, traj);

    disp("Publicado Jacobiana: " + mat2str(qSol', 4));
  end
end
