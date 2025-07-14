// Copyright 2022 The MathWorks, Inc.
// Common copy functions for control_msgs/JointTrajectoryGoal
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
#include "control_msgs/action/joint_trajectory.hpp"
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
class CONTROL_MSGS_EXPORT control_msgs_msg_JointTrajectoryGoal_common : public MATLABROS2MsgInterface<control_msgs::action::JointTrajectory::Goal> {
  public:
    virtual ~control_msgs_msg_JointTrajectoryGoal_common(){}
    virtual void copy_from_struct(control_msgs::action::JointTrajectory::Goal* msg, const matlab::data::Struct& arr, MultiLibLoader loader); 
    //----------------------------------------------------------------------------
    virtual MDArray_T get_arr(MDFactory_T& factory, const control_msgs::action::JointTrajectory::Goal* msg, MultiLibLoader loader, size_t size = 1);
};
  //----------------------------------------------------------------------------
  void control_msgs_msg_JointTrajectoryGoal_common::copy_from_struct(control_msgs::action::JointTrajectory::Goal* msg, const matlab::data::Struct& arr, MultiLibLoader loader) {
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
  }
  //----------------------------------------------------------------------------
  MDArray_T control_msgs_msg_JointTrajectoryGoal_common::get_arr(MDFactory_T& factory, const control_msgs::action::JointTrajectory::Goal* msg,
       MultiLibLoader loader, size_t size) {
    auto outArray = factory.createStructArray({size,1},{"MessageType","trajectory"});
    for(size_t ctr = 0; ctr < size; ctr++){
    outArray[ctr]["MessageType"] = factory.createCharArray("control_msgs/JointTrajectoryGoal");
    // trajectory
    auto currentElement_trajectory = (msg + ctr)->trajectory;
    auto msgClassPtr_trajectory = getCommonObject<trajectory_msgs::msg::JointTrajectory>("ros2_trajectory_msgs_msg_JointTrajectory_common",loader);
    outArray[ctr]["trajectory"] = msgClassPtr_trajectory->get_arr(factory, &currentElement_trajectory, loader);
    }
    return std::move(outArray);
  }

class CONTROL_MSGS_EXPORT control_msgs_msg_JointTrajectoryResult_common : public MATLABROS2MsgInterface<control_msgs::action::JointTrajectory::Result> {
  public:
    virtual ~control_msgs_msg_JointTrajectoryResult_common(){}
    virtual void copy_from_struct(control_msgs::action::JointTrajectory::Result* msg, const matlab::data::Struct& arr, MultiLibLoader loader); 
    //----------------------------------------------------------------------------
    virtual MDArray_T get_arr(MDFactory_T& factory, const control_msgs::action::JointTrajectory::Result* msg, MultiLibLoader loader, size_t size = 1);
};
  //----------------------------------------------------------------------------
  void control_msgs_msg_JointTrajectoryResult_common::copy_from_struct(control_msgs::action::JointTrajectory::Result* msg, const matlab::data::Struct& arr, MultiLibLoader loader) {
  }
  //----------------------------------------------------------------------------
  MDArray_T control_msgs_msg_JointTrajectoryResult_common::get_arr(MDFactory_T& factory, const control_msgs::action::JointTrajectory::Result* msg,
       MultiLibLoader loader, size_t size) {
    auto outArray = factory.createStructArray({size,1},{"MessageType"});
    for(size_t ctr = 0; ctr < size; ctr++){
    outArray[ctr]["MessageType"] = factory.createCharArray("control_msgs/JointTrajectoryResult");
    }
    return std::move(outArray);
  }

