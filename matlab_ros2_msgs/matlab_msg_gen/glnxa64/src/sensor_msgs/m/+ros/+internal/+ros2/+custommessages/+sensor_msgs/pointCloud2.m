function [data, info] = pointCloud2
%PointCloud2 gives an empty data for sensor_msgs/PointCloud2
% Copyright 2019-2021 The MathWorks, Inc.
data = struct();
data.MessageType = 'sensor_msgs/PointCloud2';
[data.header, info.header] = ros.internal.ros2.messages.std_msgs.header;
info.header.MLdataType = 'struct';
[data.height, info.height] = ros.internal.ros2.messages.ros2.default_type('uint32',1,0);
[data.width, info.width] = ros.internal.ros2.messages.ros2.default_type('uint32',1,0);
[data.fields, info.fields] = ros.internal.ros2.messages.sensor_msgs.pointField;
info.fields.MLdataType = 'struct';
info.fields.MaxLen = NaN;
info.fields.MinLen = 0;
[data.is_bigendian, info.is_bigendian] = ros.internal.ros2.messages.ros2.default_type('logical',1,0);
[data.point_step, info.point_step] = ros.internal.ros2.messages.ros2.default_type('uint32',1,0);
[data.row_step, info.row_step] = ros.internal.ros2.messages.ros2.default_type('uint32',1,0);
[data.data, info.data] = ros.internal.ros2.messages.ros2.default_type('uint8',NaN,0);
[data.is_dense, info.is_dense] = ros.internal.ros2.messages.ros2.default_type('logical',1,0);
info.MessageType = 'sensor_msgs/PointCloud2';
info.constant = 0;
info.default = 0;
info.maxstrlen = NaN;
info.MaxLen = 1;
info.MinLen = 1;
info.MatPath = cell(1,25);
info.MatPath{1} = 'header';
info.MatPath{2} = 'header.stamp';
info.MatPath{3} = 'header.stamp.sec';
info.MatPath{4} = 'header.stamp.nanosec';
info.MatPath{5} = 'header.frame_id';
info.MatPath{6} = 'height';
info.MatPath{7} = 'width';
info.MatPath{8} = 'fields';
info.MatPath{9} = 'fields.INT8';
info.MatPath{10} = 'fields.UINT8';
info.MatPath{11} = 'fields.INT16';
info.MatPath{12} = 'fields.UINT16';
info.MatPath{13} = 'fields.INT32';
info.MatPath{14} = 'fields.UINT32';
info.MatPath{15} = 'fields.FLOAT32';
info.MatPath{16} = 'fields.FLOAT64';
info.MatPath{17} = 'fields.name';
info.MatPath{18} = 'fields.offset';
info.MatPath{19} = 'fields.datatype';
info.MatPath{20} = 'fields.count';
info.MatPath{21} = 'is_bigendian';
info.MatPath{22} = 'point_step';
info.MatPath{23} = 'row_step';
info.MatPath{24} = 'data';
info.MatPath{25} = 'is_dense';
