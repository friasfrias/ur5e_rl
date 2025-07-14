cmake_minimum_required(VERSION 3.5)
project(control_msgs)
set(CMAKE_VERBOSE_MAKEFILE ON)
# Set CMAKE_BUILD_TYPE
set(CMAKE_BUILD_TYPE Release)
# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()
# Default to C++17
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()
if(ALIAS_ROS2_TF2)
  add_definitions(-Dtf2=ros2_tf2)
  add_definitions(-Dtf2_ros=ros2_tf2_ros)
  add_definitions(-Dmessage_filters=ros2_message_filters)
endif()
# find dependencies
find_package(ament_cmake REQUIRED)
find_package(ament_cmake_ros REQUIRED)
find_package(rosidl_typesupport_c REQUIRED)
find_package(rosidl_typesupport_cpp REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package(rclcpp_action REQUIRED)
find_package( action_msgs REQUIRED)
find_package( builtin_interfaces REQUIRED)
find_package( class_loader REQUIRED)
find_package( console_bridge REQUIRED)
find_package( geometry_msgs REQUIRED)
find_package( rclcpp REQUIRED)
find_package( rcutils REQUIRED)
find_package( sensor_msgs REQUIRED)
find_package( std_msgs REQUIRED)
find_package( trajectory_msgs REQUIRED)
find_package( unique_identifier_msgs REQUIRED)
include_directories("/usr/local/MATLAB/R2024b/extern/include")
include_directories("/usr/local/MATLAB/R2024b/extern/include/MatlabDataArray")
include_directories("/usr/local/MATLAB/R2024b/toolbox/ros/include/ros2")
include_directories("include/control_msgs")
set (CMAKE_SKIP_BUILD_RPATH false)
set (CMAKE_BUILD_WITH_INSTALL_RPATH true)
set (CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
set (CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
set(msg_files
  "msg/AdmittanceControllerState.msg"
  "msg/DynamicInterfaceGroupValues.msg"
  "msg/DynamicJointState.msg"
  "msg/GripperCommand.msg"
  "msg/InterfaceValue.msg"
  "msg/JointComponentTolerance.msg"
  "msg/JointControllerState.msg"
  "msg/JointJog.msg"
  "msg/JointTolerance.msg"
  "msg/JointTrajectoryControllerState.msg"
  "msg/MecanumDriveControllerState.msg"
  "msg/MultiDOFCommand.msg"
  "msg/MultiDOFStateStamped.msg"
  "msg/PidState.msg"
  "msg/SingleDOFState.msg"
  "msg/SingleDOFStateStamped.msg"
  "msg/SteeringControllerStatus.msg"
)
set(srv_files
  "srv/QueryCalibrationState.srv"
  "srv/QueryTrajectoryState.srv"
)
set(action_files
  "action/FollowJointTrajectory.action"
  "action/GripperCommand.action"
  "action/JointTrajectory.action"
  "action/ParallelGripperCommand.action"
  "action/PointHead.action"
  "action/SingleJointPosition.action"
)
rosidl_generate_interfaces(${PROJECT_NAME}
  ${msg_files}
  ${srv_files}
  ${action_files}
  DEPENDENCIES 
  action_msgs
  builtin_interfaces
  geometry_msgs
  sensor_msgs
  std_msgs
  trajectory_msgs
  unique_identifier_msgs
)
link_directories("/usr/local/MATLAB/R2024b/extern/bin/glnxa64")
# Library
add_library(
    control_msgs_matlab 
    SHARED
    src/control_msgs_AdmittanceControllerState_message.cpp
    src/control_msgs_DynamicInterfaceGroupValues_message.cpp
    src/control_msgs_DynamicJointState_message.cpp
    src/control_msgs_GripperCommand_message.cpp
    src/control_msgs_InterfaceValue_message.cpp
    src/control_msgs_JointComponentTolerance_message.cpp
    src/control_msgs_JointControllerState_message.cpp
    src/control_msgs_JointJog_message.cpp
    src/control_msgs_JointTolerance_message.cpp
    src/control_msgs_JointTrajectoryControllerState_message.cpp
    src/control_msgs_MecanumDriveControllerState_message.cpp
    src/control_msgs_MultiDOFCommand_message.cpp
    src/control_msgs_MultiDOFStateStamped_message.cpp
    src/control_msgs_PidState_message.cpp
    src/control_msgs_SingleDOFState_message.cpp
    src/control_msgs_SingleDOFStateStamped_message.cpp
    src/control_msgs_SteeringControllerStatus_message.cpp
    src/control_msgs_QueryCalibrationState_service.cpp
    src/control_msgs_QueryTrajectoryState_service.cpp
    src/control_msgs_FollowJointTrajectory_action.cpp
    src/control_msgs_GripperCommand_action.cpp
    src/control_msgs_JointTrajectory_action.cpp
    src/control_msgs_ParallelGripperCommand_action.cpp
    src/control_msgs_PointHead_action.cpp
    src/control_msgs_SingleJointPosition_action.cpp
)
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
target_compile_options(control_msgs_matlab PUBLIC 
  $<$<OR:$<COMPILE_LANGUAGE:CXX>,$<COMPILE_LANGUAGE:C>>:
  -Wall -Wextra -Wpedantic
  >)
endif()
target_include_directories(control_msgs_matlab PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
target_link_libraries( control_msgs_matlab
	"/usr/local/MATLAB/R2024b/sys/os/glnxa64/orig/libstdc++.so.6"
	"/usr/local/MATLAB/R2024b/extern/bin/glnxa64/libMatlabDataArray.so"
	"/usr/local/MATLAB/R2024b/sys/ros2/glnxa64/ros2/lib/librclcpp_action.so"
	${CMAKE_DL_LIBS}
	)
ament_target_dependencies(
  control_msgs_matlab
  "action_msgs"
  "builtin_interfaces"
  "class_loader"
  "console_bridge"
  "geometry_msgs"
  "rclcpp"
  "rcutils"
  "sensor_msgs"
  "std_msgs"
  "trajectory_msgs"
  "unique_identifier_msgs"
rclcpp_action
)
rosidl_get_typesupport_target(cpp_typesupport_target "${PROJECT_NAME}" "rosidl_typesupport_cpp")
target_link_libraries(control_msgs_matlab "${cpp_typesupport_target}")
# Causes the visibility macros to use dllexport rather than dllimport,
# which is appropriate when building the dll but not consuming it.
target_compile_definitions(control_msgs_matlab PRIVATE "CONTROL_MSGS_BUILDING_LIBRARY")
install(
  DIRECTORY include/
  DESTINATION include
)
ament_export_targets(export_${PROJECT_NAME} HAS_LIBRARY_TARGET)
ament_export_dependencies(
  action_msgs
  builtin_interfaces
  class_loader
  console_bridge
  geometry_msgs
  rclcpp
  rcutils
  sensor_msgs
  std_msgs
  trajectory_msgs
  unique_identifier_msgs
)
install(
  TARGETS control_msgs_matlab
  EXPORT export_${PROJECT_NAME}
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)
install (DIRECTORY m/ DESTINATION m/ FILES_MATCHING PATTERN "*.m")
ament_export_include_directories(
  include
)
ament_export_libraries(
  control_msgs_matlab
)
foreach(file_i ${CUDA_BINS})
add_custom_command(
                   TARGET 
                   POST_BUILD
                   COMMAND ${CMAKE_COMMAND}
                   ARGS -E copy ${PROJECT_SOURCE_DIR}/src/${file_i} ${CMAKE_INSTALL_PREFIX}/_ert_rtw/${file_i}
				   )
add_custom_command(
                   TARGET 
                   POST_BUILD
                   COMMAND ${CMAKE_COMMAND}
                   ARGS -E copy ${PROJECT_SOURCE_DIR}/src/${file_i} ${CMAKE_INSTALL_PREFIX}/codegen/exe//${file_i}
				   )				   
endforeach(file_i)
ament_package()
# Generated on Sun Jun 29 19:48:46 2025