class CONTROL_MSGS_EXPORT control_msgs_msg_JointTrajectoryFeedback_common : public MATLABROS2MsgInterface<control_msgs::action::JointTrajectory::Feedback> {
  public:
    virtual ~control_msgs_msg_JointTrajectoryFeedback_common(){}
    virtual void copy_from_struct(control_msgs::action::JointTrajectory::Feedback* msg, const matlab::data::Struct& arr, MultiLibLoader loader); 
    //----------------------------------------------------------------------------
    virtual MDArray_T get_arr(MDFactory_T& factory, const control_msgs::action::JointTrajectory::Feedback* msg, MultiLibLoader loader, size_t size = 1);
};
  //----------------------------------------------------------------------------
  void control_msgs_msg_JointTrajectoryFeedback_common::copy_from_struct(control_msgs::action::JointTrajectory::Feedback* msg, const matlab::data::Struct& arr, MultiLibLoader loader) {
  }
  //----------------------------------------------------------------------------
  MDArray_T control_msgs_msg_JointTrajectoryFeedback_common::get_arr(MDFactory_T& factory, const control_msgs::action::JointTrajectory::Feedback* msg,
       MultiLibLoader loader, size_t size) {
    auto outArray = factory.createStructArray({size,1},{"MessageType"});
    for(size_t ctr = 0; ctr < size; ctr++){
    outArray[ctr]["MessageType"] = factory.createCharArray("control_msgs/JointTrajectoryFeedback");
    }
    return std::move(outArray);
  }

