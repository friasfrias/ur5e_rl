function [data, info] = parallelGripperCommandResult
%ParallelGripperCommandResult gives an empty data for control_msgs/ParallelGripperCommandResult
% Copyright 2019-2021 The MathWorks, Inc.
data = struct();
data.MessageType = 'control_msgs/ParallelGripperCommandResult';
[data.state, info.state] = ros.internal.ros2.messages.sensor_msgs.jointState;
info.state.MLdataType = 'struct';
[data.stalled, info.stalled] = ros.internal.ros2.messages.ros2.default_type('logical',1,0);
[data.reached_goal, info.reached_goal] = ros.internal.ros2.messages.ros2.default_type('logical',1,0);
info.MessageType = 'control_msgs/ParallelGripperCommandResult';
info.constant = 0;
info.default = 0;
info.maxstrlen = NaN;
info.MaxLen = 1;
info.MinLen = 1;
info.MatPath = cell(1,12);
info.MatPath{1} = 'state';
info.MatPath{2} = 'state.header';
info.MatPath{3} = 'state.header.stamp';
info.MatPath{4} = 'state.header.stamp.sec';
info.MatPath{5} = 'state.header.stamp.nanosec';
info.MatPath{6} = 'state.header.frame_id';
info.MatPath{7} = 'state.name';
info.MatPath{8} = 'state.position';
info.MatPath{9} = 'state.velocity';
info.MatPath{10} = 'state.effort';
info.MatPath{11} = 'stalled';
info.MatPath{12} = 'reached_goal';
