// Copyright 2022 The MathWorks, Inc.
// Common copy functions for control_msgs/SingleJointPositionGoal
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
#include "control_msgs/action/single_joint_position.hpp"
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
class CONTROL_MSGS_EXPORT control_msgs_msg_SingleJointPositionGoal_common : public MATLABROS2MsgInterface<control_msgs::action::SingleJointPosition::Goal> {
  public:
    virtual ~control_msgs_msg_SingleJointPositionGoal_common(){}
    virtual void copy_from_struct(control_msgs::action::SingleJointPosition::Goal* msg, const matlab::data::Struct& arr, MultiLibLoader loader); 
    //----------------------------------------------------------------------------
    virtual MDArray_T get_arr(MDFactory_T& factory, const control_msgs::action::SingleJointPosition::Goal* msg, MultiLibLoader loader, size_t size = 1);
};
  //----------------------------------------------------------------------------
  void control_msgs_msg_SingleJointPositionGoal_common::copy_from_struct(control_msgs::action::SingleJointPosition::Goal* msg, const matlab::data::Struct& arr, MultiLibLoader loader) {
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
        //min_duration
        const matlab::data::StructArray min_duration_arr = arr["min_duration"];
        auto msgClassPtr_min_duration = getCommonObject<builtin_interfaces::msg::Duration>("ros2_builtin_interfaces_msg_Duration_common",loader);
        msgClassPtr_min_duration->copy_from_struct(&msg->min_duration,min_duration_arr[0],loader);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'min_duration' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'min_duration' is wrong type; expected a struct.");
    }
    try {
        //max_velocity
        const matlab::data::TypedArray<double> max_velocity_arr = arr["max_velocity"];
        msg->max_velocity = max_velocity_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'max_velocity' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'max_velocity' is wrong type; expected a double.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T control_msgs_msg_SingleJointPositionGoal_common::get_arr(MDFactory_T& factory, const control_msgs::action::SingleJointPosition::Goal* msg,
       MultiLibLoader loader, size_t size) {
    auto outArray = factory.createStructArray({size,1},{"MessageType","position","min_duration","max_velocity"});
    for(size_t ctr = 0; ctr < size; ctr++){
    outArray[ctr]["MessageType"] = factory.createCharArray("control_msgs/SingleJointPositionGoal");
    // position
    auto currentElement_position = (msg + ctr)->position;
    outArray[ctr]["position"] = factory.createScalar(currentElement_position);
    // min_duration
    auto currentElement_min_duration = (msg + ctr)->min_duration;
    auto msgClassPtr_min_duration = getCommonObject<builtin_interfaces::msg::Duration>("ros2_builtin_interfaces_msg_Duration_common",loader);
    outArray[ctr]["min_duration"] = msgClassPtr_min_duration->get_arr(factory, &currentElement_min_duration, loader);
    // max_velocity
    auto currentElement_max_velocity = (msg + ctr)->max_velocity;
    outArray[ctr]["max_velocity"] = factory.createScalar(currentElement_max_velocity);
    }
    return std::move(outArray);
  }

class CONTROL_MSGS_EXPORT control_msgs_msg_SingleJointPositionResult_common : public MATLABROS2MsgInterface<control_msgs::action::SingleJointPosition::Result> {
  public:
    virtual ~control_msgs_msg_SingleJointPositionResult_common(){}
    virtual void copy_from_struct(control_msgs::action::SingleJointPosition::Result* msg, const matlab::data::Struct& arr, MultiLibLoader loader); 
    //----------------------------------------------------------------------------
    virtual MDArray_T get_arr(MDFactory_T& factory, const control_msgs::action::SingleJointPosition::Result* msg, MultiLibLoader loader, size_t size = 1);
};
  //----------------------------------------------------------------------------
  void control_msgs_msg_SingleJointPositionResult_common::copy_from_struct(control_msgs::action::SingleJointPosition::Result* msg, const matlab::data::Struct& arr, MultiLibLoader loader) {
  }
  //----------------------------------------------------------------------------
  MDArray_T control_msgs_msg_SingleJointPositionResult_common::get_arr(MDFactory_T& factory, const control_msgs::action::SingleJointPosition::Result* msg,
       MultiLibLoader loader, size_t size) {
    auto outArray = factory.createStructArray({size,1},{"MessageType"});
    for(size_t ctr = 0; ctr < size; ctr++){
    outArray[ctr]["MessageType"] = factory.createCharArray("control_msgs/SingleJointPositionResult");
    }
    return std::move(outArray);
  }

class CONTROL_MSGS_EXPORT control_msgs_msg_SingleJointPositionFeedback_common : public MATLABROS2MsgInterface<control_msgs::action::SingleJointPosition::Feedback> {
  public:
    virtual ~control_msgs_msg_SingleJointPositionFeedback_common(){}
    virtual void copy_from_struct(control_msgs::action::SingleJointPosition::Feedback* msg, const matlab::data::Struct& arr, MultiLibLoader loader); 
    //----------------------------------------------------------------------------
    virtual MDArray_T get_arr(MDFactory_T& factory, const control_msgs::action::SingleJointPosition::Feedback* msg, MultiLibLoader loader, size_t size = 1);
};
  //----------------------------------------------------------------------------
  void control_msgs_msg_SingleJointPositionFeedback_common::copy_from_struct(control_msgs::action::SingleJointPosition::Feedback* msg, const matlab::data::Struct& arr, MultiLibLoader loader) {
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
        //position
        const matlab::data::TypedArray<double> position_arr = arr["position"];
        msg->position = position_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'position' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'position' is wrong type; expected a double.");
    }
    try {
        //velocity
        const matlab::data::TypedArray<double> velocity_arr = arr["velocity"];
        msg->velocity = velocity_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'velocity' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'velocity' is wrong type; expected a double.");
    }
    try {
        //error
        const matlab::data::TypedArray<double> error_arr = arr["error"];
        msg->error = error_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'error' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'error' is wrong type; expected a double.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T control_msgs_msg_SingleJointPositionFeedback_common::get_arr(MDFactory_T& factory, const control_msgs::action::SingleJointPosition::Feedback* msg,
       MultiLibLoader loader, size_t size) {
    auto outArray = factory.createStructArray({size,1},{"MessageType","header","position","velocity","error"});
    for(size_t ctr = 0; ctr < size; ctr++){
    outArray[ctr]["MessageType"] = factory.createCharArray("control_msgs/SingleJointPositionFeedback");
    // header
    auto currentElement_header = (msg + ctr)->header;
    auto msgClassPtr_header = getCommonObject<std_msgs::msg::Header>("ros2_std_msgs_msg_Header_common",loader);
    outArray[ctr]["header"] = msgClassPtr_header->get_arr(factory, &currentElement_header, loader);
    // position
    auto currentElement_position = (msg + ctr)->position;
    outArray[ctr]["position"] = factory.createScalar(currentElement_position);
    // velocity
    auto currentElement_velocity = (msg + ctr)->velocity;
    outArray[ctr]["velocity"] = factory.createScalar(currentElement_velocity);
    // error
    auto currentElement_error = (msg + ctr)->error;
    outArray[ctr]["error"] = factory.createScalar(currentElement_error);
    }
    return std::move(outArray);
  }

class CONTROL_MSGS_EXPORT ros2_control_msgs_SingleJointPosition_action : public ROS2MsgElementInterfaceFactory {
  public:
    virtual ~ros2_control_msgs_SingleJointPosition_action(){}
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
          ros2_control_msgs_SingleJointPosition_action::generatePublisherInterface(ElementType type){
    std::shared_ptr<MATLABPublisherInterface> ptr;
    if(type == eGoal){
        ptr = std::make_shared<ROS2PublisherImpl<control_msgs::action::SingleJointPosition::Goal,control_msgs_msg_SingleJointPositionGoal_common>>();
    }else if(type == eFeedback){
        ptr = std::make_shared<ROS2PublisherImpl<control_msgs::action::SingleJointPosition::Feedback,control_msgs_msg_SingleJointPositionFeedback_common>>();
    }else if(type == eResult){
        ptr = std::make_shared<ROS2PublisherImpl<control_msgs::action::SingleJointPosition::Result,control_msgs_msg_SingleJointPositionResult_common>>();
    }else{
        throw std::invalid_argument("Wrong input, Expected 'Goal' or 'Feedback' or 'Result'");
    }
    return ptr;
  }
  std::shared_ptr<MATLABSubscriberInterface> 
         ros2_control_msgs_SingleJointPosition_action::generateSubscriberInterface(ElementType type){
    std::shared_ptr<MATLABSubscriberInterface> ptr;
    if(type == eGoal){
        ptr = std::make_shared<ROS2SubscriberImpl<control_msgs::action::SingleJointPosition::Goal,control_msgs_msg_SingleJointPositionGoal_common>>();
    }else if(type == eFeedback){
        ptr = std::make_shared<ROS2SubscriberImpl<control_msgs::action::SingleJointPosition::Feedback,control_msgs_msg_SingleJointPositionFeedback_common>>();
    }else if(type == eResult){
        ptr = std::make_shared<ROS2SubscriberImpl<control_msgs::action::SingleJointPosition::Result,control_msgs_msg_SingleJointPositionResult_common>>();
    }else{
        throw std::invalid_argument("Wrong input, Expected 'Goal' or 'Feedback' or 'Result'");
    }
    return ptr;
  }
  std::shared_ptr<MATLABActClientInterface> 
          ros2_control_msgs_SingleJointPosition_action::generateActClientInterface(){
      return std::make_shared<ROS2ActClientImpl<control_msgs::action::SingleJointPosition,control_msgs::action::SingleJointPosition::Goal,control_msgs::action::SingleJointPosition::Feedback::ConstSharedPtr,control_msgs::action::SingleJointPosition::Result::ConstSharedPtr,control_msgs_msg_SingleJointPositionGoal_common,control_msgs_msg_SingleJointPositionFeedback_common,control_msgs_msg_SingleJointPositionResult_common>>();
  }
  std::shared_ptr<MATLABActServerInterface> 
          ros2_control_msgs_SingleJointPosition_action::generateActServerInterface(){
      return std::make_shared<ROS2ActServerImpl<control_msgs::action::SingleJointPosition,control_msgs::action::SingleJointPosition::Feedback,control_msgs::action::SingleJointPosition::Result,control_msgs::action::SingleJointPosition::Goal::ConstSharedPtr,control_msgs_msg_SingleJointPositionGoal_common,control_msgs_msg_SingleJointPositionFeedback_common,control_msgs_msg_SingleJointPositionResult_common>>();
  }
  std::shared_ptr<void> ros2_control_msgs_SingleJointPosition_action::generateCppMessage(ElementType type, 
                                           const matlab::data::StructArray& arr,
                                           MultiLibLoader loader,
                                           std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* commonObjMap){
    if(type == eGoal){
        auto msg = std::make_shared<control_msgs::action::SingleJointPosition::Goal>();
        control_msgs_msg_SingleJointPositionGoal_common commonObj;
        commonObj.mCommonObjMap = commonObjMap;
        commonObj.copy_from_struct(msg.get(), arr[0], loader);
        return msg;
    }else if(type == eFeedback){
        auto msg = std::make_shared<control_msgs::action::SingleJointPosition::Feedback>();
        control_msgs_msg_SingleJointPositionFeedback_common commonObj;
        commonObj.mCommonObjMap = commonObjMap;
        commonObj.copy_from_struct(msg.get(), arr[0], loader);
        return msg;
    }else if(type == eResult){
        auto msg = std::make_shared<control_msgs::action::SingleJointPosition::Result>();
        control_msgs_msg_SingleJointPositionResult_common commonObj;
        commonObj.mCommonObjMap = commonObjMap;
        commonObj.copy_from_struct(msg.get(), arr[0], loader);
        return msg;
   }else{
        throw std::invalid_argument("Wrong input, Expected 'Goal' or 'Feedback' or 'Result'");
    }
  }
 matlab::data::StructArray ros2_control_msgs_SingleJointPosition_action::generateMLMessage(ElementType type, 
                                                    void*  msgPtr ,
                                                    MultiLibLoader  loader ,
                                                    std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* commonObjMap){
    if(type == eGoal){
	    control_msgs_msg_SingleJointPositionGoal_common commonObj;	
        commonObj.mCommonObjMap = commonObjMap;
	    MDFactory_T factory;
	    return commonObj.get_arr(factory, (control_msgs::action::SingleJointPosition::Goal*)msgPtr, loader);
    }else if(type == eResult){
        control_msgs_msg_SingleJointPositionResult_common commonObj;	
        commonObj.mCommonObjMap = commonObjMap;
	    MDFactory_T factory;
	    return commonObj.get_arr(factory, (control_msgs::action::SingleJointPosition::Result*)msgPtr, loader);
    }else if(type == eFeedback){
        control_msgs_msg_SingleJointPositionFeedback_common commonObj;
        commonObj.mCommonObjMap = commonObjMap;
	    MDFactory_T factory;
	    return commonObj.get_arr(factory, (control_msgs::action::SingleJointPosition::Feedback*)msgPtr, loader);
    }
     else{
        throw std::invalid_argument("Wrong input, Expected 'Goal' or 'Feedback' or 'Result'");
    }
  }
#include "class_loader/register_macro.hpp"
// Register the component with class_loader.
// This acts as a sort of entry point, allowing the component to be discoverable when its library
// is being loaded into a running process.
CLASS_LOADER_REGISTER_CLASS(control_msgs_msg_SingleJointPositionGoal_common, MATLABROS2MsgInterface<control_msgs::action::SingleJointPosition::Goal>)
CLASS_LOADER_REGISTER_CLASS(control_msgs_msg_SingleJointPositionFeedback_common, MATLABROS2MsgInterface<control_msgs::action::SingleJointPosition::Feedback>)
CLASS_LOADER_REGISTER_CLASS(control_msgs_msg_SingleJointPositionResult_common, MATLABROS2MsgInterface<control_msgs::action::SingleJointPosition::Result>)
CLASS_LOADER_REGISTER_CLASS(ros2_control_msgs_SingleJointPosition_action, ROS2MsgElementInterfaceFactory)
#ifdef _MSC_VER
#pragma warning(pop)
#else
#pragma GCC diagnostic pop
#endif //_MSC_VER
//gen-1