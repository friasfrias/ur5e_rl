// Copyright 2022 The MathWorks, Inc.
// Common copy functions for control_msgs/GripperCommandGoal
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
#include "control_msgs/action/gripper_command.hpp"
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
class CONTROL_MSGS_EXPORT control_msgs_msg_GripperCommandGoal_common : public MATLABROS2MsgInterface<control_msgs::action::GripperCommand::Goal> {
  public:
    virtual ~control_msgs_msg_GripperCommandGoal_common(){}
    virtual void copy_from_struct(control_msgs::action::GripperCommand::Goal* msg, const matlab::data::Struct& arr, MultiLibLoader loader); 
    //----------------------------------------------------------------------------
    virtual MDArray_T get_arr(MDFactory_T& factory, const control_msgs::action::GripperCommand::Goal* msg, MultiLibLoader loader, size_t size = 1);
};
  //----------------------------------------------------------------------------
  void control_msgs_msg_GripperCommandGoal_common::copy_from_struct(control_msgs::action::GripperCommand::Goal* msg, const matlab::data::Struct& arr, MultiLibLoader loader) {
    try {
        //command
        const matlab::data::StructArray command_arr = arr["command"];
        auto msgClassPtr_command = getCommonObject<control_msgs::msg::GripperCommand>("ros2_control_msgs_msg_GripperCommand_common",loader);
        msgClassPtr_command->copy_from_struct(&msg->command,command_arr[0],loader);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'command' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'command' is wrong type; expected a struct.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T control_msgs_msg_GripperCommandGoal_common::get_arr(MDFactory_T& factory, const control_msgs::action::GripperCommand::Goal* msg,
       MultiLibLoader loader, size_t size) {
    auto outArray = factory.createStructArray({size,1},{"MessageType","command"});
    for(size_t ctr = 0; ctr < size; ctr++){
    outArray[ctr]["MessageType"] = factory.createCharArray("control_msgs/GripperCommandGoal");
    // command
    auto currentElement_command = (msg + ctr)->command;
    auto msgClassPtr_command = getCommonObject<control_msgs::msg::GripperCommand>("ros2_control_msgs_msg_GripperCommand_common",loader);
    outArray[ctr]["command"] = msgClassPtr_command->get_arr(factory, &currentElement_command, loader);
    }
    return std::move(outArray);
  }

class CONTROL_MSGS_EXPORT control_msgs_msg_GripperCommandResult_common : public MATLABROS2MsgInterface<control_msgs::action::GripperCommand::Result> {
  public:
    virtual ~control_msgs_msg_GripperCommandResult_common(){}
    virtual void copy_from_struct(control_msgs::action::GripperCommand::Result* msg, const matlab::data::Struct& arr, MultiLibLoader loader); 
    //----------------------------------------------------------------------------
    virtual MDArray_T get_arr(MDFactory_T& factory, const control_msgs::action::GripperCommand::Result* msg, MultiLibLoader loader, size_t size = 1);
};
  //----------------------------------------------------------------------------
  void control_msgs_msg_GripperCommandResult_common::copy_from_struct(control_msgs::action::GripperCommand::Result* msg, const matlab::data::Struct& arr, MultiLibLoader loader) {
    try {
        //position
        const matlab::data::TypedArray<double> position_arr = arr["position"];
        msg->position = position_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'position' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'position' is wrong type; expected a double.");
    }
    try {
        //effort
        const matlab::data::TypedArray<double> effort_arr = arr["effort"];
        msg->effort = effort_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'effort' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'effort' is wrong type; expected a double.");
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
  MDArray_T control_msgs_msg_GripperCommandResult_common::get_arr(MDFactory_T& factory, const control_msgs::action::GripperCommand::Result* msg,
       MultiLibLoader loader, size_t size) {
    auto outArray = factory.createStructArray({size,1},{"MessageType","position","effort","stalled","reached_goal"});
    for(size_t ctr = 0; ctr < size; ctr++){
    outArray[ctr]["MessageType"] = factory.createCharArray("control_msgs/GripperCommandResult");
    // position
    auto currentElement_position = (msg + ctr)->position;
    outArray[ctr]["position"] = factory.createScalar(currentElement_position);
    // effort
    auto currentElement_effort = (msg + ctr)->effort;
    outArray[ctr]["effort"] = factory.createScalar(currentElement_effort);
    // stalled
    auto currentElement_stalled = (msg + ctr)->stalled;
    outArray[ctr]["stalled"] = factory.createScalar(currentElement_stalled);
    // reached_goal
    auto currentElement_reached_goal = (msg + ctr)->reached_goal;
    outArray[ctr]["reached_goal"] = factory.createScalar(currentElement_reached_goal);
    }
    return std::move(outArray);
  }

class CONTROL_MSGS_EXPORT control_msgs_msg_GripperCommandFeedback_common : public MATLABROS2MsgInterface<control_msgs::action::GripperCommand::Feedback> {
  public:
    virtual ~control_msgs_msg_GripperCommandFeedback_common(){}
    virtual void copy_from_struct(control_msgs::action::GripperCommand::Feedback* msg, const matlab::data::Struct& arr, MultiLibLoader loader); 
    //----------------------------------------------------------------------------
    virtual MDArray_T get_arr(MDFactory_T& factory, const control_msgs::action::GripperCommand::Feedback* msg, MultiLibLoader loader, size_t size = 1);
};
  //----------------------------------------------------------------------------
  void control_msgs_msg_GripperCommandFeedback_common::copy_from_struct(control_msgs::action::GripperCommand::Feedback* msg, const matlab::data::Struct& arr, MultiLibLoader loader) {
    try {
        //position
        const matlab::data::TypedArray<double> position_arr = arr["position"];
        msg->position = position_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'position' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'position' is wrong type; expected a double.");
    }
    try {
        //effort
        const matlab::data::TypedArray<double> effort_arr = arr["effort"];
        msg->effort = effort_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'effort' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'effort' is wrong type; expected a double.");
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
  MDArray_T control_msgs_msg_GripperCommandFeedback_common::get_arr(MDFactory_T& factory, const control_msgs::action::GripperCommand::Feedback* msg,
       MultiLibLoader loader, size_t size) {
    auto outArray = factory.createStructArray({size,1},{"MessageType","position","effort","stalled","reached_goal"});
    for(size_t ctr = 0; ctr < size; ctr++){
    outArray[ctr]["MessageType"] = factory.createCharArray("control_msgs/GripperCommandFeedback");
    // position
    auto currentElement_position = (msg + ctr)->position;
    outArray[ctr]["position"] = factory.createScalar(currentElement_position);
    // effort
    auto currentElement_effort = (msg + ctr)->effort;
    outArray[ctr]["effort"] = factory.createScalar(currentElement_effort);
    // stalled
    auto currentElement_stalled = (msg + ctr)->stalled;
    outArray[ctr]["stalled"] = factory.createScalar(currentElement_stalled);
    // reached_goal
    auto currentElement_reached_goal = (msg + ctr)->reached_goal;
    outArray[ctr]["reached_goal"] = factory.createScalar(currentElement_reached_goal);
    }
    return std::move(outArray);
  }

class CONTROL_MSGS_EXPORT ros2_control_msgs_GripperCommand_action : public ROS2MsgElementInterfaceFactory {
  public:
    virtual ~ros2_control_msgs_GripperCommand_action(){}
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
          ros2_control_msgs_GripperCommand_action::generatePublisherInterface(ElementType type){
    std::shared_ptr<MATLABPublisherInterface> ptr;
    if(type == eGoal){
        ptr = std::make_shared<ROS2PublisherImpl<control_msgs::action::GripperCommand::Goal,control_msgs_msg_GripperCommandGoal_common>>();
    }else if(type == eFeedback){
        ptr = std::make_shared<ROS2PublisherImpl<control_msgs::action::GripperCommand::Feedback,control_msgs_msg_GripperCommandFeedback_common>>();
    }else if(type == eResult){
        ptr = std::make_shared<ROS2PublisherImpl<control_msgs::action::GripperCommand::Result,control_msgs_msg_GripperCommandResult_common>>();
    }else{
        throw std::invalid_argument("Wrong input, Expected 'Goal' or 'Feedback' or 'Result'");
    }
    return ptr;
  }
  std::shared_ptr<MATLABSubscriberInterface> 
         ros2_control_msgs_GripperCommand_action::generateSubscriberInterface(ElementType type){
    std::shared_ptr<MATLABSubscriberInterface> ptr;
    if(type == eGoal){
        ptr = std::make_shared<ROS2SubscriberImpl<control_msgs::action::GripperCommand::Goal,control_msgs_msg_GripperCommandGoal_common>>();
    }else if(type == eFeedback){
        ptr = std::make_shared<ROS2SubscriberImpl<control_msgs::action::GripperCommand::Feedback,control_msgs_msg_GripperCommandFeedback_common>>();
    }else if(type == eResult){
        ptr = std::make_shared<ROS2SubscriberImpl<control_msgs::action::GripperCommand::Result,control_msgs_msg_GripperCommandResult_common>>();
    }else{
        throw std::invalid_argument("Wrong input, Expected 'Goal' or 'Feedback' or 'Result'");
    }
    return ptr;
  }
  std::shared_ptr<MATLABActClientInterface> 
          ros2_control_msgs_GripperCommand_action::generateActClientInterface(){
      return std::make_shared<ROS2ActClientImpl<control_msgs::action::GripperCommand,control_msgs::action::GripperCommand::Goal,control_msgs::action::GripperCommand::Feedback::ConstSharedPtr,control_msgs::action::GripperCommand::Result::ConstSharedPtr,control_msgs_msg_GripperCommandGoal_common,control_msgs_msg_GripperCommandFeedback_common,control_msgs_msg_GripperCommandResult_common>>();
  }
  std::shared_ptr<MATLABActServerInterface> 
          ros2_control_msgs_GripperCommand_action::generateActServerInterface(){
      return std::make_shared<ROS2ActServerImpl<control_msgs::action::GripperCommand,control_msgs::action::GripperCommand::Feedback,control_msgs::action::GripperCommand::Result,control_msgs::action::GripperCommand::Goal::ConstSharedPtr,control_msgs_msg_GripperCommandGoal_common,control_msgs_msg_GripperCommandFeedback_common,control_msgs_msg_GripperCommandResult_common>>();
  }
  std::shared_ptr<void> ros2_control_msgs_GripperCommand_action::generateCppMessage(ElementType type, 
                                           const matlab::data::StructArray& arr,
                                           MultiLibLoader loader,
                                           std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* commonObjMap){
    if(type == eGoal){
        auto msg = std::make_shared<control_msgs::action::GripperCommand::Goal>();
        control_msgs_msg_GripperCommandGoal_common commonObj;
        commonObj.mCommonObjMap = commonObjMap;
        commonObj.copy_from_struct(msg.get(), arr[0], loader);
        return msg;
    }else if(type == eFeedback){
        auto msg = std::make_shared<control_msgs::action::GripperCommand::Feedback>();
        control_msgs_msg_GripperCommandFeedback_common commonObj;
        commonObj.mCommonObjMap = commonObjMap;
        commonObj.copy_from_struct(msg.get(), arr[0], loader);
        return msg;
    }else if(type == eResult){
        auto msg = std::make_shared<control_msgs::action::GripperCommand::Result>();
        control_msgs_msg_GripperCommandResult_common commonObj;
        commonObj.mCommonObjMap = commonObjMap;
        commonObj.copy_from_struct(msg.get(), arr[0], loader);
        return msg;
   }else{
        throw std::invalid_argument("Wrong input, Expected 'Goal' or 'Feedback' or 'Result'");
    }
  }
 matlab::data::StructArray ros2_control_msgs_GripperCommand_action::generateMLMessage(ElementType type, 
                                                    void*  msgPtr ,
                                                    MultiLibLoader  loader ,
                                                    std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* commonObjMap){
    if(type == eGoal){
	    control_msgs_msg_GripperCommandGoal_common commonObj;	
        commonObj.mCommonObjMap = commonObjMap;
	    MDFactory_T factory;
	    return commonObj.get_arr(factory, (control_msgs::action::GripperCommand::Goal*)msgPtr, loader);
    }else if(type == eResult){
        control_msgs_msg_GripperCommandResult_common commonObj;	
        commonObj.mCommonObjMap = commonObjMap;
	    MDFactory_T factory;
	    return commonObj.get_arr(factory, (control_msgs::action::GripperCommand::Result*)msgPtr, loader);
    }else if(type == eFeedback){
        control_msgs_msg_GripperCommandFeedback_common commonObj;
        commonObj.mCommonObjMap = commonObjMap;
	    MDFactory_T factory;
	    return commonObj.get_arr(factory, (control_msgs::action::GripperCommand::Feedback*)msgPtr, loader);
    }
     else{
        throw std::invalid_argument("Wrong input, Expected 'Goal' or 'Feedback' or 'Result'");
    }
  }
#include "class_loader/register_macro.hpp"
// Register the component with class_loader.
// This acts as a sort of entry point, allowing the component to be discoverable when its library
// is being loaded into a running process.
CLASS_LOADER_REGISTER_CLASS(control_msgs_msg_GripperCommandGoal_common, MATLABROS2MsgInterface<control_msgs::action::GripperCommand::Goal>)
CLASS_LOADER_REGISTER_CLASS(control_msgs_msg_GripperCommandFeedback_common, MATLABROS2MsgInterface<control_msgs::action::GripperCommand::Feedback>)
CLASS_LOADER_REGISTER_CLASS(control_msgs_msg_GripperCommandResult_common, MATLABROS2MsgInterface<control_msgs::action::GripperCommand::Result>)
CLASS_LOADER_REGISTER_CLASS(ros2_control_msgs_GripperCommand_action, ROS2MsgElementInterfaceFactory)
#ifdef _MSC_VER
#pragma warning(pop)
#else
#pragma GCC diagnostic pop
#endif //_MSC_VER
//gen-1