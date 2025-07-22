
clear;

% load UR5e robot 
ur5e = loadrobot('universalUR5e','DataFormat','column');
%showdetails(ur5e)
%robot.Gravity = [0 0 -9.81];

% joints vector - initial configuration 
%q = zeros(6,1)
q = deg2rad([0,-45,45,0,0,0])' 


% Loop at Fixed Rate of 10Hz 
r = rateControl(10);
dt = r.DesiredPeriod; 


maxIterations = 20;


for it = 1:1:maxIterations

    %compute Jacobian
    J = geometricJacobian(ur5e, q, 'tool0');  % 6xN Jacobian

    % desired end-effector velocity (wx, wy, wz, vx, vy, vz)
    desired_w_v = [0, 0, 0, 0, 0, 0.05]'

    
    % solve for joint velocies
    deltaq = inv(J + 1e-6 * eye(6)) * desired_w_v;
    %deltaq = pinv(J) * desired_w_v;

    % get joint position update 
    q = q + deltaq * dt;  

    % display robot 
    figure(1); clf;
    show(ur5e, q, 'PreservePlot', false);
    axis([-1 1 -1 1 0 2]);                  % zoom level                
    title("ur5e")
    view(-160,30)
    waitfor(r);     % adaptive loop 

end




