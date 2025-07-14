// Copyright 2020-2022 The MathWorks, Inc.
// Common copy functions for action_msgs/GoalInfo
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
#include "action_msgs/msg/goal_info.hpp"
#include "visibility_control.h"
#include "class_loader/multi_library_class_loader.hpp"
#include "ROS2PubSubTemplates.hpp"
class ACTION_MSGS_EXPORT ros2_action_msgs_msg_GoalInfo_common : public MATLABROS2MsgInterface<action_msgs::msg::GoalInfo> {
  public:
    virtual ~ros2_action_msgs_msg_GoalInfo_common(){}
    virtual void copy_from_struct(action_msgs::msg::GoalInfo* msg, const matlab::data::Struct& arr, MultiLibLoader loader); 
    //----------------------------------------------------------------------------
    virtual MDArray_T get_arr(MDFactory_T& factory, const action_msgs::msg::GoalInfo* msg, MultiLibLoader loader, size_t size = 1);
};
  void ros2_action_msgs_msg_GoalInfo_common::copy_from_struct(action_msgs::msg::GoalInfo* msg, const matlab::data::Struct& arr,
               MultiLibLoader loader) {
    try {
        //goal_id
        const matlab::data::StructArray goal_id_arr = arr["goal_id"];
        auto msgClassPtr_goal_id = getCommonObject<unique_identifier_msgs::msg::UUID>("ros2_unique_identifier_msgs_msg_UUID_common",loader);
        msgClassPtr_goal_id->copy_from_struct(&msg->goal_id,goal_id_arr[0],loader);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'goal_id' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'goal_id' is wrong type; expected a struct.");
    }
    try {
        //stamp
        const matlab::data::StructArray stamp_arr = arr["stamp"];
        auto msgClassPtr_stamp = getCommonObject<builtin_interfaces::msg::Time>("ros2_builtin_interfaces_msg_Time_common",loader);
        msgClassPtr_stamp->copy_from_struct(&msg->stamp,stamp_arr[0],loader);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'stamp' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'stamp' is wrong type; expected a struct.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T ros2_action_msgs_msg_GoalInfo_common::get_arr(MDFactory_T& factory, const action_msgs::msg::GoalInfo* msg,
       MultiLibLoader loader, size_t size) {
    auto outArray = factory.createStructArray({size,1},{"MessageType","goal_id","stamp"});
    for(size_t ctr = 0; ctr < size; ctr++){
    outArray[ctr]["MessageType"] = factory.createCharArray("action_msgs/GoalInfo");
    // goal_id
    auto currentElement_goal_id = (msg + ctr)->goal_id;
    auto msgClassPtr_goal_id = getCommonObject<unique_identifier_msgs::msg::UUID>("ros2_unique_identifier_msgs_msg_UUID_common",loader);
    outArray[ctr]["goal_id"] = msgClassPtr_goal_id->get_arr(factory, &currentElement_goal_id, loader);
    // stamp
    auto currentElement_stamp = (msg + ctr)->stamp;
    auto msgClassPtr_stamp = getCommonObject<builtin_interfaces::msg::Time>("ros2_builtin_interfaces_msg_Time_common",loader);
    outArray[ctr]["stamp"] = msgClassPtr_stamp->get_arr(factory, &currentElement_stamp, loader);
    }
    return std::move(outArray);
  } 
class ACTION_MSGS_EXPORT ros2_action_msgs_GoalInfo_message : public ROS2MsgElementInterfaceFactory {
  public:
    virtual ~ros2_action_msgs_GoalInfo_message(){}
    virtual std::shared_ptr<MATLABPublisherInterface> generatePublisherInterface(ElementType /*type*/);
    virtual std::shared_ptr<MATLABSubscriberInterface> generateSubscriberInterface(ElementType /*type*/);
    virtual std::shared_ptr<void> generateCppMessage(ElementType /*type*/, const matlab::data::StructArray& /* arr */, MultiLibLoader /* loader */, std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* /*commonObjMap*/);
    virtual matlab::data::StructArray generateMLMessage(ElementType  /*type*/ ,void*  /* msg */, MultiLibLoader /* loader */ , std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* /*commonObjMap*/);
};  
  std::shared_ptr<MATLABPublisherInterface> 
          ros2_action_msgs_GoalInfo_message::generatePublisherInterface(ElementType /*type*/){
    return std::make_shared<ROS2PublisherImpl<action_msgs::msg::GoalInfo,ros2_action_msgs_msg_GoalInfo_common>>();
  }
  std::shared_ptr<MATLABSubscriberInterface> 
         ros2_action_msgs_GoalInfo_message::generateSubscriberInterface(ElementType /*type*/){
    return std::make_shared<ROS2SubscriberImpl<action_msgs::msg::GoalInfo,ros2_action_msgs_msg_GoalInfo_common>>();
  }
  std::shared_ptr<void> ros2_action_msgs_GoalInfo_message::generateCppMessage(ElementType /*type*/, 
                                           const matlab::data::StructArray& arr,
                                           MultiLibLoader loader,
                                           std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* commonObjMap){
    auto msg = std::make_shared<action_msgs::msg::GoalInfo>();
    ros2_action_msgs_msg_GoalInfo_common commonObj;
    commonObj.mCommonObjMap = commonObjMap;
    commonObj.copy_from_struct(msg.get(), arr[0], loader);
    return msg;
  }
  matlab::data::StructArray ros2_action_msgs_GoalInfo_message::generateMLMessage(ElementType  /*type*/ ,
                                                    void*  msg ,
                                                    MultiLibLoader  loader ,
                                                    std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>*  commonObjMap ){
    ros2_action_msgs_msg_GoalInfo_common commonObj;	
    commonObj.mCommonObjMap = commonObjMap;	
    MDFactory_T factory;
    return commonObj.get_arr(factory, (action_msgs::msg::GoalInfo*)msg, loader);			
 }
#include "class_loader/register_macro.hpp"
// Register the component with class_loader.
// This acts as a sort of entry point, allowing the component to be discoverable when its library
// is being loaded into a running process.
CLASS_LOADER_REGISTER_CLASS(ros2_action_msgs_msg_GoalInfo_common, MATLABROS2MsgInterface<action_msgs::msg::GoalInfo>)
CLASS_LOADER_REGISTER_CLASS(ros2_action_msgs_GoalInfo_message, ROS2MsgElementInterfaceFactory)
#ifdef _MSC_VER
#pragma warning(pop)
#else
#pragma GCC diagnostic pop
#endif //_MSC_VER