function [data, info] = parallelGripperCommandFeedback
%ParallelGripperCommandFeedback gives an empty data for control_msgs/ParallelGripperCommandFeedback
% Copyright 2019-2021 The MathWorks, Inc.
data = struct();
data.MessageType = 'control_msgs/ParallelGripperCommandFeedback';
[data.state, info.state] = ros.internal.ros2.messages.sensor_msgs.jointState;
info.state.MLdataType = 'struct';
info.MessageType = 'control_msgs/ParallelGripperCommandFeedback';
info.constant = 0;
info.default = 0;
info.maxstrlen = NaN;
info.MaxLen = 1;
info.MinLen = 1;
info.MatPath = cell(1,10);
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
