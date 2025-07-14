// Copyright 2022 The MathWorks, Inc.
// Common copy functions for control_msgs/ParallelGripperCommandGoal
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
#include "control_msgs/action/parallel_gripper_command.hpp"
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
class CONTROL_MSGS_EXPORT control_msgs_msg_ParallelGripperCommandGoal_common : public MATLABROS2MsgInterface<control_msgs::action::ParallelGripperCommand::Goal> {
  public:
    virtual ~control_msgs_msg_ParallelGripperCommandGoal_common(){}
    virtual void copy_from_struct(control_msgs::action::ParallelGripperCommand::Goal* msg, const matlab::data::Struct& arr, MultiLibLoader loader); 
    //----------------------------------------------------------------------------
    virtual MDArray_T get_arr(MDFactory_T& factory, const control_msgs::action::ParallelGripperCommand::Goal* msg, MultiLibLoader loader, size_t size = 1);
};
  //----------------------------------------------------------------------------
  void control_msgs_msg_ParallelGripperCommandGoal_common::copy_from_struct(control_msgs::action::ParallelGripperCommand::Goal* msg, const matlab::data::Struct& arr, MultiLibLoader loader) {
    try {
        //command
        const matlab::data::StructArray command_arr = arr["command"];
        auto msgClassPtr_command = getCommonObject<sensor_msgs::msg::JointState>("ros2_sensor_msgs_msg_JointState_common",loader);
        msgClassPtr_command->copy_from_struct(&msg->command,command_arr[0],loader);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'command' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'command' is wrong type; expected a struct.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T control_msgs_msg_ParallelGripperCommandGoal_common::get_arr(MDFactory_T& factory, const control_msgs::action::ParallelGripperCommand::Goal* msg,
       MultiLibLoader loader, size_t size) {
    auto outArray = factory.createStructArray({size,1},{"MessageType","command"});
    for(size_t ctr = 0; ctr < size; ctr++){
    outArray[ctr]["MessageType"] = factory.createCharArray("control_msgs/ParallelGripperCommandGoal");
    // command
    auto currentElement_command = (msg + ctr)->command;
    auto msgClassPtr_command = getCommonObject<sensor_msgs::msg::JointState>("ros2_sensor_msgs_msg_JointState_common",loader);
    outArray[ctr]["command"] = msgClassPtr_command->get_arr(factory, &currentElement_command, loader);
    }
    return std::move(outArray);
  }

class CONTROL_MSGS_EXPORT control_msgs_msg_ParallelGripperCommandResult_common : public MATLABROS2MsgInterface<control_msgs::action::ParallelGripperCommand::Result> {
  public:
    virtual ~control_msgs_msg_ParallelGripperCommandResult_common(){}
    virtual void copy_from_struct(control_msgs::action::ParallelGripperCommand::Result* msg, const matlab::data::Struct& arr, MultiLibLoader loader); 
    //----------------------------------------------------------------------------
    virtual MDArray_T get_arr(MDFactory_T& factory, const control_msgs::action::ParallelGripperCommand::Result* msg, MultiLibLoader loader, size_t size = 1);
};
  //----------------------------------------------------------------------------
  void control_msgs_msg_ParallelGripperCommandResult_common::copy_from_struct(control_msgs::action::ParallelGripperCommand::Result* msg, const matlab::data::Struct& arr, MultiLibLoader loader) {
    try {
        //state
        const matlab::data::StructArray state_arr = arr["state"];
        auto msgClassPtr_state = getCommonObject<sensor_msgs::msg::JointState>("ros2_sensor_msgs_msg_JointState_common",loader);
        msgClassPtr_state->copy_from_struct(&msg->state,state_arr[0],loader);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'state' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'state' is wrong type; expected a struct.");
    }
    try {
        //stalled
        const matlab::data::TypedArray<bool> stalled_arr = arr["stalled"];
        msg->stalled = stalled_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'stalled' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'stalled' is wrong type; expected a logical.");
    }
    try {
        //reached_goal
        const matlab::data::TypedArray<bool> reached_goal_arr = arr["reached_goal"];
        msg->reached_goal = reached_goal_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'reached_goal' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'reached_goal' is wrong type; expected a logical.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T control_msgs_msg_ParallelGripperCommandResult_common::get_arr(MDFactory_T& factory, const control_msgs::action::ParallelGripperCommand::Result* msg,
       MultiLibLoader loader, size_t size) {
    auto outArray = factory.createStructArray({size,1},{"MessageType","state","stalled","reached_goal"});
    for(size_t ctr = 0; ctr < size; ctr++){
    outArray[ctr]["MessageType"] = factory.createCharArray("control_msgs/ParallelGripperCommandResult");
    // state
    auto currentElement_state = (msg + ctr)->state;
    auto msgClassPtr_state = getCommonObject<sensor_msgs::msg::JointState>("ros2_sensor_msgs_msg_JointState_common",loader);
    outArray[ctr]["state"] = msgClassPtr_state->get_arr(factory, &currentElement_state, loader);
    // stalled
    auto currentElement_stalled = (msg + ctr)->stalled;
    outArray[ctr]["stalled"] = factory.createScalar(currentElement_stalled);
    // reached_goal
    auto currentElement_reached_goal = (msg + ctr)->reached_goal;
    outArray[ctr]["reached_goal"] = factory.createScalar(currentElement_reached_goal);
    }
    return std::move(outArray);
  }

class CONTROL_MSGS_EXPORT control_msgs_msg_ParallelGripperCommandFeedback_common : public MATLABROS2MsgInterface<control_msgs::action::ParallelGripperCommand::Feedback> {
  public:
    virtual ~control_msgs_msg_ParallelGripperCommandFeedback_common(){}
    virtual void copy_from_struct(control_msgs::action::ParallelGripperCommand::Feedback* msg, const matlab::data::Struct& arr, MultiLibLoader loader); 
    //----------------------------------------------------------------------------
    virtual MDArray_T get_arr(MDFactory_T& factory, const control_msgs::action::ParallelGripperCommand::Feedback* msg, MultiLibLoader loader, size_t size = 1);
};
  //----------------------------------------------------------------------------
  void control_msgs_msg_ParallelGripperCommandFeedback_common::copy_from_struct(control_msgs::action::ParallelGripperCommand::Feedback* msg, const matlab::data::Struct& arr, MultiLibLoader loader) {
    try {
        //state
        const matlab::data::StructArray state_arr = arr["state"];
        auto msgClassPtr_state = getCommonObject<sensor_msgs::msg::JointState>("ros2_sensor_msgs_msg_JointState_common",loader);
        msgClassPtr_state->copy_from_struct(&msg->state,state_arr[0],loader);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'state' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'state' is wrong type; expected a struct.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T control_msgs_msg_ParallelGripperCommandFeedback_common::get_arr(MDFactory_T& factory, const control_msgs::action::ParallelGripperCommand::Feedback* msg,
       MultiLibLoader loader, size_t size) {
    auto outArray = factory.createStructArray({size,1},{"MessageType","state"});
    for(size_t ctr = 0; ctr < size; ctr++){
    outArray[ctr]["MessageType"] = factory.createCharArray("control_msgs/ParallelGripperCommandFeedback");
    // state
    auto currentElement_state = (msg + ctr)->state;
    auto msgClassPtr_state = getCommonObject<sensor_msgs::msg::JointState>("ros2_sensor_msgs_msg_JointState_common",loader);
    outArray[ctr]["state"] = msgClassPtr_state->get_arr(factory, &currentElement_state, loader);
    }
    return std::move(outArray);
  }

class CONTROL_MSGS_EXPORT ros2_control_msgs_ParallelGripperCommand_action : public ROS2MsgElementInterfaceFactory {
  public:
    virtual ~ros2_control_msgs_ParallelGripperCommand_action(){}
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
          ros2_control_msgs_ParallelGripperCommand_action::generatePublisherInterface(ElementType type){
    std::shared_ptr<MATLABPublisherInterface> ptr;
    if(type == eGoal){
        ptr = std::make_shared<ROS2PublisherImpl<control_msgs::action::ParallelGripperCommand::Goal,control_msgs_msg_ParallelGripperCommandGoal_common>>();
    }else if(type == eFeedback){
        ptr = std::make_shared<ROS2PublisherImpl<control_msgs::action::ParallelGripperCommand::Feedback,control_msgs_msg_ParallelGripperCommandFeedback_common>>();
    }else if(type == eResult){
        ptr = std::make_shared<ROS2PublisherImpl<control_msgs::action::ParallelGripperCommand::Result,control_msgs_msg_ParallelGripperCommandResult_common>>();
    }else{
        throw std::invalid_argument("Wrong input, Expected 'Goal' or 'Feedback' or 'Result'");
    }
    return ptr;
  }
  std::shared_ptr<MATLABSubscriberInterface> 
         ros2_control_msgs_ParallelGripperCommand_action::generateSubscriberInterface(ElementType type){
    std::shared_ptr<MATLABSubscriberInterface> ptr;
    if(type == eGoal){
        ptr = std::make_shared<ROS2SubscriberImpl<control_msgs::action::ParallelGripperCommand::Goal,control_msgs_msg_ParallelGripperCommandGoal_common>>();
    }else if(type == eFeedback){
        ptr = std::make_shared<ROS2SubscriberImpl<control_msgs::action::ParallelGripperCommand::Feedback,control_msgs_msg_ParallelGripperCommandFeedback_common>>();
    }else if(type == eResult){
        ptr = std::make_shared<ROS2SubscriberImpl<control_msgs::action::ParallelGripperCommand::Result,control_msgs_msg_ParallelGripperCommandResult_common>>();
    }else{
        throw std::invalid_argument("Wrong input, Expected 'Goal' or 'Feedback' or 'Result'");
    }
    return ptr;
  }
  std::shared_ptr<MATLABActClientInterface> 
          ros2_control_msgs_ParallelGripperCommand_action::generateActClientInterface(){
      return std::make_shared<ROS2ActClientImpl<control_msgs::action::ParallelGripperCommand,control_msgs::action::ParallelGripperCommand::Goal,control_msgs::action::ParallelGripperCommand::Feedback::ConstSharedPtr,control_msgs::action::ParallelGripperCommand::Result::ConstSharedPtr,control_msgs_msg_ParallelGripperCommandGoal_common,control_msgs_msg_ParallelGripperCommandFeedback_common,control_msgs_msg_ParallelGripperCommandResult_common>>();
  }
  std::shared_ptr<MATLABActServerInterface> 
          ros2_control_msgs_ParallelGripperCommand_action::generateActServerInterface(){
      return std::make_shared<ROS2ActServerImpl<control_msgs::action::ParallelGripperCommand,control_msgs::action::ParallelGripperCommand::Feedback,control_msgs::action::ParallelGripperCommand::Result,control_msgs::action::ParallelGripperCommand::Goal::ConstSharedPtr,control_msgs_msg_ParallelGripperCommandGoal_common,control_msgs_msg_ParallelGripperCommandFeedback_common,control_msgs_msg_ParallelGripperCommandResult_common>>();
  }
  std::shared_ptr<void> ros2_control_msgs_ParallelGripperCommand_action::generateCppMessage(ElementType type, 
                                           const matlab::data::StructArray& arr,
                                           MultiLibLoader loader,
                                           std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* commonObjMap){
    if(type == eGoal){
        auto msg = std::make_shared<control_msgs::action::ParallelGripperCommand::Goal>();
        control_msgs_msg_ParallelGripperCommandGoal_common commonObj;
        commonObj.mCommonObjMap = commonObjMap;
        commonObj.copy_from_struct(msg.get(), arr[0], loader);
        return msg;
    }else if(type == eFeedback){
        auto msg = std::make_shared<control_msgs::action::ParallelGripperCommand::Feedback>();
        control_msgs_msg_ParallelGripperCommandFeedback_common commonObj;
        commonObj.mCommonObjMap = commonObjMap;
        commonObj.copy_from_struct(msg.get(), arr[0], loader);
        return msg;
    }else if(type == eResult){
        auto msg = std::make_shared<control_msgs::action::ParallelGripperCommand::Result>();
        control_msgs_msg_ParallelGripperCommandResult_common commonObj;
        commonObj.mCommonObjMap = commonObjMap;
        commonObj.copy_from_struct(msg.get(), arr[0], loader);
        return msg;
   }else{
        throw std::invalid_argument("Wrong input, Expected 'Goal' or 'Feedback' or 'Result'");
    }
  }
 matlab::data::StructArray ros2_control_msgs_ParallelGripperCommand_action::generateMLMessage(ElementType type, 
                                                    void*  msgPtr ,
                                                    MultiLibLoader  loader ,
                                                    std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* commonObjMap){
    if(type == eGoal){
	    control_msgs_msg_ParallelGripperCommandGoal_common commonObj;	
        commonObj.mCommonObjMap = commonObjMap;
	    MDFactory_T factory;
	    return commonObj.get_arr(factory, (control_msgs::action::ParallelGripperCommand::Goal*)msgPtr, loader);
    }else if(type == eResult){
        control_msgs_msg_ParallelGripperCommandResult_common commonObj;	
        commonObj.mCommonObjMap = commonObjMap;
	    MDFactory_T factory;
	    return commonObj.get_arr(factory, (control_msgs::action::ParallelGripperCommand::Result*)msgPtr, loader);
    }else if(type == eFeedback){
        control_msgs_msg_ParallelGripperCommandFeedback_common commonObj;
        commonObj.mCommonObjMap = commonObjMap;
	    MDFactory_T factory;
	    return commonObj.get_arr(factory, (control_msgs::action::ParallelGripperCommand::Feedback*)msgPtr, loader);
    }
     else{
        throw std::invalid_argument("Wrong input, Expected 'Goal' or 'Feedback' or 'Result'");
    }
  }
#include "class_loader/register_macro.hpp"
// Register the component with class_loader.
// This acts as a sort of entry point, allowing the component to be discoverable when its library
// is being loaded into a running process.
CLASS_LOADER_REGISTER_CLASS(control_msgs_msg_ParallelGripperCommandGoal_common, MATLABROS2MsgInterface<control_msgs::action::ParallelGripperCommand::Goal>)
CLASS_LOADER_REGISTER_CLASS(control_msgs_msg_ParallelGripperCommandFeedback_common, MATLABROS2MsgInterface<control_msgs::action::ParallelGripperCommand::Feedback>)
CLASS_LOADER_REGISTER_CLASS(control_msgs_msg_ParallelGripperCommandResult_common, MATLABROS2MsgInterface<control_msgs::action::ParallelGripperCommand::Result>)
CLASS_LOADER_REGISTER_CLASS(ros2_control_msgs_ParallelGripperCommand_action, ROS2MsgElementInterfaceFactory)
#ifdef _MSC_VER
#pragma warning(pop)
#else
#pragma GCC diagnostic pop
#endif //_MSC_VER
//gen-1