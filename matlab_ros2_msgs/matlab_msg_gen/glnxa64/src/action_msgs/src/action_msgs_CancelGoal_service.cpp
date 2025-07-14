// Copyright 2021-2022 The MathWorks, Inc.
// Common copy functions for action_msgs/CancelGoalRequest
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
#include "action_msgs/srv/cancel_goal.hpp"
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
#include "ROS2ServiceTemplates.hpp"
class ACTION_MSGS_EXPORT ros2_action_msgs_msg_CancelGoalRequest_common : public MATLABROS2MsgInterface<action_msgs::srv::CancelGoal::Request> {
  public:
    virtual ~ros2_action_msgs_msg_CancelGoalRequest_common(){}
    virtual void copy_from_struct(action_msgs::srv::CancelGoal::Request* msg, const matlab::data::Struct& arr, MultiLibLoader loader); 
    virtual MDArray_T get_arr(MDFactory_T& factory, const action_msgs::srv::CancelGoal::Request* msg, MultiLibLoader loader, size_t size = 1);
};
  void ros2_action_msgs_msg_CancelGoalRequest_common::copy_from_struct(action_msgs::srv::CancelGoal::Request* msg, const matlab::data::Struct& arr,
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
  }
  //----------------------------------------------------------------------------
  MDArray_T ros2_action_msgs_msg_CancelGoalRequest_common::get_arr(MDFactory_T& factory, const action_msgs::srv::CancelGoal::Request* msg,
       MultiLibLoader loader, size_t size) {
    auto outArray = factory.createStructArray({size,1},{"MessageType","goal_info"});
    for(size_t ctr = 0; ctr < size; ctr++){
    outArray[ctr]["MessageType"] = factory.createCharArray("action_msgs/CancelGoalRequest");
    // goal_info
    auto currentElement_goal_info = (msg + ctr)->goal_info;
    auto msgClassPtr_goal_info = getCommonObject<action_msgs::msg::GoalInfo>("ros2_action_msgs_msg_GoalInfo_common",loader);
    outArray[ctr]["goal_info"] = msgClassPtr_goal_info->get_arr(factory, &currentElement_goal_info, loader);
    }
    return std::move(outArray);
  }