class CONTROL_MSGS_EXPORT ros2_control_msgs_JointTrajectory_action : public ROS2MsgElementInterfaceFactory {
  public:
    virtual ~ros2_control_msgs_JointTrajectory_action(){}
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
          ros2_control_msgs_JointTrajectory_action::generatePublisherInterface(ElementType type){
    std::shared_ptr<MATLABPublisherInterface> ptr;
    if(type == eGoal){
        ptr = std::make_shared<ROS2PublisherImpl<control_msgs::action::JointTrajectory::Goal,control_msgs_msg_JointTrajectoryGoal_common>>();
    }else if(type == eFeedback){
        ptr = std::make_shared<ROS2PublisherImpl<control_msgs::action::JointTrajectory::Feedback,control_msgs_msg_JointTrajectoryFeedback_common>>();
    }else if(type == eResult){
        ptr = std::make_shared<ROS2PublisherImpl<control_msgs::action::JointTrajectory::Result,control_msgs_msg_JointTrajectoryResult_common>>();
    }else{
        throw std::invalid_argument("Wrong input, Expected 'Goal' or 'Feedback' or 'Result'");
    }
    return ptr;
  }
  std::shared_ptr<MATLABSubscriberInterface> 
         ros2_control_msgs_JointTrajectory_action::generateSubscriberInterface(ElementType type){
    std::shared_ptr<MATLABSubscriberInterface> ptr;
    if(type == eGoal){
        ptr = std::make_shared<ROS2SubscriberImpl<control_msgs::action::JointTrajectory::Goal,control_msgs_msg_JointTrajectoryGoal_common>>();
    }else if(type == eFeedback){
        ptr = std::make_shared<ROS2SubscriberImpl<control_msgs::action::JointTrajectory::Feedback,control_msgs_msg_JointTrajectoryFeedback_common>>();
    }else if(type == eResult){
        ptr = std::make_shared<ROS2SubscriberImpl<control_msgs::action::JointTrajectory::Result,control_msgs_msg_JointTrajectoryResult_common>>();
    }else{
        throw std::invalid_argument("Wrong input, Expected 'Goal' or 'Feedback' or 'Result'");
    }
    return ptr;
  }
  std::shared_ptr<MATLABActClientInterface> 
          ros2_control_msgs_JointTrajectory_action::generateActClientInterface(){
      return std::make_shared<ROS2ActClientImpl<control_msgs::action::JointTrajectory,control_msgs::action::JointTrajectory::Goal,control_msgs::action::JointTrajectory::Feedback::ConstSharedPtr,control_msgs::action::JointTrajectory::Result::ConstSharedPtr,control_msgs_msg_JointTrajectoryGoal_common,control_msgs_msg_JointTrajectoryFeedback_common,control_msgs_msg_JointTrajectoryResult_common>>();
  }
  std::shared_ptr<MATLABActServerInterface> 
          ros2_control_msgs_JointTrajectory_action::generateActServerInterface(){
      return std::make_shared<ROS2ActServerImpl<control_msgs::action::JointTrajectory,control_msgs::action::JointTrajectory::Feedback,control_msgs::action::JointTrajectory::Result,control_msgs::action::JointTrajectory::Goal::ConstSharedPtr,control_msgs_msg_JointTrajectoryGoal_common,control_msgs_msg_JointTrajectoryFeedback_common,control_msgs_msg_JointTrajectoryResult_common>>();
  }
  std::shared_ptr<void> ros2_control_msgs_JointTrajectory_action::generateCppMessage(ElementType type, 
                                           const matlab::data::StructArray& arr,
                                           MultiLibLoader loader,
                                           std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* commonObjMap){
    if(type == eGoal){
        auto msg = std::make_shared<control_msgs::action::JointTrajectory::Goal>();
        control_msgs_msg_JointTrajectoryGoal_common commonObj;
        commonObj.mCommonObjMap = commonObjMap;
        commonObj.copy_from_struct(msg.get(), arr[0], loader);
        return msg;
    }else if(type == eFeedback){
        auto msg = std::make_shared<control_msgs::action::JointTrajectory::Feedback>();
        control_msgs_msg_JointTrajectoryFeedback_common commonObj;
        commonObj.mCommonObjMap = commonObjMap;
        commonObj.copy_from_struct(msg.get(), arr[0], loader);
        return msg;
    }else if(type == eResult){
        auto msg = std::make_shared<control_msgs::action::JointTrajectory::Result>();
        control_msgs_msg_JointTrajectoryResult_common commonObj;
        commonObj.mCommonObjMap = commonObjMap;
        commonObj.copy_from_struct(msg.get(), arr[0], loader);
        return msg;
   }else{
        throw std::invalid_argument("Wrong input, Expected 'Goal' or 'Feedback' or 'Result'");
    }
  }
 matlab::data::StructArray ros2_control_msgs_JointTrajectory_action::generateMLMessage(ElementType type, 
                                                    void*  msgPtr ,
                                                    MultiLibLoader  loader ,
                                                    std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* commonObjMap){
    if(type == eGoal){
	    control_msgs_msg_JointTrajectoryGoal_common commonObj;	
        commonObj.mCommonObjMap = commonObjMap;
	    MDFactory_T factory;
	    return commonObj.get_arr(factory, (control_msgs::action::JointTrajectory::Goal*)msgPtr, loader);
    }else if(type == eResult){
        control_msgs_msg_JointTrajectoryResult_common commonObj;	
        commonObj.mCommonObjMap = commonObjMap;
	    MDFactory_T factory;
	    return commonObj.get_arr(factory, (control_msgs::action::JointTrajectory::Result*)msgPtr, loader);
    }else if(type == eFeedback){
        control_msgs_msg_JointTrajectoryFeedback_common commonObj;
        commonObj.mCommonObjMap = commonObjMap;
	    MDFactory_T factory;
	    return commonObj.get_arr(factory, (control_msgs::action::JointTrajectory::Feedback*)msgPtr, loader);
    }
     else{
        throw std::invalid_argument("Wrong input, Expected 'Goal' or 'Feedback' or 'Result'");
    }
  }
#include "class_loader/register_macro.hpp"
// Register the component with class_loader.
// This acts as a sort of entry point, allowing the component to be discoverable when its library
// is being loaded into a running process.
CLASS_LOADER_REGISTER_CLASS(control_msgs_msg_JointTrajectoryGoal_common, MATLABROS2MsgInterface<control_msgs::action::JointTrajectory::Goal>)
CLASS_LOADER_REGISTER_CLASS(control_msgs_msg_JointTrajectoryFeedback_common, MATLABROS2MsgInterface<control_msgs::action::JointTrajectory::Feedback>)
CLASS_LOADER_REGISTER_CLASS(control_msgs_msg_JointTrajectoryResult_common, MATLABROS2MsgInterface<control_msgs::action::JointTrajectory::Result>)
CLASS_LOADER_REGISTER_CLASS(ros2_control_msgs_JointTrajectory_action, ROS2MsgElementInterfaceFactory)
#ifdef _MSC_VER
#pragma warning(pop)
#else
#pragma GCC diagnostic pop
#endif //_MSC_VER
//gen-1