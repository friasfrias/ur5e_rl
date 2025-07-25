function [data, info] = regionOfInterest
%RegionOfInterest gives an empty data for sensor_msgs/RegionOfInterest
% Copyright 2019-2021 The MathWorks, Inc.
data = struct();
data.MessageType = 'sensor_msgs/RegionOfInterest';
[data.x_offset, info.x_offset] = ros.internal.ros2.messages.ros2.default_type('uint32',1,0);
[data.y_offset, info.y_offset] = ros.internal.ros2.messages.ros2.default_type('uint32',1,0);
[data.height, info.height] = ros.internal.ros2.messages.ros2.default_type('uint32',1,0);
[data.width, info.width] = ros.internal.ros2.messages.ros2.default_type('uint32',1,0);
[data.do_rectify, info.do_rectify] = ros.internal.ros2.messages.ros2.default_type('logical',1,0);
info.MessageType = 'sensor_msgs/RegionOfInterest';
info.constant = 0;
info.default = 0;
info.maxstrlen = NaN;
info.MaxLen = 1;
info.MinLen = 1;
info.MatPath = cell(1,5);
info.MatPath{1} = 'x_offset';
info.MatPath{2} = 'y_offset';
info.MatPath{3} = 'height';
info.MatPath{4} = 'width';
info.MatPath{5} = 'do_rectify';
