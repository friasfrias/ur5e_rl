// Copyright 2022 The MathWorks, Inc.
// Common copy functions for control_msgs/FollowJointTrajectoryGoal
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4100)
#pragma warning(disable : 4265)
#pragma warning(disable : 4456)
#pragma warning(disable : 4458)
#pragma warning(disable : 4946)
#pragma warning(disable : 4244)
#else
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wredundant-decls"
#pragma GCC diagnostic ignored "-Wnon-virtual-dtor"
#pragma GCC diagnostic ignored "-Wdelete-non-virtual-dtor"
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Wshadow"
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif //_MSC_VER
#include "rclcpp/rclcpp.hpp"
#include "control_msgs/action/follow_joint_trajectory.hpp"
#include "visibility_control.h"
#ifndef FOUNDATION_MATLABDATA_API
#include "MDArray.hpp"
#include "StructArray.hpp"
#include "TypedArrayRef.hpp"
#include "Struct.hpp"
#include "ArrayFactory.hpp"
#include "StructRef.hpp"
#include "Reference.hpp"
#endif
#include "class_loader/multi_library_class_loader.hpp"
#include "ROS2PubSubTemplates.hpp"
#include "ROS2ActionTemplates.hpp"
class CONTROL_MSGS_EXPORT control_msgs_msg_FollowJointTrajectoryGoal_common : public MATLABROS2MsgInterface<control_msgs::action::FollowJointTrajectory::Goal> {
  public:
    virtual ~control_msgs_msg_FollowJointTrajectoryGoal_common(){}
    virtual void copy_from_struct(control_msgs::action::FollowJointTrajectory::Goal* msg, const matlab::data::Struct& arr, MultiLibLoader loader); 
    //----------------------------------------------------------------------------
    virtual MDArray_T get_arr(MDFactory_T& factory, const control_msgs::action::FollowJointTrajectory::Goal* msg, MultiLibLoader loader, size_t size = 1);
};
  //----------------------------------------------------------------------------
  void control_msgs_msg_FollowJointTrajectoryGoal_common::copy_from_struct(control_msgs::action::FollowJointTrajectory::Goal* msg, const matlab::data::Struct& arr, MultiLibLoader loader) {
    try {
        //trajectory
        const matlab::data::StructArray trajectory_arr = arr["trajectory"];
        auto msgClassPtr_trajectory = getCommonObject<trajectory_msgs::msg::JointTrajectory>("ros2_trajectory_msgs_msg_JointTrajectory_common",loader);
        msgClassPtr_trajectory->copy_from_struct(&msg->trajectory,trajectory_arr[0],loader);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'trajectory' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'trajectory' is wrong type; expected a struct.");
    }
    try {
        //multi_dof_trajectory
        const matlab::data::StructArray multi_dof_trajectory_arr = arr["multi_dof_trajectory"];
        auto msgClassPtr_multi_dof_trajectory = getCommonObject<trajectory_msgs::msg::MultiDOFJointTrajectory>("ros2_trajectory_msgs_msg_MultiDOFJointTrajectory_common",loader);
        msgClassPtr_multi_dof_trajectory->copy_from_struct(&msg->multi_dof_trajectory,multi_dof_trajectory_arr[0],loader);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'multi_dof_trajectory' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'multi_dof_trajectory' is wrong type; expected a struct.");
    }
    try {
        //path_tolerance
        const matlab::data::StructArray path_tolerance_arr = arr["path_tolerance"];
        for (auto _path_tolerancearr : path_tolerance_arr) {
        	control_msgs::msg::JointTolerance _val;
        auto msgClassPtr_path_tolerance = getCommonObject<control_msgs::msg::JointTolerance>("ros2_control_msgs_msg_JointTolerance_common",loader);
        msgClassPtr_path_tolerance->copy_from_struct(&_val,_path_tolerancearr,loader);
        	msg->path_tolerance.push_back(_val);
        }
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'path_tolerance' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'path_tolerance' is wrong type; expected a struct.");
    }
    try {
        //component_path_tolerance
        const matlab::data::StructArray component_path_tolerance_arr = arr["component_path_tolerance"];
        for (auto _component_path_tolerancearr : component_path_tolerance_arr) {
        	control_msgs::msg::JointComponentTolerance _val;
        auto msgClassPtr_component_path_tolerance = getCommonObject<control_msgs::msg::JointComponentTolerance>("ros2_control_msgs_msg_JointComponentTolerance_common",loader);
        msgClassPtr_component_path_tolerance->copy_from_struct(&_val,_component_path_tolerancearr,loader);
        	msg->component_path_tolerance.push_back(_val);
        }
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'component_path_tolerance' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'component_path_tolerance' is wrong type; expected a struct.");
    }
    try {
        //goal_tolerance
        const matlab::data::StructArray goal_tolerance_arr = arr["goal_tolerance"];
        for (auto _goal_tolerancearr : goal_tolerance_arr) {
        	control_msgs::msg::JointTolerance _val;
        auto msgClassPtr_goal_tolerance = getCommonObject<control_msgs::msg::JointTolerance>("ros2_control_msgs_msg_JointTolerance_common",loader);
        msgClassPtr_goal_tolerance->copy_from_struct(&_val,_goal_tolerancearr,loader);
        	msg->goal_tolerance.push_back(_val);
        }
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'goal_tolerance' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'goal_tolerance' is wrong type; expected a struct.");
    }
    try {
        //component_goal_tolerance
        const matlab::data::StructArray component_goal_tolerance_arr = arr["component_goal_tolerance"];
        for (auto _component_goal_tolerancearr : component_goal_tolerance_arr) {
        	control_msgs::msg::JointComponentTolerance _val;
        auto msgClassPtr_component_goal_tolerance = getCommonObject<control_msgs::msg::JointComponentTolerance>("ros2_control_msgs_msg_JointComponentTolerance_common",loader);
        msgClassPtr_component_goal_tolerance->copy_from_struct(&_val,_component_goal_tolerancearr,loader);
        	msg->component_goal_tolerance.push_back(_val);
        }
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'component_goal_tolerance' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'component_goal_tolerance' is wrong type; expected a struct.");
    }
    try {
        //goal_time_tolerance
        const matlab::data::StructArray goal_time_tolerance_arr = arr["goal_time_tolerance"];
        auto msgClassPtr_goal_time_tolerance = getCommonObject<builtin_interfaces::msg::Duration>("ros2_builtin_interfaces_msg_Duration_common",loader);
        msgClassPtr_goal_time_tolerance->copy_from_struct(&msg->goal_time_tolerance,goal_time_tolerance_arr[0],loader);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'goal_time_tolerance' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'goal_time_tolerance' is wrong type; expected a struct.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T control_msgs_msg_FollowJointTrajectoryGoal_common::get_arr(MDFactory_T& factory, const control_msgs::action::FollowJointTrajectory::Goal* msg,
       MultiLibLoader loader, size_t size) {
    auto outArray = factory.createStructArray({size,1},{"MessageType","trajectory","multi_dof_trajectory","path_tolerance","component_path_tolerance","goal_tolerance","component_goal_tolerance","goal_time_tolerance"});
    for(size_t ctr = 0; ctr < size; ctr++){
    outArray[ctr]["MessageType"] = factory.createCharArray("control_msgs/FollowJointTrajectoryGoal");
    // trajectory
    auto currentElement_trajectory = (msg + ctr)->trajectory;
    auto msgClassPtr_trajectory = getCommonObject<trajectory_msgs::msg::JointTrajectory>("ros2_trajectory_msgs_msg_JointTrajectory_common",loader);
    outArray[ctr]["trajectory"] = msgClassPtr_trajectory->get_arr(factory, &currentElement_trajectory, loader);
    // multi_dof_trajectory
    auto currentElement_multi_dof_trajectory = (msg + ctr)->multi_dof_trajectory;
    auto msgClassPtr_multi_dof_trajectory = getCommonObject<trajectory_msgs::msg::MultiDOFJointTrajectory>("ros2_trajectory_msgs_msg_MultiDOFJointTrajectory_common",loader);
    outArray[ctr]["multi_dof_trajectory"] = msgClassPtr_multi_dof_trajectory->get_arr(factory, &currentElement_multi_dof_trajectory, loader);
    // path_tolerance
    auto currentElement_path_tolerance = (msg + ctr)->path_tolerance;
    auto msgClassPtr_path_tolerance = getCommonObject<control_msgs::msg::JointTolerance>("ros2_control_msgs_msg_JointTolerance_common",loader);
    outArray[ctr]["path_tolerance"] = msgClassPtr_path_tolerance->get_arr(factory,&currentElement_path_tolerance[0],loader,currentElement_path_tolerance.size());
    // component_path_tolerance
    auto currentElement_component_path_tolerance = (msg + ctr)->component_path_tolerance;
    auto msgClassPtr_component_path_tolerance = getCommonObject<control_msgs::msg::JointComponentTolerance>("ros2_control_msgs_msg_JointComponentTolerance_common",loader);
    outArray[ctr]["component_path_tolerance"] = msgClassPtr_component_path_tolerance->get_arr(factory,&currentElement_component_path_tolerance[0],loader,currentElement_component_path_tolerance.size());
    // goal_tolerance
    auto currentElement_goal_tolerance = (msg + ctr)->goal_tolerance;
    auto msgClassPtr_goal_tolerance = getCommonObject<control_msgs::msg::JointTolerance>("ros2_control_msgs_msg_JointTolerance_common",loader);
    outArray[ctr]["goal_tolerance"] = msgClassPtr_goal_tolerance->get_arr(factory,&currentElement_goal_tolerance[0],loader,currentElement_goal_tolerance.size());
    // component_goal_tolerance
    auto currentElement_component_goal_tolerance = (msg + ctr)->component_goal_tolerance;
    auto msgClassPtr_component_goal_tolerance = getCommonObject<control_msgs::msg::JointComponentTolerance>("ros2_control_msgs_msg_JointComponentTolerance_common",loader);
    outArray[ctr]["component_goal_tolerance"] = msgClassPtr_component_goal_tolerance->get_arr(factory,&currentElement_component_goal_tolerance[0],loader,currentElement_component_goal_tolerance.size());
    // goal_time_tolerance
    auto currentElement_goal_time_tolerance = (msg + ctr)->goal_time_tolerance;
    auto msgClassPtr_goal_time_tolerance = getCommonObject<builtin_interfaces::msg::Duration>("ros2_builtin_interfaces_msg_Duration_common",loader);
    outArray[ctr]["goal_time_tolerance"] = msgClassPtr_goal_time_tolerance->get_arr(factory, &currentElement_goal_time_tolerance, loader);
    }
    return std::move(outArray);
  }

class CONTROL_MSGS_EXPORT control_msgs_msg_FollowJointTrajectoryResult_common : public MATLABROS2MsgInterface<control_msgs::action::FollowJointTrajectory::Result> {
  public:
    virtual ~control_msgs_msg_FollowJointTrajectoryResult_common(){}
    virtual void copy_from_struct(control_msgs::action::FollowJointTrajectory::Result* msg, const matlab::data::Struct& arr, MultiLibLoader loader); 
    //----------------------------------------------------------------------------
    virtual MDArray_T get_arr(MDFactory_T& factory, const control_msgs::action::FollowJointTrajectory::Result* msg, MultiLibLoader loader, size_t size = 1);
};
  //----------------------------------------------------------------------------
  void control_msgs_msg_FollowJointTrajectoryResult_common::copy_from_struct(control_msgs::action::FollowJointTrajectory::Result* msg, const matlab::data::Struct& arr, MultiLibLoader loader) {
    try {
        //error_code
        const matlab::data::TypedArray<int32_t> error_code_arr = arr["error_code"];
        msg->error_code = error_code_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'error_code' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'error_code' is wrong type; expected a int32.");
    }
    try {
        //error_string
        const matlab::data::CharArray error_string_arr = arr["error_string"];
        msg->error_string = error_string_arr.toAscii();
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'error_string' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'error_string' is wrong type; expected a string.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T control_msgs_msg_FollowJointTrajectoryResult_common::get_arr(MDFactory_T& factory, const control_msgs::action::FollowJointTrajectory::Result* msg,
       MultiLibLoader loader, size_t size) {
    auto outArray = factory.createStructArray({size,1},{"MessageType","error_code","SUCCESSFUL","INVALID_GOAL","INVALID_JOINTS","OLD_HEADER_TIMESTAMP","PATH_TOLERANCE_VIOLATED","GOAL_TOLERANCE_VIOLATED","error_string"});
    for(size_t ctr = 0; ctr < size; ctr++){
    outArray[ctr]["MessageType"] = factory.createCharArray("control_msgs/FollowJointTrajectoryResult");
    // error_code
    auto currentElement_error_code = (msg + ctr)->error_code;
    outArray[ctr]["error_code"] = factory.createScalar(currentElement_error_code);
    // SUCCESSFUL
    auto currentElement_SUCCESSFUL = (msg + ctr)->SUCCESSFUL;
    outArray[ctr]["SUCCESSFUL"] = factory.createScalar(currentElement_SUCCESSFUL);
    // INVALID_GOAL
    auto currentElement_INVALID_GOAL = (msg + ctr)->INVALID_GOAL;
    outArray[ctr]["INVALID_GOAL"] = factory.createScalar(currentElement_INVALID_GOAL);
    // INVALID_JOINTS
    auto currentElement_INVALID_JOINTS = (msg + ctr)->INVALID_JOINTS;
    outArray[ctr]["INVALID_JOINTS"] = factory.createScalar(currentElement_INVALID_JOINTS);
    // OLD_HEADER_TIMESTAMP
    auto currentElement_OLD_HEADER_TIMESTAMP = (msg + ctr)->OLD_HEADER_TIMESTAMP;
    outArray[ctr]["OLD_HEADER_TIMESTAMP"] = factory.createScalar(currentElement_OLD_HEADER_TIMESTAMP);
    // PATH_TOLERANCE_VIOLATED
    auto currentElement_PATH_TOLERANCE_VIOLATED = (msg + ctr)->PATH_TOLERANCE_VIOLATED;
    outArray[ctr]["PATH_TOLERANCE_VIOLATED"] = factory.createScalar(currentElement_PATH_TOLERANCE_VIOLATED);
    // GOAL_TOLERANCE_VIOLATED
    auto currentElement_GOAL_TOLERANCE_VIOLATED = (msg + ctr)->GOAL_TOLERANCE_VIOLATED;
    outArray[ctr]["GOAL_TOLERANCE_VIOLATED"] = factory.createScalar(currentElement_GOAL_TOLERANCE_VIOLATED);
    // error_string
    auto currentElement_error_string = (msg + ctr)->error_string;
    outArray[ctr]["error_string"] = factory.createCharArray(currentElement_error_string);
    }
    return std::move(outArray);
  }

class CONTROL_MSGS_EXPORT control_msgs_msg_FollowJointTrajectoryFeedback_common : public MATLABROS2MsgInterface<control_msgs::action::FollowJointTrajectory::Feedback> {
  public:
    virtual ~control_msgs_msg_FollowJointTrajectoryFeedback_common(){}
    virtual void copy_from_struct(control_msgs::action::FollowJointTrajectory::Feedback* msg, const matlab::data::Struct& arr, MultiLibLoader loader); 
    //----------------------------------------------------------------------------
    virtual MDArray_T get_arr(MDFactory_T& factory, const control_msgs::action::FollowJointTrajectory::Feedback* msg, MultiLibLoader loader, size_t size = 1);
};
  //----------------------------------------------------------------------------
  void control_msgs_msg_FollowJointTrajectoryFeedback_common::copy_from_struct(control_msgs::action::FollowJointTrajectory::Feedback* msg, const matlab::data::Struct& arr, MultiLibLoader loader) {
    try {
        //header
        const matlab::data::StructArray header_arr = arr["header"];
        auto msgClassPtr_header = getCommonObject<std_msgs::msg::Header>("ros2_std_msgs_msg_Header_common",loader);
        msgClassPtr_header->copy_from_struct(&msg->header,header_arr[0],loader);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'header' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'header' is wrong type; expected a struct.");
    }
    try {
        //joint_names
        const matlab::data::CellArray joint_names_cellarr = arr["joint_names"];
        size_t nelem = joint_names_cellarr.getNumberOfElements();
        for (size_t idx=0; idx < nelem; ++idx){
        	const matlab::data::CharArray joint_names_arr = joint_names_cellarr[idx];
        	msg->joint_names.push_back(joint_names_arr.toAscii());
        }
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'joint_names' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'joint_names' is wrong type; expected a string.");
    }
    try {
        //desired
        const matlab::data::StructArray desired_arr = arr["desired"];
        auto msgClassPtr_desired = getCommonObject<trajectory_msgs::msg::JointTrajectoryPoint>("ros2_trajectory_msgs_msg_JointTrajectoryPoint_common",loader);
        msgClassPtr_desired->copy_from_struct(&msg->desired,desired_arr[0],loader);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'desired' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'desired' is wrong type; expected a struct.");
    }
    try {
        //actual
        const matlab::data::StructArray actual_arr = arr["actual"];
        auto msgClassPtr_actual = getCommonObject<trajectory_msgs::msg::JointTrajectoryPoint>("ros2_trajectory_msgs_msg_JointTrajectoryPoint_common",loader);
        msgClassPtr_actual->copy_from_struct(&msg->actual,actual_arr[0],loader);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'actual' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'actual' is wrong type; expected a struct.");
    }
    try {
        //error
        const matlab::data::StructArray error_arr = arr["error"];
        auto msgClassPtr_error = getCommonObject<trajectory_msgs::msg::JointTrajectoryPoint>("ros2_trajectory_msgs_msg_JointTrajectoryPoint_common",loader);
        msgClassPtr_error->copy_from_struct(&msg->error,error_arr[0],loader);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'error' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'error' is wrong type; expected a struct.");
    }
    try {
        //multi_dof_joint_names
        const matlab::data::CellArray multi_dof_joint_names_cellarr = arr["multi_dof_joint_names"];
        size_t nelem = multi_dof_joint_names_cellarr.getNumberOfElements();
        for (size_t idx=0; idx < nelem; ++idx){
        	const matlab::data::CharArray multi_dof_joint_names_arr = multi_dof_joint_names_cellarr[idx];
        	msg->multi_dof_joint_names.push_back(multi_dof_joint_names_arr.toAscii());
        }
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'multi_dof_joint_names' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'multi_dof_joint_names' is wrong type; expected a string.");
    }
    try {
        //multi_dof_desired
        const matlab::data::StructArray multi_dof_desired_arr = arr["multi_dof_desired"];
        auto msgClassPtr_multi_dof_desired = getCommonObject<trajectory_msgs::msg::MultiDOFJointTrajectoryPoint>("ros2_trajectory_msgs_msg_MultiDOFJointTrajectoryPoint_common",loader);
        msgClassPtr_multi_dof_desired->copy_from_struct(&msg->multi_dof_desired,multi_dof_desired_arr[0],loader);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'multi_dof_desired' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'multi_dof_desired' is wrong type; expected a struct.");
    }
    try {
        //multi_dof_actual
        const matlab::data::StructArray multi_dof_actual_arr = arr["multi_dof_actual"];
        auto msgClassPtr_multi_dof_actual = getCommonObject<trajectory_msgs::msg::MultiDOFJointTrajectoryPoint>("ros2_trajectory_msgs_msg_MultiDOFJointTrajectoryPoint_common",loader);
        msgClassPtr_multi_dof_actual->copy_from_struct(&msg->multi_dof_actual,multi_dof_actual_arr[0],loader);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'multi_dof_actual' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'multi_dof_actual' is wrong type; expected a struct.");
    }
    try {
        //multi_dof_error
        const matlab::data::StructArray multi_dof_error_arr = arr["multi_dof_error"];
        auto msgClassPtr_multi_dof_error = getCommonObject<trajectory_msgs::msg::MultiDOFJointTrajectoryPoint>("ros2_trajectory_msgs_msg_MultiDOFJointTrajectoryPoint_common",loader);
        msgClassPtr_multi_dof_error->copy_from_struct(&msg->multi_dof_error,multi_dof_error_arr[0],loader);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'multi_dof_error' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'multi_dof_error' is wrong type; expected a struct.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T control_msgs_msg_FollowJointTrajectoryFeedback_common::get_arr(MDFactory_T& factory, const control_msgs::action::FollowJointTrajectory::Feedback* msg,
       MultiLibLoader loader, size_t size) {
    auto outArray = factory.createStructArray({size,1},{"MessageType","header","joint_names","desired","actual","error","multi_dof_joint_names","multi_dof_desired","multi_dof_actual","multi_dof_error"});
    for(size_t ctr = 0; ctr < size; ctr++){
    outArray[ctr]["MessageType"] = factory.createCharArray("control_msgs/FollowJointTrajectoryFeedback");
    // header
    auto currentElement_header = (msg + ctr)->header;
    auto msgClassPtr_header = getCommonObject<std_msgs::msg::Header>("ros2_std_msgs_msg_Header_common",loader);
    outArray[ctr]["header"] = msgClassPtr_header->get_arr(factory, &currentElement_header, loader);
    // joint_names
    auto currentElement_joint_names = (msg + ctr)->joint_names;
    auto joint_namesoutCell = factory.createCellArray({currentElement_joint_names.size(),1});
    for(size_t idxin = 0; idxin < currentElement_joint_names.size(); ++ idxin){
    	joint_namesoutCell[idxin] = factory.createCharArray(currentElement_joint_names[idxin]);
    }
    outArray[ctr]["joint_names"] = joint_namesoutCell;
    // desired
    auto currentElement_desired = (msg + ctr)->desired;
    auto msgClassPtr_desired = getCommonObject<trajectory_msgs::msg::JointTrajectoryPoint>("ros2_trajectory_msgs_msg_JointTrajectoryPoint_common",loader);
    outArray[ctr]["desired"] = msgClassPtr_desired->get_arr(factory, &currentElement_desired, loader);
    // actual
    auto currentElement_actual = (msg + ctr)->actual;
    auto msgClassPtr_actual = getCommonObject<trajectory_msgs::msg::JointTrajectoryPoint>("ros2_trajectory_msgs_msg_JointTrajectoryPoint_common",loader);
    outArray[ctr]["actual"] = msgClassPtr_actual->get_arr(factory, &currentElement_actual, loader);
    // error
    auto currentElement_error = (msg + ctr)->error;
    auto msgClassPtr_error = getCommonObject<trajectory_msgs::msg::JointTrajectoryPoint>("ros2_trajectory_msgs_msg_JointTrajectoryPoint_common",loader);
    outArray[ctr]["error"] = msgClassPtr_error->get_arr(factory, &currentElement_error, loader);
    // multi_dof_joint_names
    auto currentElement_multi_dof_joint_names = (msg + ctr)->multi_dof_joint_names;
    auto multi_dof_joint_namesoutCell = factory.createCellArray({currentElement_multi_dof_joint_names.size(),1});
    for(size_t idxin = 0; idxin < currentElement_multi_dof_joint_names.size(); ++ idxin){
    	multi_dof_joint_namesoutCell[idxin] = factory.createCharArray(currentElement_multi_dof_joint_names[idxin]);
    }
    outArray[ctr]["multi_dof_joint_names"] = multi_dof_joint_namesoutCell;
    // multi_dof_desired
    auto currentElement_multi_dof_desired = (msg + ctr)->multi_dof_desired;
    auto msgClassPtr_multi_dof_desired = getCommonObject<trajectory_msgs::msg::MultiDOFJointTrajectoryPoint>("ros2_trajectory_msgs_msg_MultiDOFJointTrajectoryPoint_common",loader);
    outArray[ctr]["multi_dof_desired"] = msgClassPtr_multi_dof_desired->get_arr(factory, &currentElement_multi_dof_desired, loader);
    // multi_dof_actual
    auto currentElement_multi_dof_actual = (msg + ctr)->multi_dof_actual;
    auto msgClassPtr_multi_dof_actual = getCommonObject<trajectory_msgs::msg::MultiDOFJointTrajectoryPoint>("ros2_trajectory_msgs_msg_MultiDOFJointTrajectoryPoint_common",loader);
    outArray[ctr]["multi_dof_actual"] = msgClassPtr_multi_dof_actual->get_arr(factory, &currentElement_multi_dof_actual, loader);
    // multi_dof_error
    auto currentElement_multi_dof_error = (msg + ctr)->multi_dof_error;
    auto msgClassPtr_multi_dof_error = getCommonObject<trajectory_msgs::msg::MultiDOFJointTrajectoryPoint>("ros2_trajectory_msgs_msg_MultiDOFJointTrajectoryPoint_common",loader);
    outArray[ctr]["multi_dof_error"] = msgClassPtr_multi_dof_error->get_arr(factory, &currentElement_multi_dof_error, loader);
    }
    return std::move(outArray);
  }

class CONTROL_MSGS_EXPORT ros2_control_msgs_FollowJointTrajectory_action : public ROS2MsgElementInterfaceFactory {
  public:
    virtual ~ros2_control_msgs_FollowJointTrajectory_action(){}
    virtual std::shared_ptr<MATLABPublisherInterface> generatePublisherInterface(ElementType type);
    virtual std::shared_ptr<MATLABSubscriberInterface> generateSubscriberInterface(ElementType type);
    virtual std::shared_ptr<MATLABActClientInterface> generateActClientInterface();
    virtual std::shared_ptr<MATLABActServerInterface> generateActServerInterface();
    virtual matlab::data::StructArray generateMLMessage(ElementType type, 
                                                    void*  msgPtr ,
                                                    MultiLibLoader  loader ,
                                                    std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* commonObjMap);
    virtual std::shared_ptr<void> generateCppMessage(ElementType type, 
                                           const matlab::data::StructArray& arr,
                                           MultiLibLoader loader,
                                           std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* commonObjMap);
};  
  std::shared_ptr<MATLABPublisherInterface> 
          ros2_control_msgs_FollowJointTrajectory_action::generatePublisherInterface(ElementType type){
    std::shared_ptr<MATLABPublisherInterface> ptr;
    if(type == eGoal){
        ptr = std::make_shared<ROS2PublisherImpl<control_msgs::action::FollowJointTrajectory::Goal,control_msgs_msg_FollowJointTrajectoryGoal_common>>();
    }else if(type == eFeedback){
        ptr = std::make_shared<ROS2PublisherImpl<control_msgs::action::FollowJointTrajectory::Feedback,control_msgs_msg_FollowJointTrajectoryFeedback_common>>();
    }else if(type == eResult){
        ptr = std::make_shared<ROS2PublisherImpl<control_msgs::action::FollowJointTrajectory::Result,control_msgs_msg_FollowJointTrajectoryResult_common>>();
    }else{
        throw std::invalid_argument("Wrong input, Expected 'Goal' or 'Feedback' or 'Result'");
    }
    return ptr;
  }
  std::shared_ptr<MATLABSubscriberInterface> 
         ros2_control_msgs_FollowJointTrajectory_action::generateSubscriberInterface(ElementType type){
    std::shared_ptr<MATLABSubscriberInterface> ptr;
    if(type == eGoal){
        ptr = std::make_shared<ROS2SubscriberImpl<control_msgs::action::FollowJointTrajectory::Goal,control_msgs_msg_FollowJointTrajectoryGoal_common>>();
    }else if(type == eFeedback){
        ptr = std::make_shared<ROS2SubscriberImpl<control_msgs::action::FollowJointTrajectory::Feedback,control_msgs_msg_FollowJointTrajectoryFeedback_common>>();
    }else if(type == eResult){
        ptr = std::make_shared<ROS2SubscriberImpl<control_msgs::action::FollowJointTrajectory::Result,control_msgs_msg_FollowJointTrajectoryResult_common>>();
    }else{
        throw std::invalid_argument("Wrong input, Expected 'Goal' or 'Feedback' or 'Result'");
    }
    return ptr;
  }
  std::shared_ptr<MATLABActClientInterface> 
          ros2_control_msgs_FollowJointTrajectory_action::generateActClientInterface(){
      return std::make_shared<ROS2ActClientImpl<control_msgs::action::FollowJointTrajectory,control_msgs::action::FollowJointTrajectory::Goal,control_msgs::action::FollowJointTrajectory::Feedback::ConstSharedPtr,control_msgs::action::FollowJointTrajectory::Result::ConstSharedPtr,control_msgs_msg_FollowJointTrajectoryGoal_common,control_msgs_msg_FollowJointTrajectoryFeedback_common,control_msgs_msg_FollowJointTrajectoryResult_common>>();
  }
  std::shared_ptr<MATLABActServerInterface> 
          ros2_control_msgs_FollowJointTrajectory_action::generateActServerInterface(){
      return std::make_shared<ROS2ActServerImpl<control_msgs::action::FollowJointTrajectory,control_msgs::action::FollowJointTrajectory::Feedback,control_msgs::action::FollowJointTrajectory::Result,control_msgs::action::FollowJointTrajectory::Goal::ConstSharedPtr,control_msgs_msg_FollowJointTrajectoryGoal_common,control_msgs_msg_FollowJointTrajectoryFeedback_common,control_msgs_msg_FollowJointTrajectoryResult_common>>();
  }
  std::shared_ptr<void> ros2_control_msgs_FollowJointTrajectory_action::generateCppMessage(ElementType type, 
                                           const matlab::data::StructArray& arr,
                                           MultiLibLoader loader,
                                           std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* commonObjMap){
    if(type == eGoal){
        auto msg = std::make_shared<control_msgs::action::FollowJointTrajectory::Goal>();
        control_msgs_msg_FollowJointTrajectoryGoal_common commonObj;
        commonObj.mCommonObjMap = commonObjMap;
        commonObj.copy_from_struct(msg.get(), arr[0], loader);
        return msg;
    }else if(type == eFeedback){
        auto msg = std::make_shared<control_msgs::action::FollowJointTrajectory::Feedback>();
        control_msgs_msg_FollowJointTrajectoryFeedback_common commonObj;
        commonObj.mCommonObjMap = commonObjMap;
        commonObj.copy_from_struct(msg.get(), arr[0], loader);
        return msg;
    }else if(type == eResult){
        auto msg = std::make_shared<control_msgs::action::FollowJointTrajectory::Result>();
        control_msgs_msg_FollowJointTrajectoryResult_common commonObj;
        commonObj.mCommonObjMap = commonObjMap;
        commonObj.copy_from_struct(msg.get(), arr[0], loader);
        return msg;
   }else{
        throw std::invalid_argument("Wrong input, Expected 'Goal' or 'Feedback' or 'Result'");
    }
  }
 matlab::data::StructArray ros2_control_msgs_FollowJointTrajectory_action::generateMLMessage(ElementType type, 
                                                    void*  msgPtr ,
                                                    MultiLibLoader  loader ,
                                                    std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* commonObjMap){
    if(type == eGoal){
	    control_msgs_msg_FollowJointTrajectoryGoal_common commonObj;	
        commonObj.mCommonObjMap = commonObjMap;
	    MDFactory_T factory;
	    return commonObj.get_arr(factory, (control_msgs::action::FollowJointTrajectory::Goal*)msgPtr, loader);
    }else if(type == eResult){
        control_msgs_msg_FollowJointTrajectoryResult_common commonObj;	
        commonObj.mCommonObjMap = commonObjMap;
	    MDFactory_T factory;
	    return commonObj.get_arr(factory, (control_msgs::action::FollowJointTrajectory::Result*)msgPtr, loader);
    }else if(type == eFeedback){
        control_msgs_msg_FollowJointTrajectoryFeedback_common commonObj;
        commonObj.mCommonObjMap = commonObjMap;
	    MDFactory_T factory;
	    return commonObj.get_arr(factory, (control_msgs::action::FollowJointTrajectory::Feedback*)msgPtr, loader);
    }
     else{
        throw std::invalid_argument("Wrong input, Expected 'Goal' or 'Feedback' or 'Result'");
    }
  }
#include "class_loader/register_macro.hpp"
// Register the component with class_loader.
// This acts as a sort of entry point, allowing the component to be discoverable when its library
// is being loaded into a running process.
CLASS_LOADER_REGISTER_CLASS(control_msgs_msg_FollowJointTrajectoryGoal_common, MATLABROS2MsgInterface<control_msgs::action::FollowJointTrajectory::Goal>)
CLASS_LOADER_REGISTER_CLASS(control_msgs_msg_FollowJointTrajectoryFeedback_common, MATLABROS2MsgInterface<control_msgs::action::FollowJointTrajectory::Feedback>)
CLASS_LOADER_REGISTER_CLASS(control_msgs_msg_FollowJointTrajectoryResult_common, MATLABROS2MsgInterface<control_msgs::action::FollowJointTrajectory::Result>)
CLASS_LOADER_REGISTER_CLASS(ros2_control_msgs_FollowJointTrajectory_action, ROS2MsgElementInterfaceFactory)
#ifdef _MSC_VER
#pragma warning(pop)
#else
#pragma GCC diagnostic pop
#endif //_MSC_VER
//gen-1