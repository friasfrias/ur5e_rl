// Copyright 2020-2022 The MathWorks, Inc.
// Common copy functions for action_msgs/GoalStatus
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
#include "action_msgs/msg/goal_status.hpp"
#include "visibility_control.h"
#include "class_loader/multi_library_class_loader.hpp"
#include "ROS2PubSubTemplates.hpp"
class ACTION_MSGS_EXPORT ros2_action_msgs_msg_GoalStatus_common : public MATLABROS2MsgInterface<action_msgs::msg::GoalStatus> {
  public:
    virtual ~ros2_action_msgs_msg_GoalStatus_common(){}
    virtual void copy_from_struct(action_msgs::msg::GoalStatus* msg, const matlab::data::Struct& arr, MultiLibLoader loader); 
    //----------------------------------------------------------------------------
    virtual MDArray_T get_arr(MDFactory_T& factory, const action_msgs::msg::GoalStatus* msg, MultiLibLoader loader, size_t size = 1);
};
  void ros2_action_msgs_msg_GoalStatus_common::copy_from_struct(action_msgs::msg::GoalStatus* msg, const matlab::data::Struct& arr,
               MultiLibLoader loader) {
    try {
        //goal_info
        const matlab::data::StructArray goal_info_arr = arr["goal_info"];
        auto msgClassPtr_goal_info = getCommonObject<action_msgs::msg::GoalInfo>("ros2_action_msgs_msg_GoalInfo_common",loader);
        msgClassPtr_goal_info->copy_from_struct(&msg->goal_info,goal_info_arr[0],loader);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'goal_info' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'goal_info' is wrong type; expected a struct.");
    }
    try {
        //status
        const matlab::data::TypedArray<int8_t> status_arr = arr["status"];
        msg->status = status_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'status' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'status' is wrong type; expected a int8.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T ros2_action_msgs_msg_GoalStatus_common::get_arr(MDFactory_T& factory, const action_msgs::msg::GoalStatus* msg,
       MultiLibLoader loader, size_t size) {
    auto outArray = factory.createStructArray({size,1},{"MessageType","STATUS_UNKNOWN","STATUS_ACCEPTED","STATUS_EXECUTING","STATUS_CANCELING","STATUS_SUCCEEDED","STATUS_CANCELED","STATUS_ABORTED","goal_info","status"});
    for(size_t ctr = 0; ctr < size; ctr++){
    outArray[ctr]["MessageType"] = factory.createCharArray("action_msgs/GoalStatus");
    // STATUS_UNKNOWN
    auto currentElement_STATUS_UNKNOWN = (msg + ctr)->STATUS_UNKNOWN;
    outArray[ctr]["STATUS_UNKNOWN"] = factory.createScalar(currentElement_STATUS_UNKNOWN);
    // STATUS_ACCEPTED
    auto currentElement_STATUS_ACCEPTED = (msg + ctr)->STATUS_ACCEPTED;
    outArray[ctr]["STATUS_ACCEPTED"] = factory.createScalar(currentElement_STATUS_ACCEPTED);
    // STATUS_EXECUTING
    auto currentElement_STATUS_EXECUTING = (msg + ctr)->STATUS_EXECUTING;
    outArray[ctr]["STATUS_EXECUTING"] = factory.createScalar(currentElement_STATUS_EXECUTING);
    // STATUS_CANCELING
    auto currentElement_STATUS_CANCELING = (msg + ctr)->STATUS_CANCELING;
    outArray[ctr]["STATUS_CANCELING"] = factory.createScalar(currentElement_STATUS_CANCELING);
    // STATUS_SUCCEEDED
    auto currentElement_STATUS_SUCCEEDED = (msg + ctr)->STATUS_SUCCEEDED;
    outArray[ctr]["STATUS_SUCCEEDED"] = factory.createScalar(currentElement_STATUS_SUCCEEDED);
    // STATUS_CANCELED
    auto currentElement_STATUS_CANCELED = (msg + ctr)->STATUS_CANCELED;
    outArray[ctr]["STATUS_CANCELED"] = factory.createScalar(currentElement_STATUS_CANCELED);
    // STATUS_ABORTED
    auto currentElement_STATUS_ABORTED = (msg + ctr)->STATUS_ABORTED;
    outArray[ctr]["STATUS_ABORTED"] = factory.createScalar(currentElement_STATUS_ABORTED);
    // goal_info
    auto currentElement_goal_info = (msg + ctr)->goal_info;
    auto msgClassPtr_goal_info = getCommonObject<action_msgs::msg::GoalInfo>("ros2_action_msgs_msg_GoalInfo_common",loader);
    outArray[ctr]["goal_info"] = msgClassPtr_goal_info->get_arr(factory, &currentElement_goal_info, loader);
    // status
    auto currentElement_status = (msg + ctr)->status;
    outArray[ctr]["status"] = factory.createScalar(currentElement_status);
    }
    return std::move(outArray);
  } 
class ACTION_MSGS_EXPORT ros2_action_msgs_GoalStatus_message : public ROS2MsgElementInterfaceFactory {
  public:
    virtual ~ros2_action_msgs_GoalStatus_message(){}
    virtual std::shared_ptr<MATLABPublisherInterface> generatePublisherInterface(ElementType /*type*/);
    virtual std::shared_ptr<MATLABSubscriberInterface> generateSubscriberInterface(ElementType /*type*/);
    virtual std::shared_ptr<void> generateCppMessage(ElementType /*type*/, const matlab::data::StructArray& /* arr */, MultiLibLoader /* loader */, std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* /*commonObjMap*/);
    virtual matlab::data::StructArray generateMLMessage(ElementType  /*type*/ ,void*  /* msg */, MultiLibLoader /* loader */ , std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* /*commonObjMap*/);
};  
  std::shared_ptr<MATLABPublisherInterface> 
          ros2_action_msgs_GoalStatus_message::generatePublisherInterface(ElementType /*type*/){
    return std::make_shared<ROS2PublisherImpl<action_msgs::msg::GoalStatus,ros2_action_msgs_msg_GoalStatus_common>>();
  }
  std::shared_ptr<MATLABSubscriberInterface> 
         ros2_action_msgs_GoalStatus_message::generateSubscriberInterface(ElementType /*type*/){
    return std::make_shared<ROS2SubscriberImpl<action_msgs::msg::GoalStatus,ros2_action_msgs_msg_GoalStatus_common>>();
  }
  std::shared_ptr<void> ros2_action_msgs_GoalStatus_message::generateCppMessage(ElementType /*type*/, 
                                           const matlab::data::StructArray& arr,
                                           MultiLibLoader loader,
                                           std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* commonObjMap){
    auto msg = std::make_shared<action_msgs::msg::GoalStatus>();
    ros2_action_msgs_msg_GoalStatus_common commonObj;
    commonObj.mCommonObjMap = commonObjMap;
    commonObj.copy_from_struct(msg.get(), arr[0], loader);
    return msg;
  }
  matlab::data::StructArray ros2_action_msgs_GoalStatus_message::generateMLMessage(ElementType  /*type*/ ,
                                                    void*  msg ,
                                                    MultiLibLoader  loader ,
                                                    std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>*  commonObjMap ){
    ros2_action_msgs_msg_GoalStatus_common commonObj;	
    commonObj.mCommonObjMap = commonObjMap;	
    MDFactory_T factory;
    return commonObj.get_arr(factory, (action_msgs::msg::GoalStatus*)msg, loader);			
 }
#include "class_loader/register_macro.hpp"
// Register the component with class_loader.
// This acts as a sort of entry point, allowing the component to be discoverable when its library
// is being loaded into a running process.
CLASS_LOADER_REGISTER_CLASS(ros2_action_msgs_msg_GoalStatus_common, MATLABROS2MsgInterface<action_msgs::msg::GoalStatus>)
CLASS_LOADER_REGISTER_CLASS(ros2_action_msgs_GoalStatus_message, ROS2MsgElementInterfaceFactory)
#ifdef _MSC_VER
#pragma warning(pop)
#else
#pragma GCC diagnostic pop
#endif //_MSC_VER