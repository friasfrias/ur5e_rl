function [data, info] = fluidPressure
%FluidPressure gives an empty data for sensor_msgs/FluidPressure
% Copyright 2019-2021 The MathWorks, Inc.
data = struct();
data.MessageType = 'sensor_msgs/FluidPressure';
[data.header, info.header] = ros.internal.ros2.messages.std_msgs.header;
info.header.MLdataType = 'struct';
[data.fluid_pressure, info.fluid_pressure] = ros.internal.ros2.messages.ros2.default_type('double',1,0);
[data.variance, info.variance] = ros.internal.ros2.messages.ros2.default_type('double',1,0);
info.MessageType = 'sensor_msgs/FluidPressure';
info.constant = 0;
info.default = 0;
info.maxstrlen = NaN;
info.MaxLen = 1;
info.MinLen = 1;
info.MatPath = cell(1,7);
info.MatPath{1} = 'header';
info.MatPath{2} = 'header.stamp';
info.MatPath{3} = 'header.stamp.sec';
info.MatPath{4} = 'header.stamp.nanosec';
info.MatPath{5} = 'header.frame_id';
info.MatPath{6} = 'fluid_pressure';
info.MatPath{7} = 'variance';
