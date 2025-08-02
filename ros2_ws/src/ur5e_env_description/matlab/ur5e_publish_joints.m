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

function ur5e_publish_joints
  % 1) Cria nó e publisher de trajectória
  node = ros2node("ur5e_joints_publisher");
  pub  = ros2publisher(node, ...
        "/ur5e_controller/joint_trajectory", ...
        "trajectory_msgs/JointTrajectory");

  % 2) Estado inicial e solver IK
  ur5e = loadrobot('universalUR5e','DataFormat','column');
  q0   = [0; -1.745; -2.27; 0.93; 1.53; 0.0];
  ik   = inverseKinematics('RigidBodyTree',ur5e);
  tol  = ones(6,1)*1e-3;

  % 3) Subscriber para /rl_delta
  sub = ros2subscriber(node, ...
        "/rl_delta", ...
        "geometry_msgs/Vector3", ...
        @deltaCb);

  disp("*** MATLAB: nó pronto, à espera de /rl_delta ***");

  % 4) Apenas bloqueia o main; callbacks continuam a correr
  while true
    pause(0.1);
  end

  % --- callback: roda sempre que chega um delta ---
  function deltaCb(msg)
    % lê o delta (vectors x,y,z)
    d = [msg.x; msg.y; msg.z];
    disp(">>> delta recebido: " + mat2str(d'));

    % acumula no transform atual
    persistent Tdesired
    if isempty(Tdesired)
      Tdesired = getTransform(ur5e, q0, 'tool0');
      disp("Posição inicial TCP:"); disp(Tdesired(1:3,4)');
    end
    Tdesired = Tdesired * trvec2tform(d');

    % resolve o IK incremental
    [qSol, ~] = ik('tool0', Tdesired, tol, q0);
    q0 = qSol;  % atualiza estado para o próximo passo

    % monta mensagem e publica
    traj = ros2message(pub);
    traj.joint_names = { ...
      'shoulder_pan_joint','shoulder_lift_joint','elbow_joint', ...
      'wrist_1_joint','wrist_2_joint','wrist_3_joint'};
    pt = ros2message("trajectory_msgs/JointTrajectoryPoint");
    pt.positions = qSol;
    pt.time_from_start.sec = int32(1);
    traj.points = pt;
    send(pub, traj);

    disp("Publicado IK: " + mat2str(qSol'));
  end

end
