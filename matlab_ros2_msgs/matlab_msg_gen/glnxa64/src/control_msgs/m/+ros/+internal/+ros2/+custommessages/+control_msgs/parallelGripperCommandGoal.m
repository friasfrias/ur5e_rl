function [data, info] = parallelGripperCommandGoal
%ParallelGripperCommandGoal gives an empty data for control_msgs/ParallelGripperCommandGoal
% Copyright 2019-2021 The MathWorks, Inc.
data = struct();
data.MessageType = 'control_msgs/ParallelGripperCommandGoal';
[data.command, info.command] = ros.internal.ros2.messages.sensor_msgs.jointState;
info.command.MLdataType = 'struct';
info.MessageType = 'control_msgs/ParallelGripperCommandGoal';
info.constant = 0;
info.default = 0;
info.maxstrlen = NaN;
info.MaxLen = 1;
info.MinLen = 1;
info.MatPath = cell(1,10);
info.MatPath{1} = 'command';
info.MatPath{2} = 'command.header';
info.MatPath{3} = 'command.header.stamp';
info.MatPath{4} = 'command.header.stamp.sec';
info.MatPath{5} = 'command.header.stamp.nanosec';
info.MatPath{6} = 'command.header.frame_id';
info.MatPath{7} = 'command.name';
info.MatPath{8} = 'command.position';
info.MatPath{9} = 'command.velocity';
info.MatPath{10} = 'command.effort';
