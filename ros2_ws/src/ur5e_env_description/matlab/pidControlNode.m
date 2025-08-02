
    % 1) Cria nó e subscreve
    node     = ros2node("/pid_control_node");
    subDisp  = ros2subscriber(node, "/displacements",    "std_msgs/Float32MultiArray");
    subState = ros2subscriber(node, "/joint_states",    "sensor_msgs/JointState");
    subPattern = ros2subscriber(node, "/pattern_detected", "std_msgs/Bool");
    pubTraj  = ros2publisher(node, "/ur5e_controller/joint_trajectory",  "trajectory_msgs/JointTrajectory");

    trajMsg = ros2message("trajectory_msgs/JointTrajectory");  
        %trajMsg.header.stamp = rostime("now");  
        trajMsg.joint_names = {'shoulder_pan_joint','shoulder_lift_joint','elbow_joint', ...
                       'wrist_1_joint','wrist_2_joint','wrist_3_joint'};

    % 2) Carrega modelo para Jacobiana
    ur5e = loadrobot('universalUR5e','DataFormat','column');

    % 3) Ganhos PID
    % Kp = 2.4      .* [1.0, 1.0, 1.0];
    % Ki = 0.01     .*[1.0, 1.0, 1.0];   
    % Kd = 0.001.*[1.0, 1.0, 1.0];
    Kp = 4.3.* [1.0, 1.0, 1.0];
    Ki = 0.001     .*[1.0, 1.0, 1.0];   
    Kd = 0.1.*[1.0, 1.0, 1.0];

    % Anti-windup e saturação
    maxValX = 0.2;   % m/s ou ajusta ao teu espaço de trabalho
    maxValZ = 0.2;  

    int_x = 0; prev_x = 0;
    int_y = 0; prev_y = 0;
    int_z = 0; prev_z = 0;

    %dt = 0.01   ;  % 100 Hz
    dt = 0.007; 
    threshold = 1e-4;  % evita espaços quase singulares

    tempos = zeros(1,10);  % vetor para guardar duração de cada episódio

    for ep = 1:10

        fprintf("\n📘 Episódio %d\n", ep)

        int_x = 0; prev_x = 0;
        int_y = 0; prev_y = 0;
        int_z = 0; prev_z = 0;

        Msg = receive(subState); 
        q = Msg.position
        T = getTransform(ur5e,q,"tool0");
        ref = T(1:3,4);
    
        t0 = tic;
    
        while true 
    
            patternMsg = receive(subPattern, 1);  % timeout de 1s
            if isempty(patternMsg) || ~patternMsg.data
                disp("🔄 Padrão não detetado — reiniciar episódio");
                break;
            end
            
            dispMsg = receive(subDisp); 
    
            dx = double(dispMsg.data(1));
            dz = double(dispMsg.data(2)); 
    
            % 5.3) PID cartesiano 
            T = getTransform(ur5e,q,"tool0");
    
            %dx = 37 *dx;
            dx = 40 *dx;
            dz = 2      *dz;
    
    
            err_x = ref(1) - T(1,4) - dz;
            err_y = ref(2) - T(2,4) + dx;  
            err_z = ref(3) - T(3,4);
    
    
    
            err_norm = norm( err_x + err_y + err_z);
    
            fprintf("ex %g ey %g ez %g |e| %g dx %g dz %g \n",err_x,err_y,err_z, err_norm, dx, dz)
    
            %if( err_norm < 0.5e-6 ) break; end 
    
            int_x = int_x + err_x*dt;
            int_y = int_y +  err_y*dt;
            int_z = int_z + err_z*dt;
            der_x = (err_x - prev_x)/dt;
            der_y = (err_y - prev_y)/dt;
            der_z = (err_z - prev_z)/dt;
    
            vx = Kp(1)*err_x + Ki(1)*int_x + Kd(1)*der_x;
            vy = Kp(2)*err_y + Ki(2)*int_y + Kd(2)*der_y;
            vz = Kp(3)*err_z + Ki(3)*int_z + Kd(3)*der_z;
    
            prev_x = err_x;
            prev_y = err_y;
            prev_z = err_z;
    
            % 5.4) Jacobiana completa e check singularidade
            J = geometricJacobian(ur5e, q, 'tool0');
            if abs(det(J)) < threshold
                warning("Jacobian perto da singularidade — saltando correção");
                pause(dt); break;
            end
    
            % 5.5) dq para velocidades cartesianos [vx;0;vz]
            dq = pinv(J) * [0; 0; 0; vx; vy; vz]; 
    
            q_new = q + dq*dt;
            q = q_new;
    
            pt = ros2message("trajectory_msgs/JointTrajectoryPoint");
            pt.positions = q_new;
            %pt.positions = q + [0.6, 0, 0, 0, 0, 0]';
            pt.time_from_start.sec = int32(0);
            pt.time_from_start.nanosec =  uint32(0);
            trajMsg.points = pt;   
    
            %trajMsg.points.positions'  
            send(pubTraj, trajMsg);
    
            pause(dt);
    
        end

        % Guardar tempo
        tempos(ep) = toc(t0);
        fprintf("✅ Episódio %d concluído em %.2f segundos\n", ep, tempos(ep));
    end

    % Mostrar gráfico
    figure;
    plot(1:10, tempos, '-o', 'LineWidth', 2);
    xlabel("Episódio");
    ylabel("Tempo até perda do padrão (s)");
    title("Desempenho do PID por Episódio");
    grid on;