function printDHParameters()
  % Carrega o modelo
  ur5e = loadrobot('universalUR5e','DataFormat','column');

  fprintf('   link                | alpha (rad) |     a (m)    |     d (m)    | theta_offset (rad)\n');
  fprintf('-----------------------+-------------+--------------+--------------+--------------------\n');

  % Percorre cada corpo (skip base)
  for i = 2:numel(ur5e.Bodies)
    body  = ur5e.Bodies{i};
    joint = body.Joint;
    if strcmp(joint.Type,'revolute')
      A = joint.JointToParentTransform;

      % Extrai os parâmetros MDH
      alpha        = atan2(A(3,2),   A(3,3));   % rotação em torno de x
      a            =      A(1,4);                % translação ao longo de x
      d            =      A(3,4);                % translação ao longo de z
      theta_offset = atan2(A(2,1),   A(1,1));   % rotação em torno de z

      % Imprime usando joint.Name em vez de JointName
      fprintf('%21s | %10.4f | %12.4f | %12.4f | %18.4f\n', ...
              joint.Name, alpha, a, d, theta_offset);
    end
  end
end
