// Copyright 2021-2022 The MathWorks, Inc.
// Common copy functions for control_msgs/QueryTrajectoryStateRequest
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
#include "control_msgs/srv/query_trajectory_state.hpp"
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
class CONTROL_MSGS_EXPORT ros2_control_msgs_msg_QueryTrajectoryStateRequest_common : public MATLABROS2MsgInterface<control_msgs::srv::QueryTrajectoryState::Request> {
  public:
    virtual ~ros2_control_msgs_msg_QueryTrajectoryStateRequest_common(){}
    virtual void copy_from_struct(control_msgs::srv::QueryTrajectoryState::Request* msg, const matlab::data::Struct& arr, MultiLibLoader loader); 
    virtual MDArray_T get_arr(MDFactory_T& factory, const control_msgs::srv::QueryTrajectoryState::Request* msg, MultiLibLoader loader, size_t size = 1);
};
  void ros2_control_msgs_msg_QueryTrajectoryStateRequest_common::copy_from_struct(control_msgs::srv::QueryTrajectoryState::Request* msg, const matlab::data::Struct& arr,
               MultiLibLoader loader) {
    try {
        //time
        const matlab::data::StructArray time_arr = arr["time"];
        auto msgClassPtr_time = getCommonObject<builtin_interfaces::msg::Time>("ros2_builtin_interfaces_msg_Time_common",loader);
        msgClassPtr_time->copy_from_struct(&msg->time,time_arr[0],loader);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'time' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'time' is wrong type; expected a struct.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T ros2_control_msgs_msg_QueryTrajectoryStateRequest_common::get_arr(MDFactory_T& factory, const control_msgs::srv::QueryTrajectoryState::Request* msg,
       MultiLibLoader loader, size_t size) {
    auto outArray = factory.createStructArray({size,1},{"MessageType","time"});
    for(size_t ctr = 0; ctr < size; ctr++){
    outArray[ctr]["MessageType"] = factory.createCharArray("control_msgs/QueryTrajectoryStateRequest");
    // time
    auto currentElement_time = (msg + ctr)->time;
    auto msgClassPtr_time = getCommonObject<builtin_interfaces::msg::Time>("ros2_builtin_interfaces_msg_Time_common",loader);
    outArray[ctr]["time"] = msgClassPtr_time->get_arr(factory, &currentElement_time, loader);
    }
    return std::move(outArray);
  }
class CONTROL_MSGS_EXPORT ros2_control_msgs_msg_QueryTrajectoryStateResponse_common : public MATLABROS2MsgInterface<control_msgs::srv::QueryTrajectoryState::Response> {
  public:
    virtual ~ros2_control_msgs_msg_QueryTrajectoryStateResponse_common(){}
    virtual void copy_from_struct(control_msgs::srv::QueryTrajectoryState::Response* msg, const matlab::data::Struct& arr, MultiLibLoader loader); 
    virtual MDArray_T get_arr(MDFactory_T& factory, const control_msgs::srv::QueryTrajectoryState::Response* msg, MultiLibLoader loader, size_t size = 1);
};
  void ros2_control_msgs_msg_QueryTrajectoryStateResponse_common::copy_from_struct(control_msgs::srv::QueryTrajectoryState::Response* msg, const matlab::data::Struct& arr,
               MultiLibLoader loader) {
    try {
        //success
        const matlab::data::TypedArray<bool> success_arr = arr["success"];
        msg->success = success_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'success' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'success' is wrong type; expected a logical.");
    }
    try {
        //message
        const matlab::data::CharArray message_arr = arr["message"];
        msg->message = message_arr.toAscii();
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'message' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'message' is wrong type; expected a string.");
    }
    try {
        //name
        const matlab::data::CellArray name_cellarr = arr["name"];
        size_t nelem = name_cellarr.getNumberOfElements();
        for (size_t idx=0; idx < nelem; ++idx){
        	const matlab::data::CharArray name_arr = name_cellarr[idx];
        	msg->name.push_back(name_arr.toAscii());
        }
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'name' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'name' is wrong type; expected a string.");
    }
    try {
        //position
        const matlab::data::TypedArray<double> position_arr = arr["position"];
        size_t nelem = position_arr.getNumberOfElements();
        	msg->position.resize(nelem);
        	std::copy(position_arr.begin(), position_arr.begin()+nelem, msg->position.begin());
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'position' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'position' is wrong type; expected a double.");
    }
    try {
        //velocity
        const matlab::data::TypedArray<double> velocity_arr = arr["velocity"];
        size_t nelem = velocity_arr.getNumberOfElements();
        	msg->velocity.resize(nelem);
        	std::copy(velocity_arr.begin(), velocity_arr.begin()+nelem, msg->velocity.begin());
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'velocity' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'velocity' is wrong type; expected a double.");
    }
    try {
        //acceleration
        const matlab::data::TypedArray<double> acceleration_arr = arr["acceleration"];
        size_t nelem = acceleration_arr.getNumberOfElements();
        	msg->acceleration.resize(nelem);
        	std::copy(acceleration_arr.begin(), acceleration_arr.begin()+nelem, msg->acceleration.begin());
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'acceleration' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'acceleration' is wrong type; expected a double.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T ros2_control_msgs_msg_QueryTrajectoryStateResponse_common::get_arr(MDFactory_T& factory, const control_msgs::srv::QueryTrajectoryState::Response* msg,
       MultiLibLoader loader, size_t size) {
    auto outArray = factory.createStructArray({size,1},{"MessageType","success","message","name","position","velocity","acceleration"});
    for(size_t ctr = 0; ctr < size; ctr++){
    outArray[ctr]["MessageType"] = factory.createCharArray("control_msgs/QueryTrajectoryStateResponse");
    // success
    auto currentElement_success = (msg + ctr)->success;
    outArray[ctr]["success"] = factory.createScalar(currentElement_success);
    // message
    auto currentElement_message = (msg + ctr)->message;
    outArray[ctr]["message"] = factory.createCharArray(currentElement_message);
    // name
    auto currentElement_name = (msg + ctr)->name;
    auto nameoutCell = factory.createCellArray({currentElement_name.size(),1});
    for(size_t idxin = 0; idxin < currentElement_name.size(); ++ idxin){
    	nameoutCell[idxin] = factory.createCharArray(currentElement_name[idxin]);
    }
    outArray[ctr]["name"] = nameoutCell;
    // position
    auto currentElement_position = (msg + ctr)->position;
    outArray[ctr]["position"] = factory.createArray<control_msgs::srv::QueryTrajectoryState::Response::_position_type::const_iterator, double>({currentElement_position.size(), 1}, currentElement_position.begin(), currentElement_position.end());
    // velocity
    auto currentElement_velocity = (msg + ctr)->velocity;
    outArray[ctr]["velocity"] = factory.createArray<control_msgs::srv::QueryTrajectoryState::Response::_velocity_type::const_iterator, double>({currentElement_velocity.size(), 1}, currentElement_velocity.begin(), currentElement_velocity.end());
    // acceleration
    auto currentElement_acceleration = (msg + ctr)->acceleration;
    outArray[ctr]["acceleration"] = factory.createArray<control_msgs::srv::QueryTrajectoryState::Response::_acceleration_type::const_iterator, double>({currentElement_acceleration.size(), 1}, currentElement_acceleration.begin(), currentElement_acceleration.end());
    }
    return std::move(outArray);
  } 
class CONTROL_MSGS_EXPORT ros2_control_msgs_QueryTrajectoryState_service : public ROS2MsgElementInterfaceFactory {
  public:
    virtual ~ros2_control_msgs_QueryTrajectoryState_service(){}
    virtual std::shared_ptr<MATLABPublisherInterface> generatePublisherInterface(ElementType type);
    virtual std::shared_ptr<MATLABSubscriberInterface> generateSubscriberInterface(ElementType type);
    virtual std::shared_ptr<MATLABSvcServerInterface> generateSvcServerInterface();
    virtual std::shared_ptr<MATLABSvcClientInterface> generateSvcClientInterface();
    virtual std::shared_ptr<void> generateCppMessage(ElementType /*type*/, const matlab::data::StructArray& /* arr */, MultiLibLoader /* loader */, std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* /*commonObjMap*/);
    virtual matlab::data::StructArray generateMLMessage(ElementType  /*type*/ ,void*  /* msg */, MultiLibLoader /* loader */ , std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* /*commonObjMap*/);
};  
  std::shared_ptr<MATLABPublisherInterface> 
          ros2_control_msgs_QueryTrajectoryState_service::generatePublisherInterface(ElementType type){
    if(type == eRequest){
        return std::make_shared<ROS2PublisherImpl<control_msgs::srv::QueryTrajectoryState::Request,ros2_control_msgs_msg_QueryTrajectoryStateRequest_common>>();
    }else if(type == eResponse){
        return std::make_shared<ROS2PublisherImpl<control_msgs::srv::QueryTrajectoryState::Response,ros2_control_msgs_msg_QueryTrajectoryStateResponse_common>>();
    }else{
        throw std::invalid_argument("Wrong input, Expected 'Request' or 'Response'");
    }
  }
  std::shared_ptr<MATLABSubscriberInterface> 
          ros2_control_msgs_QueryTrajectoryState_service::generateSubscriberInterface(ElementType type){
    if(type == eRequest){
        return std::make_shared<ROS2SubscriberImpl<control_msgs::srv::QueryTrajectoryState::Request,ros2_control_msgs_msg_QueryTrajectoryStateRequest_common>>();
    }else if(type == eResponse){
        return std::make_shared<ROS2SubscriberImpl<control_msgs::srv::QueryTrajectoryState::Response,ros2_control_msgs_msg_QueryTrajectoryStateResponse_common>>();
    }else{
        throw std::invalid_argument("Wrong input, Expected 'Request' or 'Response'");
    }
  }
  std::shared_ptr<void> ros2_control_msgs_QueryTrajectoryState_service::generateCppMessage(ElementType type, 
                                           const matlab::data::StructArray& arr,
                                           MultiLibLoader loader,
                                           std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* commonObjMap){
    if(type == eRequest){
        auto msg = std::make_shared<control_msgs::srv::QueryTrajectoryState::Request>();
        ros2_control_msgs_msg_QueryTrajectoryStateRequest_common commonObj;
        commonObj.mCommonObjMap = commonObjMap;
        commonObj.copy_from_struct(msg.get(), arr[0], loader);
        return msg;
    }else if(type == eResponse){
        auto msg = std::make_shared<control_msgs::srv::QueryTrajectoryState::Response>();
        ros2_control_msgs_msg_QueryTrajectoryStateResponse_common commonObj;
        commonObj.mCommonObjMap = commonObjMap;
        commonObj.copy_from_struct(msg.get(), arr[0], loader);
        return msg;
    }else{
        throw std::invalid_argument("Wrong input, Expected 'Request' or 'Response'");
    }
  }
  std::shared_ptr<MATLABSvcServerInterface> 
          ros2_control_msgs_QueryTrajectoryState_service::generateSvcServerInterface(){
    return std::make_shared<ROS2SvcServerImpl<control_msgs::srv::QueryTrajectoryState,control_msgs::srv::QueryTrajectoryState::Request,control_msgs::srv::QueryTrajectoryState::Response,ros2_control_msgs_msg_QueryTrajectoryStateRequest_common,ros2_control_msgs_msg_QueryTrajectoryStateResponse_common>>();
  }
  std::shared_ptr<MATLABSvcClientInterface> 
          ros2_control_msgs_QueryTrajectoryState_service::generateSvcClientInterface(){
    return std::make_shared<ROS2SvcClientImpl<control_msgs::srv::QueryTrajectoryState,control_msgs::srv::QueryTrajectoryState::Request,control_msgs::srv::QueryTrajectoryState::Response,ros2_control_msgs_msg_QueryTrajectoryStateRequest_common,ros2_control_msgs_msg_QueryTrajectoryStateResponse_common,rclcpp::Client<control_msgs::srv::QueryTrajectoryState>::SharedFuture>>();
  }
  matlab::data::StructArray ros2_control_msgs_QueryTrajectoryState_service::generateMLMessage(ElementType type, 
                                                    void*  msgPtr ,
                                                    MultiLibLoader  loader ,
                                                    std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* commonObjMap){
    if(type == eRequest){
	    ros2_control_msgs_msg_QueryTrajectoryStateRequest_common commonObj;	
        commonObj.mCommonObjMap = commonObjMap;
	    MDFactory_T factory;
	    return commonObj.get_arr(factory, (control_msgs::srv::QueryTrajectoryState::Request*)msgPtr, loader);
    }else if(type == eResponse){
        ros2_control_msgs_msg_QueryTrajectoryStateResponse_common commonObj;	
        commonObj.mCommonObjMap = commonObjMap;	
	    MDFactory_T factory;
	    return commonObj.get_arr(factory, (control_msgs::srv::QueryTrajectoryState::Response*)msgPtr, loader);
    }else{
        throw std::invalid_argument("Wrong input, Expected 'Request' or 'Response'");
    }
  }
#include "class_loader/register_macro.hpp"
// Register the component with class_loader.
// This acts as a sort of entry point, allowing the component to be discoverable when its library
// is being loaded into a running process.
CLASS_LOADER_REGISTER_CLASS(ros2_control_msgs_msg_QueryTrajectoryStateRequest_common, MATLABROS2MsgInterface<control_msgs::srv::QueryTrajectoryState::Request>)
CLASS_LOADER_REGISTER_CLASS(ros2_control_msgs_msg_QueryTrajectoryStateResponse_common, MATLABROS2MsgInterface<control_msgs::srv::QueryTrajectoryState::Response>)
CLASS_LOADER_REGISTER_CLASS(ros2_control_msgs_QueryTrajectoryState_service, ROS2MsgElementInterfaceFactory)
#ifdef _MSC_VER
#pragma warning(pop)
#else
#pragma GCC diagnostic pop
#endif //_MSC_VER
//gen-1
