
    % 1) Cria nó e subscreve
    node     = ros2node("/pid_control_node");
    subDisp  = ros2subscriber(node, "/displacements",    "std_msgs/Float32MultiArray");
    subState = ros2subscriber(node, "/joint_states",    "sensor_msgs/JointState");
    pubTraj  = ros2publisher(node, "/ur5e_controller/joint_trajectory",  "trajectory_msgs/JointTrajectory");

    % 2) Carrega modelo para Jacobiana
    ur5e = loadrobot('universalUR5e','DataFormat','column');

    % 3) Ganhos PID
    Kp = 0.01 .* [1.0, 1.0];   % [Kp_x, Kp_z]
    Ki = [0.0, 0.0];   
    Kd = [0.0, 0.0];

    % Anti-windup e saturação
    maxValX = 0.2;   % m/s ou ajusta ao teu espaço de trabalho
    maxValZ = 0.2;  
    
   
   
        int_x = 0; prev_x = 0;
        int_z = 0; prev_z = 0;
        %err_x = 0.01 ; err_z = 0.01;
    

    dt = 0.02;  % 20 Hz
    threshold = 1e-3;  % evita espaços quase singulares

    dt = 1;


    Msg = receive(subState); 
    q = Msg.position;



    while true
        %tic; 

        dispMsg = receive(subDisp); 

        %stateMsg = subState.LatestMessage;
        %if isempty(stateMsg); pause(dt); continue; end
        %q = double(stateMsg.position(:));

        %dispMsg = subDisp.LatestMessage;
        %if isempty(dispMsg); pause(dt); continue; end
        dx = double(dispMsg.data(1));
        dz = double(dispMsg.data(2)); 

        % 5.3) PID cartesiano 
        err_x = -dx;  err_z = -dz;
        int_x = int_x + err_x*dt;
        int_z = int_z + err_z*dt;
        der_x = (err_x - prev_x)/dt;
        der_z = (err_z - prev_z)/dt;
        vx = Kp(1)*err_x + Ki(1)*int_x + Kd(1)*der_x;
        vz = Kp(2)*err_z + Ki(2)*int_z + Kd(2)*der_z;

        % anti-windup por saturação
        if abs(vx) > maxValX
            vx    = sign(vx)*maxValX;
            int_x = int_x - err_x*dt;  
        end
        if abs(vz) > maxValZ
            vz    = sign(vz)*maxValZ;
            int_z = int_z - err_z*dt;
        end

        prev_x = err_x;
        prev_z = err_z;

        % 5.4) Jacobiana completa e check singularidade
        J = geometricJacobian(ur5e, q, 'tool0');
        if abs(det(J)) < threshold
            warning("Jacobian perto da singularidade — saltando correção");
            pause(dt); continue;
        end

        % 5.5) dq para velocidades cartesianos [vx;0;vz]
        dq = 0.2.* pinv(J) * [0; 0; 0; vx; 0; vz]; 

        q_new = q + dq*dt;
        q = q_new;

        %disp(err_x)
        %disp(err_z)
        %disp(vx)
        %disp(vz)
        fprintf("dx %g dz %g \t vx %g vz %g\n",dx,dz,vx,vz)


        trajMsg = ros2message("trajectory_msgs/JointTrajectory");  
        %trajMsg.header.stamp = rostime("now");  
        trajMsg.joint_names = {'shoulder_pan_joint','shoulder_lift_joint','elbow_joint', ...
                       'wrist_1_joint','wrist_2_joint','wrist_3_joint'};


        pt = ros2message("trajectory_msgs/JointTrajectoryPoint");
        pt.positions = q_new;
        %pt.positions = q + [0.6, 0, 0, 0, 0, 0]';
        pt.time_from_start.sec = int32(0);
        pt.time_from_start.nanosec =  uint32(0);
        trajMsg.points = pt;   

        trajMsg.points.positions'  
        send(pubTraj, trajMsg);

        pause(dt);
        %toc
    end
