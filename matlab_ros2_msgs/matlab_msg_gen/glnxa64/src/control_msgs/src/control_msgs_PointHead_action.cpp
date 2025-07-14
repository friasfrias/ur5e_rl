// Copyright 2022 The MathWorks, Inc.
// Common copy functions for control_msgs/PointHeadGoal
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
#include "control_msgs/action/point_head.hpp"
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
class CONTROL_MSGS_EXPORT control_msgs_msg_PointHeadGoal_common : public MATLABROS2MsgInterface<control_msgs::action::PointHead::Goal> {
  public:
    virtual ~control_msgs_msg_PointHeadGoal_common(){}
    virtual void copy_from_struct(control_msgs::action::PointHead::Goal* msg, const matlab::data::Struct& arr, MultiLibLoader loader); 
    //----------------------------------------------------------------------------
    virtual MDArray_T get_arr(MDFactory_T& factory, const control_msgs::action::PointHead::Goal* msg, MultiLibLoader loader, size_t size = 1);
};
  //----------------------------------------------------------------------------
  void control_msgs_msg_PointHeadGoal_common::copy_from_struct(control_msgs::action::PointHead::Goal* msg, const matlab::data::Struct& arr, MultiLibLoader loader) {
    try {
        //target
        const matlab::data::StructArray target_arr = arr["target"];
        auto msgClassPtr_target = getCommonObject<geometry_msgs::msg::PointStamped>("ros2_geometry_msgs_msg_PointStamped_common",loader);
        msgClassPtr_target->copy_from_struct(&msg->target,target_arr[0],loader);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'target' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'target' is wrong type; expected a struct.");
    }
    try {
        //pointing_axis
        const matlab::data::StructArray pointing_axis_arr = arr["pointing_axis"];
        auto msgClassPtr_pointing_axis = getCommonObject<geometry_msgs::msg::Vector3>("ros2_geometry_msgs_msg_Vector3_common",loader);
        msgClassPtr_pointing_axis->copy_from_struct(&msg->pointing_axis,pointing_axis_arr[0],loader);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'pointing_axis' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'pointing_axis' is wrong type; expected a struct.");
    }
    try {
        //pointing_frame
        const matlab::data::CharArray pointing_frame_arr = arr["pointing_frame"];
        msg->pointing_frame = pointing_frame_arr.toAscii();
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'pointing_frame' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'pointing_frame' is wrong type; expected a string.");
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
  MDArray_T control_msgs_msg_PointHeadGoal_common::get_arr(MDFactory_T& factory, const control_msgs::action::PointHead::Goal* msg,
       MultiLibLoader loader, size_t size) {
    auto outArray = factory.createStructArray({size,1},{"MessageType","target","pointing_axis","pointing_frame","min_duration","max_velocity"});
    for(size_t ctr = 0; ctr < size; ctr++){
    outArray[ctr]["MessageType"] = factory.createCharArray("control_msgs/PointHeadGoal");
    // target
    auto currentElement_target = (msg + ctr)->target;
    auto msgClassPtr_target = getCommonObject<geometry_msgs::msg::PointStamped>("ros2_geometry_msgs_msg_PointStamped_common",loader);
    outArray[ctr]["target"] = msgClassPtr_target->get_arr(factory, &currentElement_target, loader);
    // pointing_axis
    auto currentElement_pointing_axis = (msg + ctr)->pointing_axis;
    auto msgClassPtr_pointing_axis = getCommonObject<geometry_msgs::msg::Vector3>("ros2_geometry_msgs_msg_Vector3_common",loader);
    outArray[ctr]["pointing_axis"] = msgClassPtr_pointing_axis->get_arr(factory, &currentElement_pointing_axis, loader);
    // pointing_frame
    auto currentElement_pointing_frame = (msg + ctr)->pointing_frame;
    outArray[ctr]["pointing_frame"] = factory.createCharArray(currentElement_pointing_frame);
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

class CONTROL_MSGS_EXPORT control_msgs_msg_PointHeadResult_common : public MATLABROS2MsgInterface<control_msgs::action::PointHead::Result> {
  public:
    virtual ~control_msgs_msg_PointHeadResult_common(){}
    virtual void copy_from_struct(control_msgs::action::PointHead::Result* msg, const matlab::data::Struct& arr, MultiLibLoader loader); 
    //----------------------------------------------------------------------------
    virtual MDArray_T get_arr(MDFactory_T& factory, const control_msgs::action::PointHead::Result* msg, MultiLibLoader loader, size_t size = 1);
};
  //----------------------------------------------------------------------------
  void control_msgs_msg_PointHeadResult_common::copy_from_struct(control_msgs::action::PointHead::Result* msg, const matlab::data::Struct& arr, MultiLibLoader loader) {
  }
  //----------------------------------------------------------------------------
  MDArray_T control_msgs_msg_PointHeadResult_common::get_arr(MDFactory_T& factory, const control_msgs::action::PointHead::Result* msg,
       MultiLibLoader loader, size_t size) {
    auto outArray = factory.createStructArray({size,1},{"MessageType"});
    for(size_t ctr = 0; ctr < size; ctr++){
    outArray[ctr]["MessageType"] = factory.createCharArray("control_msgs/PointHeadResult");
    }
    return std::move(outArray);
  }

class CONTROL_MSGS_EXPORT control_msgs_msg_PointHeadFeedback_common : public MATLABROS2MsgInterface<control_msgs::action::PointHead::Feedback> {
  public:
    virtual ~control_msgs_msg_PointHeadFeedback_common(){}
    virtual void copy_from_struct(control_msgs::action::PointHead::Feedback* msg, const matlab::data::Struct& arr, MultiLibLoader loader); 
    //----------------------------------------------------------------------------
    virtual MDArray_T get_arr(MDFactory_T& factory, const control_msgs::action::PointHead::Feedback* msg, MultiLibLoader loader, size_t size = 1);
};
  //----------------------------------------------------------------------------
  void control_msgs_msg_PointHeadFeedback_common::copy_from_struct(control_msgs::action::PointHead::Feedback* msg, const matlab::data::Struct& arr, MultiLibLoader loader) {
    try {
        //pointing_angle_error
        const matlab::data::TypedArray<double> pointing_angle_error_arr = arr["pointing_angle_error"];
        msg->pointing_angle_error = pointing_angle_error_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'pointing_angle_error' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'pointing_angle_error' is wrong type; expected a double.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T control_msgs_msg_PointHeadFeedback_common::get_arr(MDFactory_T& factory, const control_msgs::action::PointHead::Feedback* msg,
       MultiLibLoader loader, size_t size) {
    auto outArray = factory.createStructArray({size,1},{"MessageType","pointing_angle_error"});
    for(size_t ctr = 0; ctr < size; ctr++){
    outArray[ctr]["MessageType"] = factory.createCharArray("control_msgs/PointHeadFeedback");
    // pointing_angle_error
    auto currentElement_pointing_angle_error = (msg + ctr)->pointing_angle_error;
    outArray[ctr]["pointing_angle_error"] = factory.createScalar(currentElement_pointing_angle_error);
    }
    return std::move(outArray);
  }

class CONTROL_MSGS_EXPORT ros2_control_msgs_PointHead_action : public ROS2MsgElementInterfaceFactory {
  public:
    virtual ~ros2_control_msgs_PointHead_action(){}
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
          ros2_control_msgs_PointHead_action::generatePublisherInterface(ElementType type){
    std::shared_ptr<MATLABPublisherInterface> ptr;
    if(type == eGoal){
        ptr = std::make_shared<ROS2PublisherImpl<control_msgs::action::PointHead::Goal,control_msgs_msg_PointHeadGoal_common>>();
    }else if(type == eFeedback){
        ptr = std::make_shared<ROS2PublisherImpl<control_msgs::action::PointHead::Feedback,control_msgs_msg_PointHeadFeedback_common>>();
    }else if(type == eResult){
        ptr = std::make_shared<ROS2PublisherImpl<control_msgs::action::PointHead::Result,control_msgs_msg_PointHeadResult_common>>();
    }else{
        throw std::invalid_argument("Wrong input, Expected 'Goal' or 'Feedback' or 'Result'");
    }
    return ptr;
  }
  std::shared_ptr<MATLABSubscriberInterface> 
         ros2_control_msgs_PointHead_action::generateSubscriberInterface(ElementType type){
    std::shared_ptr<MATLABSubscriberInterface> ptr;
    if(type == eGoal){
        ptr = std::make_shared<ROS2SubscriberImpl<control_msgs::action::PointHead::Goal,control_msgs_msg_PointHeadGoal_common>>();
    }else if(type == eFeedback){
        ptr = std::make_shared<ROS2SubscriberImpl<control_msgs::action::PointHead::Feedback,control_msgs_msg_PointHeadFeedback_common>>();
    }else if(type == eResult){
        ptr = std::make_shared<ROS2SubscriberImpl<control_msgs::action::PointHead::Result,control_msgs_msg_PointHeadResult_common>>();
    }else{
        throw std::invalid_argument("Wrong input, Expected 'Goal' or 'Feedback' or 'Result'");
    }
    return ptr;
  }
  std::shared_ptr<MATLABActClientInterface> 
          ros2_control_msgs_PointHead_action::generateActClientInterface(){
      return std::make_shared<ROS2ActClientImpl<control_msgs::action::PointHead,control_msgs::action::PointHead::Goal,control_msgs::action::PointHead::Feedback::ConstSharedPtr,control_msgs::action::PointHead::Result::ConstSharedPtr,control_msgs_msg_PointHeadGoal_common,control_msgs_msg_PointHeadFeedback_common,control_msgs_msg_PointHeadResult_common>>();
  }
  std::shared_ptr<MATLABActServerInterface> 
          ros2_control_msgs_PointHead_action::generateActServerInterface(){
      return std::make_shared<ROS2ActServerImpl<control_msgs::action::PointHead,control_msgs::action::PointHead::Feedback,control_msgs::action::PointHead::Result,control_msgs::action::PointHead::Goal::ConstSharedPtr,control_msgs_msg_PointHeadGoal_common,control_msgs_msg_PointHeadFeedback_common,control_msgs_msg_PointHeadResult_common>>();
  }
  std::shared_ptr<void> ros2_control_msgs_PointHead_action::generateCppMessage(ElementType type, 
                                           const matlab::data::StructArray& arr,
                                           MultiLibLoader loader,
                                           std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* commonObjMap){
    if(type == eGoal){
        auto msg = std::make_shared<control_msgs::action::PointHead::Goal>();
        control_msgs_msg_PointHeadGoal_common commonObj;
        commonObj.mCommonObjMap = commonObjMap;
        commonObj.copy_from_struct(msg.get(), arr[0], loader);
        return msg;
    }else if(type == eFeedback){
        auto msg = std::make_shared<control_msgs::action::PointHead::Feedback>();
        control_msgs_msg_PointHeadFeedback_common commonObj;
        commonObj.mCommonObjMap = commonObjMap;
        commonObj.copy_from_struct(msg.get(), arr[0], loader);
        return msg;
    }else if(type == eResult){
        auto msg = std::make_shared<control_msgs::action::PointHead::Result>();
        control_msgs_msg_PointHeadResult_common commonObj;
        commonObj.mCommonObjMap = commonObjMap;
        commonObj.copy_from_struct(msg.get(), arr[0], loader);
        return msg;
   }else{
        throw std::invalid_argument("Wrong input, Expected 'Goal' or 'Feedback' or 'Result'");
    }
  }
 matlab::data::StructArray ros2_control_msgs_PointHead_action::generateMLMessage(ElementType type, 
                                                    void*  msgPtr ,
                                                    MultiLibLoader  loader ,
                                                    std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* commonObjMap){
    if(type == eGoal){
	    control_msgs_msg_PointHeadGoal_common commonObj;	
        commonObj.mCommonObjMap = commonObjMap;
	    MDFactory_T factory;
	    return commonObj.get_arr(factory, (control_msgs::action::PointHead::Goal*)msgPtr, loader);
    }else if(type == eResult){
        control_msgs_msg_PointHeadResult_common commonObj;	
        commonObj.mCommonObjMap = commonObjMap;
	    MDFactory_T factory;
	    return commonObj.get_arr(factory, (control_msgs::action::PointHead::Result*)msgPtr, loader);
    }else if(type == eFeedback){
        control_msgs_msg_PointHeadFeedback_common commonObj;
        commonObj.mCommonObjMap = commonObjMap;
	    MDFactory_T factory;
	    return commonObj.get_arr(factory, (control_msgs::action::PointHead::Feedback*)msgPtr, loader);
    }
     else{
        throw std::invalid_argument("Wrong input, Expected 'Goal' or 'Feedback' or 'Result'");
    }
  }
#include "class_loader/register_macro.hpp"
// Register the component with class_loader.
// This acts as a sort of entry point, allowing the component to be discoverable when its library
// is being loaded into a running process.
CLASS_LOADER_REGISTER_CLASS(control_msgs_msg_PointHeadGoal_common, MATLABROS2MsgInterface<control_msgs::action::PointHead::Goal>)
CLASS_LOADER_REGISTER_CLASS(control_msgs_msg_PointHeadFeedback_common, MATLABROS2MsgInterface<control_msgs::action::PointHead::Feedback>)
CLASS_LOADER_REGISTER_CLASS(control_msgs_msg_PointHeadResult_common, MATLABROS2MsgInterface<control_msgs::action::PointHead::Result>)
CLASS_LOADER_REGISTER_CLASS(ros2_control_msgs_PointHead_action, ROS2MsgElementInterfaceFactory)
#ifdef _MSC_VER
#pragma warning(pop)
#else
#pragma GCC diagnostic pop
#endif //_MSC_VER
//gen-1