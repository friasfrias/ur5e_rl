// Copyright 2020-2022 The MathWorks, Inc.
// Common copy functions for action_msgs/GoalStatusArray
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
#include "action_msgs/msg/goal_status_array.hpp"
#include "visibility_control.h"
#include "class_loader/multi_library_class_loader.hpp"
#include "ROS2PubSubTemplates.hpp"
class ACTION_MSGS_EXPORT ros2_action_msgs_msg_GoalStatusArray_common : public MATLABROS2MsgInterface<action_msgs::msg::GoalStatusArray> {
  public:
    virtual ~ros2_action_msgs_msg_GoalStatusArray_common(){}
    virtual void copy_from_struct(action_msgs::msg::GoalStatusArray* msg, const matlab::data::Struct& arr, MultiLibLoader loader); 
    //----------------------------------------------------------------------------
    virtual MDArray_T get_arr(MDFactory_T& factory, const action_msgs::msg::GoalStatusArray* msg, MultiLibLoader loader, size_t size = 1);
};
  void ros2_action_msgs_msg_GoalStatusArray_common::copy_from_struct(action_msgs::msg::GoalStatusArray* msg, const matlab::data::Struct& arr,
               MultiLibLoader loader) {
    try {
        //status_list
        const matlab::data::StructArray status_list_arr = arr["status_list"];
        for (auto _status_listarr : status_list_arr) {
        	action_msgs::msg::GoalStatus _val;
        auto msgClassPtr_status_list = getCommonObject<action_msgs::msg::GoalStatus>("ros2_action_msgs_msg_GoalStatus_common",loader);
        msgClassPtr_status_list->copy_from_struct(&_val,_status_listarr,loader);
        	msg->status_list.push_back(_val);
        }
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'status_list' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'status_list' is wrong type; expected a struct.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T ros2_action_msgs_msg_GoalStatusArray_common::get_arr(MDFactory_T& factory, const action_msgs::msg::GoalStatusArray* msg,
       MultiLibLoader loader, size_t size) {
    auto outArray = factory.createStructArray({size,1},{"MessageType","status_list"});
    for(size_t ctr = 0; ctr < size; ctr++){
    outArray[ctr]["MessageType"] = factory.createCharArray("action_msgs/GoalStatusArray");
    // status_list
    auto currentElement_status_list = (msg + ctr)->status_list;
    auto msgClassPtr_status_list = getCommonObject<action_msgs::msg::GoalStatus>("ros2_action_msgs_msg_GoalStatus_common",loader);
    outArray[ctr]["status_list"] = msgClassPtr_status_list->get_arr(factory,&currentElement_status_list[0],loader,currentElement_status_list.size());
    }
    return std::move(outArray);
  } 
class ACTION_MSGS_EXPORT ros2_action_msgs_GoalStatusArray_message : public ROS2MsgElementInterfaceFactory {
  public:
    virtual ~ros2_action_msgs_GoalStatusArray_message(){}
    virtual std::shared_ptr<MATLABPublisherInterface> generatePublisherInterface(ElementType /*type*/);
    virtual std::shared_ptr<MATLABSubscriberInterface> generateSubscriberInterface(ElementType /*type*/);
    virtual std::shared_ptr<void> generateCppMessage(ElementType /*type*/, const matlab::data::StructArray& /* arr */, MultiLibLoader /* loader */, std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* /*commonObjMap*/);
    virtual matlab::data::StructArray generateMLMessage(ElementType  /*type*/ ,void*  /* msg */, MultiLibLoader /* loader */ , std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* /*commonObjMap*/);
};  
  std::shared_ptr<MATLABPublisherInterface> 
          ros2_action_msgs_GoalStatusArray_message::generatePublisherInterface(ElementType /*type*/){
    return std::make_shared<ROS2PublisherImpl<action_msgs::msg::GoalStatusArray,ros2_action_msgs_msg_GoalStatusArray_common>>();
  }
  std::shared_ptr<MATLABSubscriberInterface> 
         ros2_action_msgs_GoalStatusArray_message::generateSubscriberInterface(ElementType /*type*/){
    return std::make_shared<ROS2SubscriberImpl<action_msgs::msg::GoalStatusArray,ros2_action_msgs_msg_GoalStatusArray_common>>();
  }
  std::shared_ptr<void> ros2_action_msgs_GoalStatusArray_message::generateCppMessage(ElementType /*type*/, 
                                           const matlab::data::StructArray& arr,
                                           MultiLibLoader loader,
                                           std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* commonObjMap){
    auto msg = std::make_shared<action_msgs::msg::GoalStatusArray>();
    ros2_action_msgs_msg_GoalStatusArray_common commonObj;
    commonObj.mCommonObjMap = commonObjMap;
    commonObj.copy_from_struct(msg.get(), arr[0], loader);
    return msg;
  }
  matlab::data::StructArray ros2_action_msgs_GoalStatusArray_message::generateMLMessage(ElementType  /*type*/ ,
                                                    void*  msg ,
                                                    MultiLibLoader  loader ,
                                                    std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>*  commonObjMap ){
    ros2_action_msgs_msg_GoalStatusArray_common commonObj;	
    commonObj.mCommonObjMap = commonObjMap;	
    MDFactory_T factory;
    return commonObj.get_arr(factory, (action_msgs::msg::GoalStatusArray*)msg, loader);			
 }
#include "class_loader/register_macro.hpp"
// Register the component with class_loader.
// This acts as a sort of entry point, allowing the component to be discoverable when its library
// is being loaded into a running process.
CLASS_LOADER_REGISTER_CLASS(ros2_action_msgs_msg_GoalStatusArray_common, MATLABROS2MsgInterface<action_msgs::msg::GoalStatusArray>)
CLASS_LOADER_REGISTER_CLASS(ros2_action_msgs_GoalStatusArray_message, ROS2MsgElementInterfaceFactory)
#ifdef _MSC_VER
#pragma warning(pop)
#else
#pragma GCC diagnostic pop
#endif //_MSC_VER