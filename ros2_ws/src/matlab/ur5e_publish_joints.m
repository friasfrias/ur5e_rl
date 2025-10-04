% function ur5e_publish_joints
%   % 1) Cria nó e publisher de trajectória
%   node = ros2node("ur5e_joints_publisher");
%   pub  = ros2publisher(node, ...
%         "/ur5e_controller/joint_trajectory", ...
%         "trajectory_msgs/JointTrajectory");
% 
%   % 2) Variável compartilhada para a pose desejada (começa em home)
%   ur5e       = loadrobot('universalUR5e','DataFormat','column');
%   q0         = [0; -1.745; -2.27; 0.93; 1.53; 0.0];
%   Tdesired   = getTransform(ur5e, q0, 'tool0');
% 
%   % 3) Subscriber à pose desejada (callback agora aceita dois args)
%   % sub = ros2subscriber(node, ...
%   %       "/cmd_cartesian", ...
%   %       "geometry_msgs/Pose", ...
%   %       @poseCb);
% 
%   % 4) Prepara o solver IK
%   ik   = inverseKinematics('RigidBodyTree',ur5e);
%   tol  = ones(6,1)*1e-3;
% 
%   % 4) Subscriber para os deltas cartesianos do agente RL
%   sub = ros2subscriber(node, ...
%         "/rl_delta", ...
%         "geometry_msgs/Vector3", ...
%         @deltaCb);
% 
%   disp("*** MATLAB: ur5e_publish_joints ready, waiting for /rl_delta ***")
%   %spin(node);  % mantém vivo, processa callbacks
% 
%   % Callback para atualizar Tdesired com o delta recebido
%   % function poseCb(msg)
%   %   disp(">>> poseCb:"); disp(msg.position);
%   %   Tdesired = trvec2tform([msg.position.x, msg.position.y, msg.position.z])...
%   %            * quat2tform([msg.orientation.w, msg.orientation.x, ...
%   %                         msg.orientation.y, msg.orientation.z]);
%   % end
% 
%   % Callback para atualizar Tdesired com o delta recebido
%   function deltaCb(msg)
% 
%     disp(msg)
%     d = [msg.x; msg.y; msg.z];  % deslocamento em metros
%     % Atualiza a pose desejada multiplicando pelo delta local
%     Tdesired = Tdesired * trvec2tform(d');
%   end
% 
%   % 5) Loop principal
%   while true
%     % 5.a) resolve o IK com a última Tdesired
%     q1 = ik('tool0', Tdesired, tol, q0);
% 
%     % --- 1) monta vetores lower e upper a partir dos limites de cada junta ---
%     bodies     = ur5e.Bodies;                % cell array de rigidBody
%     nJoints    = numel(q1);                  % número de juntas móveis
%     lower      = zeros(nJoints,1);
%     upper      = zeros(nJoints,1);
%     idx        = 0;
% 
%     for i = 1:numel(bodies)
%         joint = bodies{i}.Joint;
%         % ignora juntas fixas
%         if strcmp(joint.Type,"fixed")
%             continue
%         end
%         idx = idx + 1;
%         % joint.PositionLimits é um vetor [min, max]
%         lim = joint.PositionLimits();  % 1×2
%         lower(idx) = lim(1);
%         upper(idx) = lim(2);
%     end
% 
%     % --- 2) aplica clamp para garantir que q1 fica dentro dos limites ---
%     q1 = max( min(q1, upper), lower );
% 
% 
%     % 5.b) monta e envia a Trajectory
%     traj = ros2message(pub);
%     traj.joint_names = { ...
%       'shoulder_pan_joint','shoulder_lift_joint','elbow_joint', ...
%       'wrist_1_joint','wrist_2_joint','wrist_3_joint' ...
%     };
%     pt = ros2message("trajectory_msgs/JointTrajectoryPoint");
%     pt.positions            = q1;
%     pt.time_from_start.sec  = int32(1);
%     pt.time_from_start.nanosec = uint32(0);
%     pt.velocities    = [];
%     pt.accelerations = [];
%     pt.effort        = [];
%     traj.points = pt;
%     send(pub, traj);
%     disp("Published q1: "+mat2str(q1',4))
% 
%     % 5.c) atualiza e aguarda (o pause gatilha o processamento de callbacks)
%     q0 = q1;
%     pause(0.01);
%   end
% end
% 
% function ur5e_publish_joints
%   % 1) Cria nó e publisher de trajectória
%   node = ros2node("ur5e_joints_publisher");
%   pub  = ros2publisher(node, ...
%         "/ur5e_controller/joint_trajectory", ...
%         "trajectory_msgs/JointTrajectory");
% 
%   % 2) Estado inicial e solver IK
%   ur5e = loadrobot('universalUR5e','DataFormat','column');
%   q0   = [0; -1.745; -2.27; 0.93; 1.53; 0.0];
%   ik   = inverseKinematics('RigidBodyTree',ur5e);
%   tol  = ones(6,1)*1e-3;
% 
%   % 3) Subscriber para /rl_delta
%   sub = ros2subscriber(node, ...
%         "/rl_delta", ...
%         "geometry_msgs/Vector3", ...
%         @deltaCb);
% 
%   disp("*** MATLAB: nó pronto, à espera de /rl_delta ***");
% 
%   % 4) Apenas bloqueia o main; callbacks continuam a correr
%   while true
%     pause(0.1);
%   end
% 
%   % --- callback: roda sempre que chega um delta ---
%   function deltaCb(msg)
%     % lê o delta (vectors x,y,z)
%     d = [msg.x; msg.y; msg.z];
%     disp(">>> delta recebido: " + mat2str(d'));
% 
%     % acumula no transform atual
%     persistent Tdesired
%     if isempty(Tdesired)
%       Tdesired = getTransform(ur5e, q0, 'tool0');
%       disp("Posição inicial TCP:"); disp(Tdesired(1:3,4)');
%     end
%     Tdesired = Tdesired * trvec2tform(d');
% 
%     % resolve o IK incremental
%     [qSol, ~] = ik('tool0', Tdesired, tol, q0);
%     q0 = qSol;  % atualiza estado para o próximo passo
% 
%     % monta mensagem e publica
%     traj = ros2message(pub);
%     traj.joint_names = { ...
%       'shoulder_pan_joint','shoulder_lift_joint','elbow_joint', ...
%       'wrist_1_joint','wrist_2_joint','wrist_3_joint'};
%     pt = ros2message("trajectory_msgs/JointTrajectoryPoint");
%     pt.positions = qSol;
%     pt.time_from_start.sec = int32(1);
%     traj.points = pt;
%     send(pub, traj);
% 
%     disp("Publicado IK: " + mat2str(qSol'));
%   end
% 
% end

% 
% 
% 
% 
% function ur5e_publish_joints
%   % 1) Cria nó e publisher de trajectória
%   node = ros2node("ur5e_joints_publisher");
%   pub  = ros2publisher(node, ...
%         "/ur5e_controller/joint_trajectory", ...
%         "trajectory_msgs/JointTrajectory");
% 
%   % 2) Estado inicial e solver IK
%   ur5e = loadrobot('universalUR5e','DataFormat','column');
%   q0   = [0; -1.745; -2.27; 0.93; 1.53; 0.0];
%   ik   = inverseKinematics('RigidBodyTree',ur5e);
%   tol  = ones(6,1)*1e-3;
% 
%   % 3) Subscriber para /rl_delta
%   sub = ros2subscriber(node, ...
%         "/rl_delta", ...
%         "geometry_msgs/Vector3", ...
%         @deltaCb);
% 
%   disp("*** MATLAB: nó pronto, à espera de /rl_delta ***");
% 
%   % 4) Apenas bloqueia o main; callbacks continuam a correr
%   while true
%     pause(0.1);
%   end
% 
%   % --- callback: roda sempre que chega um delta ---
%   function deltaCb(msg)
%     % lê o delta (vectors x,y,z)
%     d = [msg.x; msg.y; msg.z];
%     disp(">>> delta recebido: " + mat2str(d'));
% 
%     % acumula no transform atual
%     persistent Tdesired
%     if isempty(Tdesired)
%       Tdesired = getTransform(ur5e, q0, 'tool0');
%       disp("Posição inicial TCP:"); disp(Tdesired(1:3,4)');
%     end
%     Tdesired = Tdesired * trvec2tform(d');
% 
%     % resolve o IK incremental
%     [qSol, ~] = ik('tool0', Tdesired, tol, q0);
%     q0 = qSol;  % atualiza estado para o próximo passo
% 
%     % monta mensagem e publica
%     traj = ros2message(pub);
%     traj.joint_names = { ...
%       'shoulder_pan_joint','shoulder_lift_joint','elbow_joint', ...
%       'wrist_1_joint','wrist_2_joint','wrist_3_joint'};
%     pt = ros2message("trajectory_msgs/JointTrajectoryPoint");
%     pt.positions = qSol;
%     pt.time_from_start.sec = int32(1);
%     traj.points = pt;
%     send(pub, traj);
% 
%     disp("Publicado IK: " + mat2str(qSol'));
%   end
% 
% end




% function ur5e_publish_joints
%   % 1) Cria nó e publisher de trajectória
%   node = ros2node("ur5e_joints_publisher");
%   pub  = ros2publisher(node, ...
%         "/ur5e_controller/joint_trajectory", ...
%         "trajectory_msgs/JointTrajectory");
% 
%   % 2) Estado inicial e solver IK
%   ur5e = loadrobot('universalUR5e','DataFormat','column');
%   q0   = [0; -1.745; -2.27; 0.93; 1.53; 0.0];
%   ik   = inverseKinematics('RigidBodyTree',ur5e);
%   tol  = ones(6,1)*1e-3;
% 
%   % 3) Subscreve os dois tópicos
%   subDelta = ros2subscriber(node, "/rl_delta", "geometry_msgs/Vector3", @deltaCb);
%   subReset = ros2subscriber(node, "/rl_reset", "std_msgs/Bool", @resetCb);
% 
%   disp("*** MATLAB: nó pronto, à espera de /rl_delta e /rl_reset ***");
% 
%   % 4) Apenas bloqueia o main; callbacks continuam ativos
%   while true
%     pause(0.1);
%   end
% 
%   % ---- Callback do reset ----
%   function resetCb(msg)
%     if msg.data
%       disp(">>> Reset recebido — estado reinicializado.");
%       clear deltaCb  % limpa os persistent da outra callback
%     end
%   end
% 
%   % ---- Callback do delta ----
%   function deltaCb(msg)
%     persistent Tdesired
%     persistent qLast
% 
%     d = [msg.x; msg.y; msg.z];
%     disp(">>> delta recebido: " + mat2str(d'));
% 
%     if isempty(Tdesired)
%       Tdesired = getTransform(ur5e, q0, 'tool0');
%       qLast = q0;
%       disp("Posição inicial TCP:"); disp(Tdesired(1:3,4)');
%     end
% 
%     % Aplica delta à transformação atual
%     Tdesired = Tdesired * trvec2tform(d');
% 
%     % Resolve IK incremental
%     [qSol, ~] = ik('tool0', Tdesired, tol, qLast);
%     qLast = qSol;
% 
%     % Monta e envia a mensagem de trajetória
%     traj = ros2message(pub);
%     traj.joint_names = {
%       'shoulder_pan_joint','shoulder_lift_joint','elbow_joint', ...
%       'wrist_1_joint','wrist_2_joint','wrist_3_joint'};
%     pt = ros2message("trajectory_msgs/JointTrajectoryPoint");
%     pt.positions = qSol;
%     pt.time_from_start.sec = int32(0);
%     pt.time_from_start.nanosec = uint32(1e06);
%     traj.points = pt;
%     send(pub, traj);
% 
%     disp("Publicado IK: " + mat2str(qSol', 4));
%   end
% end


% function ur5e_publish_joints
%   % 1) Cria nó e publisher de trajectória
%   node = ros2node("ur5e_joints_publisher");
%   pub  = ros2publisher(node, ...
%         "/ur5e_controller/joint_trajectory", ...
%         "trajectory_msgs/JointTrajectory");
% 
%   % 2) Estado inicial e solver IK
%   ur5e = loadrobot('universalUR5e','DataFormat','column');
%   q0   = [0; -1.745; -2.27; 0.93; 1.53; 0.0];
%   ik   = inverseKinematics('RigidBodyTree', ur5e);
%   tol  = ones(6,1)*1e-3;
% 
%   % 3) Subscreve os dois tópicos
%   subDelta = ros2subscriber(node, "/rl_delta", "geometry_msgs/Vector3", @deltaCb);
%   subReset = ros2subscriber(node, "/rl_reset", "std_msgs/Bool", @resetCb);
% 
%   disp("*** MATLAB: nó pronto, à espera de /rl_delta e /rl_reset ***");
% 
%   % 4) Apenas bloqueia o main; callbacks continuam ativos
%   while true
%     pause(0.1);
%   end
% 
%   % ---- Callback do reset ----
%   function resetCb(msg)
%     if msg.data
%       disp(">>> Reset recebido — estado reinicializado.");
%       clear deltaCb  % limpa os persistent da outra callback
%       disp("[CONFIRMAÇÃO] Variáveis persistentes apagadas.");
% 
%       % === Pausa para estabilizar ===
%       pause(1.0);
%       disp("[PAUSA] Espera de 1 segundo após reset concluída.");
%     end
%   end
% 
%   % ---- Callback do delta ----
%   function deltaCb(msg)
%     persistent Tdesired
%     persistent qLast
% 
%     d = [msg.x; msg.y; msg.z];
%     disp(">>> delta recebido: " + mat2str(d'));
% 
%     if isempty(Tdesired)
%       Tdesired = getTransform(ur5e, q0, 'tool0');
%       qLast = q0;
%       disp("[CONFIRMAÇÃO] Tdesired reinicializado.");
%       disp("Posição inicial TCP:"); disp(Tdesired(1:3,4)');
%     end
% 
%     % Aplica delta à transformação atual
%     Tdesired = Tdesired * trvec2tform(d');
% 
%     % Resolve IK incremental
%     [qSol, ~] = ik('tool0', Tdesired, tol, qLast);
%     qLast = qSol;
% 
%     % Monta e envia a mensagem de trajetória
%     traj = ros2message(pub);
%     traj.joint_names = {
%       'shoulder_pan_joint','shoulder_lift_joint','elbow_joint', ...
%       'wrist_1_joint','wrist_2_joint','wrist_3_joint'};
%     pt = ros2message("trajectory_msgs/JointTrajectoryPoint");
%     pt.positions = qSol;
%     pt.time_from_start.sec = int32(0);
%     pt.time_from_start.nanosec = uint32(1e06);
%     traj.points = pt;
%     send(pub, traj);
% 
%     disp("Publicado IK: " + mat2str(qSol', 4));
%   end
% end
% 


% function ur5e_publish_joints
%   % 1) Cria nó e publisher de trajectória
%   node = ros2node("ur5e_joints_publisher");
%   pub  = ros2publisher(node, ...
%         "/ur5e_controller/joint_trajectory", ...
%         "trajectory_msgs/JointTrajectory");
% 
%   % 2) Estado inicial e solver IK
%   ur5e = loadrobot('universalUR5e','DataFormat','column');
%   q0   = [0; -1.745; -2.27; 0.93; 1.53; 0.0];
%   ik   = inverseKinematics('RigidBodyTree', ur5e);
%   tol  = ones(6,1)*1e-3;
% 
%   % 3) Variáveis globais de estabilização
%   ignore_deltas = false;
%   steps_since_reset = 0;
%   has_reset_stabilized = false;
% 
%   % 4) Subscreve os tópicos
%   subDelta = ros2subscriber(node, "/rl_delta", "geometry_msgs/Vector3", @deltaCb);
%   subReset = ros2subscriber(node, "/rl_reset", "std_msgs/Bool", @resetCb);
%   subStab  = ros2subscriber(node, "/rl_stabilized", "std_msgs/Bool", @stabilizedCb);
%   subState = ros2subscriber(node, "/joint_states", "sensor_msgs/JointState");
% 
%   % 5) Variáveis persistentes
%   persistent Tdesired
%   persistent qLast
% 
%   disp("*** MATLAB: nó pronto, à espera de /rl_delta, /rl_reset e /rl_stabilized ***");
% 
%   while true
%     pause(0.1);
%   end
% 
%   % ---- Callback do reset ----
%   function resetCb(msg)
%     if msg.data
%       disp(">>> Reset recebido — estado reinicializado.");
%       clear deltaCb
%       disp("[CONFIRMAÇÃO] Variáveis persistentes apagadas.");
% 
%       ignore_deltas = true;
%       steps_since_reset = 0;
%       has_reset_stabilized = false;
% 
%       Tdesired = [];
%       qLast = [];
%     end
%   end
% 
%   % ---- Callback do stabilized ----
%   function stabilizedCb(msg)
%     if msg.data
%       ignore_deltas = false;
%       has_reset_stabilized = true;
% 
%       % Espera até o /joint_states tiver uma mensagem válida
%       tries = 0;
%       while isempty(subState.LatestMessage) && tries < 10
%         pause(0.1);
%         tries = tries + 1;
%       end
% 
%       if isempty(subState.LatestMessage)
%         warning("Não foi possível obter /joint_states após estabilização.");
%         return;
%       end
% 
%       q_now = subState.LatestMessage.position;
%       Tdesired = getTransform(ur5e, q_now, 'tool0');
%       qLast = q_now;
% 
%       disp("[MATLAB] Estabilização concluída — comandos RL reativados.");
%       disp("[MATLAB] Tdesired inicializado com q_now.");
%       disp("q_now = "); disp(q_now');
%     end
%   end
% 
%   % ---- Callback do delta ----
%   function deltaCb(msg)
%     if ignore_deltas || ~has_reset_stabilized || isempty(Tdesired)
%       steps_since_reset = steps_since_reset + 1;
%       disp("[MATLAB] Estabilização ativa ou Tdesired não definido — q = q0. Passo " + steps_since_reset);
% 
%       traj = ros2message(pub);
%       traj.joint_names = {
%           'shoulder_pan_joint','shoulder_lift_joint','elbow_joint', ...
%           'wrist_1_joint','wrist_2_joint','wrist_3_joint'};
%       pt = ros2message("trajectory_msgs/JointTrajectoryPoint");
%       pt.positions = q0;
%       pt.time_from_start.sec = int32(0);
%       pt.time_from_start.nanosec = uint32(5e8);
%       traj.points = pt;
%       send(pub, traj);
%       return;
%     end
% 
%     d = [msg.x; msg.y; msg.z];
%     disp(">>> delta recebido: " + mat2str(d'));
% 
%     % DEBUG opcional: força delta maior para testar movimento
%     if norm(d) < 0.001
%       d = [0.02; 0.0; 0.0];  % força deslocamento lateral
%       disp("[DEBUG] Delta forçado para teste: " + mat2str(d'));
%     end
% 
%     % Mostrar transformação do TCP
%     T_before = Tdesired;
%     T_after  = Tdesired * trvec2tform(d');
%     disp("TCP antes : " + mat2str(T_before(1:3,4)', 4));
%     disp("TCP depois: " + mat2str(T_after(1:3,4)', 4));
% 
%     % Atualizar Tdesired
%     Tdesired = T_after;
%     [qSol, ~] = ik('tool0', Tdesired, tol, qLast);
% 
%     disp("Δq = " + mat2str(qSol' - qLast', 5));
%     qLast = qSol;
% 
%     % Publicar trajetória
%     traj = ros2message(pub);
%     traj.joint_names = {
%         'shoulder_pan_joint','shoulder_lift_joint','elbow_joint', ...
%         'wrist_1_joint','wrist_2_joint','wrist_3_joint'};
%     pt = ros2message("trajectory_msgs/JointTrajectoryPoint");
%     pt.positions = qSol;
%     pt.time_from_start.sec = int32(0);
%     pt.time_from_start.nanosec = uint32(5e8);
%     traj.points = pt;
%     send(pub, traj);
% 
%     disp("Publicado IK: " + mat2str(qSol', 4));
%   end
% end



% function ur5e_publish_joints
%   % 1) Cria nó e publisher de trajectória
%   node = ros2node("ur5e_joints_publisher");
%   pub  = ros2publisher(node, ...
%         "/ur5e_controller/joint_trajectory", ...
%         "trajectory_msgs/JointTrajectory");
% 
%   % 2) Estado inicial e solver IK
%   ur5e = loadrobot('universalUR5e','DataFormat','column');
%   q0   = [0; -1.745; -2.27; 0.93; 1.53; 0.0];
%   ik   = inverseKinematics('RigidBodyTree', ur5e);
%   tol  = ones(6,1)*1e-3;
% 
%   % 3) Variáveis globais de estabilização
%   ignore_deltas = false;
%   steps_since_reset = 0;
%   has_reset_stabilized = false;
% 
%   % 4) Subscreve os tópicos
%   subDelta = ros2subscriber(node, "/rl_delta", "geometry_msgs/Vector3", @deltaCb);
%   subReset = ros2subscriber(node, "/rl_reset", "std_msgs/Bool", @resetCb);
%   subStab  = ros2subscriber(node, "/rl_stabilized", "std_msgs/Bool", @stabilizedCb);
%   subState = ros2subscriber(node, "/joint_states", "sensor_msgs/JointState");
% 
%   % 5) Variáveis persistentes
%   persistent Tdesired
%   persistent qLast
% 
%   disp("*** MATLAB: nó pronto, à espera de /rl_delta, /rl_reset e /rl_stabilized ***");
% 
%   while true
%     pause(0.1);
%   end
% 
%   % ---- Callback do reset ----
%   function resetCb(msg)
%     if msg.data
%       disp(">>> Reset recebido — estado reinicializado.");
%       clear deltaCb
%       disp("[CONFIRMAÇÃO] Variáveis persistentes apagadas.");
% 
%       ignore_deltas = true;
%       steps_since_reset = 0;
%       has_reset_stabilized = false;
% 
%       Tdesired = [];
%       qLast = [];
%     end
%   end
% 
%   % ---- Callback do stabilized ----
%   function stabilizedCb(msg)
%     if msg.data
%       ignore_deltas = false;
%       has_reset_stabilized = true;
% 
%       % Espera até o /joint_states tiver uma mensagem válida
%       tries = 0;
%       while isempty(subState.LatestMessage) && tries < 10
%         pause(0.1);
%         tries = tries + 1;
%       end
% 
%       if isempty(subState.LatestMessage)
%         warning("Não foi possível obter /joint_states após estabilização.");
%         return;
%       end
% 
%       q_now = subState.LatestMessage.position;
%       Tdesired = getTransform(ur5e, q_now, 'tool0');
%       qLast = q_now;
% 
%       disp("[MATLAB] Estabilização concluída — comandos RL reativados.");
%       disp("[MATLAB] Tdesired inicializado com q_now.");
%       disp("q_now = "); disp(q_now');
%     end
%   end
% 
%   % ---- Callback do delta ----
%   function deltaCb(msg)
%     if ignore_deltas || ~has_reset_stabilized || isempty(Tdesired)
%       steps_since_reset = steps_since_reset + 1;
%       disp("[MATLAB] Estabilização ativa ou Tdesired não definido — q = q0. Passo " + steps_since_reset);
% 
%       traj = ros2message(pub);
%       traj.joint_names = {
%           'shoulder_pan_joint','shoulder_lift_joint','elbow_joint', ...
%           'wrist_1_joint','wrist_2_joint','wrist_3_joint'};
%       pt = ros2message("trajectory_msgs/JointTrajectoryPoint");
%       pt.positions = q0;
%       pt.time_from_start.sec = int32(0);
%       pt.time_from_start.nanosec = uint32(5e8);
%       traj.points = pt;
%       send(pub, traj);
%       return;
%     end
% 
%     d = [msg.x; msg.y; msg.z];
%     disp(">>> delta recebido: " + mat2str(d'));
% 
%     % DEBUG opcional: força delta maior para testar movimento
%     if norm(d) < 0.001
%       d = [0.02; 0.0; 0.0];  % força deslocamento lateral
%       disp("[DEBUG] Delta forçado para teste: " + mat2str(d'));
%     end
% 
%     % Mostrar transformação do TCP
%     T_before = Tdesired;
%     T_after  = Tdesired * trvec2tform(d');
%     disp("TCP antes : " + mat2str(T_before(1:3,4)', 4));
%     disp("TCP depois: " + mat2str(T_after(1:3,4)', 4));
% 
%     % Atualizar Tdesired
%     Tdesired = T_after;
%     [qSol, ~] = ik('tool0', Tdesired, tol, qLast);
% 
%     disp("Δq = " + mat2str(qSol' - qLast', 5));
%     qLast = qSol;
% 
%     % Publicar trajetória
%     traj = ros2message(pub);
%     traj.joint_names = {
%         'shoulder_pan_joint','shoulder_lift_joint','elbow_joint', ...
%         'wrist_1_joint','wrist_2_joint','wrist_3_joint'};
%     pt = ros2message("trajectory_msgs/JointTrajectoryPoint");
%     pt.positions = qSol;
%     pt.time_from_start.sec = int32(0);
%     pt.time_from_start.nanosec = uint32(0.1);
%     traj.points = pt;
%     send(pub, traj);
% 
%     disp("Publicado IK: " + mat2str(qSol', 4));
%   end
% end


function ur5e_publish_joints
  % 1) Nó e publisher de trajectória
  node = ros2node("ur5e_joints_publisher");
  pub  = ros2publisher(node, ...
        "/ur5e_controller/joint_trajectory", ...
        "trajectory_msgs/JointTrajectory");

  % 2) Modelo UR5e + estado inicial (igual ao env.py)
  ur5e = loadrobot('universalUR5e','DataFormat','column');
  q0   = [0; -1.745; -2.26; 0.93; 1.53; 0.0];     % rad
  Tdesired = getTransform(ur5e, q0, 'tool0');

  % 3) Solver IK  (nota: 'tol' são PESOS 1x6: [pos_xyz orient_rpy])
  ik  = inverseKinematics('RigidBodyTree', ur5e);
  tol = ones(6,1)*1e-3;   

  % 4) Subscribers
  subDelta = ros2subscriber(node, "/rl_delta", "geometry_msgs/Vector3", @deltaCb);
  subReset = ros2subscriber(node, "/rl_reset", "std_msgs/Bool",       @resetCb);

  % === Callbacks (nested, partilham Tdesired/q0) ==========================
  function resetCb(msg)
    if msg.data
      % Recentra Tdesired na pose atual de q0 para evitar arranques laterais
      Tdesired = getTransform(ur5e, q0, 'tool0');
      % (Se quiseres, dá também um pequeno "flush" com q0)
      traj = ros2message(pub);
      traj.joint_names = { ...
        'shoulder_pan_joint','shoulder_lift_joint','elbow_joint', ...
        'wrist_1_joint','wrist_2_joint','wrist_3_joint' };
      pt = ros2message("trajectory_msgs/JointTrajectoryPoint");
      pt.positions = q0;
      pt.time_from_start.sec     = int32(0);
      pt.time_from_start.nanosec = uint32(5e7);   % 50 ms
      traj.points = pt;
      send(pub, traj);
      disp(">>> /rl_reset recebido — Tdesired recentrado em q0");
    end
  end

  function deltaCb(msg)
    % campos em minúsculas no MATLAB ROS2
    d = [msg.x; msg.y; msg.z];     % metros
    % aplica incremento na pose alvo (frame local do TCP)
    Tdesired = Tdesired * trvec2tform(d');
  end
  % =======================================================================

  disp("*** MATLAB: ur5e_publish_joints pronto; a ouvir /rl_delta e /rl_reset ***");

  % 5) Loop principal: resolve IK, clamp e envia trajectória
  while true
    % 5.a) IK para a última Tdesired
    q1 = ik('tool0', Tdesired, tol, q0);

    % 5.b) clamp por limites de junta
    bodies  = ur5e.Bodies;
    nJoints = numel(q1);
    lower   = zeros(nJoints,1);
    upper   = zeros(nJoints,1);
    idx = 0;
    for i = 1:numel(bodies)
      joint = bodies{i}.Joint;
      if strcmp(joint.Type,"fixed"); continue; end
      idx = idx + 1;
      lim = joint.PositionLimits();  % [min max]
      lower(idx) = lim(1);
      upper(idx) = lim(2);
    end
    q1 = max(min(q1, upper), lower);

    % 5.c) TrajectoryPoint rápido (segue incrementos)
    traj = ros2message(pub);
    traj.joint_names = { ...
      'shoulder_pan_joint','shoulder_lift_joint','elbow_joint', ...
      'wrist_1_joint','wrist_2_joint','wrist_3_joint' };
    pt = ros2message("trajectory_msgs/JointTrajectoryPoint");
    pt.positions = q1;
    pt.time_from_start.sec     = int32(0);
    pt.time_from_start.nanosec = uint32(8e7);   % ~80 ms
    pt.velocities    = [];
    pt.accelerations = [];
    pt.effort        = [];
    traj.points = pt;
    send(pub, traj);
    % disp("send q=" + mat2str(q1',4));

    % 5.d) avança estado e deixa callbacks correrem
    q0 = q1;
    pause(0.02);    % ~50 Hz
  end
end