class ACTION_MSGS_EXPORT ros2_action_msgs_msg_CancelGoalResponse_common : public MATLABROS2MsgInterface<action_msgs::srv::CancelGoal::Response> {
  public:
    virtual ~ros2_action_msgs_msg_CancelGoalResponse_common(){}
    virtual void copy_from_struct(action_msgs::srv::CancelGoal::Response* msg, const matlab::data::Struct& arr, MultiLibLoader loader); 
    virtual MDArray_T get_arr(MDFactory_T& factory, const action_msgs::srv::CancelGoal::Response* msg, MultiLibLoader loader, size_t size = 1);
};
  void ros2_action_msgs_msg_CancelGoalResponse_common::copy_from_struct(action_msgs::srv::CancelGoal::Response* msg, const matlab::data::Struct& arr,
               MultiLibLoader loader) {
    try {
        //return_code
        const matlab::data::TypedArray<int8_t> return_code_arr = arr["return_code"];
        msg->return_code = return_code_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'return_code' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'return_code' is wrong type; expected a int8.");
    }
    try {
        //goals_canceling
        const matlab::data::StructArray goals_canceling_arr = arr["goals_canceling"];
        for (auto _goals_cancelingarr : goals_canceling_arr) {
        	action_msgs::msg::GoalInfo _val;
        auto msgClassPtr_goals_canceling = getCommonObject<action_msgs::msg::GoalInfo>("ros2_action_msgs_msg_GoalInfo_common",loader);
        msgClassPtr_goals_canceling->copy_from_struct(&_val,_goals_cancelingarr,loader);
        	msg->goals_canceling.push_back(_val);
        }
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'goals_canceling' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'goals_canceling' is wrong type; expected a struct.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T ros2_action_msgs_msg_CancelGoalResponse_common::get_arr(MDFactory_T& factory, const action_msgs::srv::CancelGoal::Response* msg,
       MultiLibLoader loader, size_t size) {
    auto outArray = factory.createStructArray({size,1},{"MessageType","ERROR_NONE","ERROR_REJECTED","ERROR_UNKNOWN_GOAL_ID","ERROR_GOAL_TERMINATED","return_code","goals_canceling"});
    for(size_t ctr = 0; ctr < size; ctr++){
    outArray[ctr]["MessageType"] = factory.createCharArray("action_msgs/CancelGoalResponse");
    // ERROR_NONE
    auto currentElement_ERROR_NONE = (msg + ctr)->ERROR_NONE;
    outArray[ctr]["ERROR_NONE"] = factory.createScalar(currentElement_ERROR_NONE);
    // ERROR_REJECTED
    auto currentElement_ERROR_REJECTED = (msg + ctr)->ERROR_REJECTED;
    outArray[ctr]["ERROR_REJECTED"] = factory.createScalar(currentElement_ERROR_REJECTED);
    // ERROR_UNKNOWN_GOAL_ID
    auto currentElement_ERROR_UNKNOWN_GOAL_ID = (msg + ctr)->ERROR_UNKNOWN_GOAL_ID;
    outArray[ctr]["ERROR_UNKNOWN_GOAL_ID"] = factory.createScalar(currentElement_ERROR_UNKNOWN_GOAL_ID);
    // ERROR_GOAL_TERMINATED
    auto currentElement_ERROR_GOAL_TERMINATED = (msg + ctr)->ERROR_GOAL_TERMINATED;
    outArray[ctr]["ERROR_GOAL_TERMINATED"] = factory.createScalar(currentElement_ERROR_GOAL_TERMINATED);
    // return_code
    auto currentElement_return_code = (msg + ctr)->return_code;
    outArray[ctr]["return_code"] = factory.createScalar(currentElement_return_code);
    // goals_canceling
    auto currentElement_goals_canceling = (msg + ctr)->goals_canceling;
    auto msgClassPtr_goals_canceling = getCommonObject<action_msgs::msg::GoalInfo>("ros2_action_msgs_msg_GoalInfo_common",loader);
    outArray[ctr]["goals_canceling"] = msgClassPtr_goals_canceling->get_arr(factory,&currentElement_goals_canceling[0],loader,currentElement_goals_canceling.size());
    }
    return std::move(outArray);
  } 
class ACTION_MSGS_EXPORT ros2_action_msgs_CancelGoal_service : public ROS2MsgElementInterfaceFactory {
  public:
    virtual ~ros2_action_msgs_CancelGoal_service(){}
    virtual std::shared_ptr<MATLABPublisherInterface> generatePublisherInterface(ElementType type);
    virtual std::shared_ptr<MATLABSubscriberInterface> generateSubscriberInterface(ElementType type);
    virtual std::shared_ptr<MATLABSvcServerInterface> generateSvcServerInterface();
    virtual std::shared_ptr<MATLABSvcClientInterface> generateSvcClientInterface();
    virtual std::shared_ptr<void> generateCppMessage(ElementType /*type*/, const matlab::data::StructArray& /* arr */, MultiLibLoader /* loader */, std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* /*commonObjMap*/);
    virtual matlab::data::StructArray generateMLMessage(ElementType  /*type*/ ,void*  /* msg */, MultiLibLoader /* loader */ , std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* /*commonObjMap*/);
};  
  std::shared_ptr<MATLABPublisherInterface> 
          ros2_action_msgs_CancelGoal_service::generatePublisherInterface(ElementType type){
    if(type == eRequest){
        return std::make_shared<ROS2PublisherImpl<action_msgs::srv::CancelGoal::Request,ros2_action_msgs_msg_CancelGoalRequest_common>>();
    }else if(type == eResponse){
        return std::make_shared<ROS2PublisherImpl<action_msgs::srv::CancelGoal::Response,ros2_action_msgs_msg_CancelGoalResponse_common>>();
    }else{
        throw std::invalid_argument("Wrong input, Expected 'Request' or 'Response'");
    }
  }
  std::shared_ptr<MATLABSubscriberInterface> 
          ros2_action_msgs_CancelGoal_service::generateSubscriberInterface(ElementType type){
    if(type == eRequest){
        return std::make_shared<ROS2SubscriberImpl<action_msgs::srv::CancelGoal::Request,ros2_action_msgs_msg_CancelGoalRequest_common>>();
    }else if(type == eResponse){
        return std::make_shared<ROS2SubscriberImpl<action_msgs::srv::CancelGoal::Response,ros2_action_msgs_msg_CancelGoalResponse_common>>();
    }else{
        throw std::invalid_argument("Wrong input, Expected 'Request' or 'Response'");
    }
  }
  std::shared_ptr<void> ros2_action_msgs_CancelGoal_service::generateCppMessage(ElementType type, 
                                           const matlab::data::StructArray& arr,
                                           MultiLibLoader loader,
                                           std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* commonObjMap){
    if(type == eRequest){
        auto msg = std::make_shared<action_msgs::srv::CancelGoal::Request>();
        ros2_action_msgs_msg_CancelGoalRequest_common commonObj;
        commonObj.mCommonObjMap = commonObjMap;
        commonObj.copy_from_struct(msg.get(), arr[0], loader);
        return msg;
    }else if(type == eResponse){
        auto msg = std::make_shared<action_msgs::srv::CancelGoal::Response>();
        ros2_action_msgs_msg_CancelGoalResponse_common commonObj;
        commonObj.mCommonObjMap = commonObjMap;
        commonObj.copy_from_struct(msg.get(), arr[0], loader);
        return msg;
    }else{
        throw std::invalid_argument("Wrong input, Expected 'Request' or 'Response'");
    }
  }
  std::shared_ptr<MATLABSvcServerInterface> 
          ros2_action_msgs_CancelGoal_service::generateSvcServerInterface(){
    return std::make_shared<ROS2SvcServerImpl<action_msgs::srv::CancelGoal,action_msgs::srv::CancelGoal::Request,action_msgs::srv::CancelGoal::Response,ros2_action_msgs_msg_CancelGoalRequest_common,ros2_action_msgs_msg_CancelGoalResponse_common>>();
  }
  std::shared_ptr<MATLABSvcClientInterface> 
          ros2_action_msgs_CancelGoal_service::generateSvcClientInterface(){
    return std::make_shared<ROS2SvcClientImpl<action_msgs::srv::CancelGoal,action_msgs::srv::CancelGoal::Request,action_msgs::srv::CancelGoal::Response,ros2_action_msgs_msg_CancelGoalRequest_common,ros2_action_msgs_msg_CancelGoalResponse_common,rclcpp::Client<action_msgs::srv::CancelGoal>::SharedFuture>>();
  }
  matlab::data::StructArray ros2_action_msgs_CancelGoal_service::generateMLMessage(ElementType type, 
                                                    void*  msgPtr ,
                                                    MultiLibLoader  loader ,
                                                    std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* commonObjMap){
    if(type == eRequest){
	    ros2_action_msgs_msg_CancelGoalRequest_common commonObj;	
        commonObj.mCommonObjMap = commonObjMap;
	    MDFactory_T factory;
	    return commonObj.get_arr(factory, (action_msgs::srv::CancelGoal::Request*)msgPtr, loader);
    }else if(type == eResponse){
        ros2_action_msgs_msg_CancelGoalResponse_common commonObj;	
        commonObj.mCommonObjMap = commonObjMap;	
	    MDFactory_T factory;
	    return commonObj.get_arr(factory, (action_msgs::srv::CancelGoal::Response*)msgPtr, loader);
    }else{
        throw std::invalid_argument("Wrong input, Expected 'Request' or 'Response'");
    }
  }
#include "class_loader/register_macro.hpp"
// Register the component with class_loader.
// This acts as a sort of entry point, allowing the component to be discoverable when its library
// is being loaded into a running process.
CLASS_LOADER_REGISTER_CLASS(ros2_action_msgs_msg_CancelGoalRequest_common, MATLABROS2MsgInterface<action_msgs::srv::CancelGoal::Request>)
CLASS_LOADER_REGISTER_CLASS(ros2_action_msgs_msg_CancelGoalResponse_common, MATLABROS2MsgInterface<action_msgs::srv::CancelGoal::Response>)
CLASS_LOADER_REGISTER_CLASS(ros2_action_msgs_CancelGoal_service, ROS2MsgElementInterfaceFactory)
#ifdef _MSC_VER
#pragma warning(pop)
#else
#pragma GCC diagnostic pop
#endif //_MSC_VER
//gen-1
