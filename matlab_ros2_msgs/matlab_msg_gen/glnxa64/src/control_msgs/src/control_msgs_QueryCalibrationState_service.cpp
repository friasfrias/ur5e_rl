// Copyright 2021-2022 The MathWorks, Inc.
// Common copy functions for control_msgs/QueryCalibrationStateRequest
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
#include "control_msgs/srv/query_calibration_state.hpp"
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
class CONTROL_MSGS_EXPORT ros2_control_msgs_msg_QueryCalibrationStateRequest_common : public MATLABROS2MsgInterface<control_msgs::srv::QueryCalibrationState::Request> {
  public:
    virtual ~ros2_control_msgs_msg_QueryCalibrationStateRequest_common(){}
    virtual void copy_from_struct(control_msgs::srv::QueryCalibrationState::Request* msg, const matlab::data::Struct& arr, MultiLibLoader loader); 
    virtual MDArray_T get_arr(MDFactory_T& factory, const control_msgs::srv::QueryCalibrationState::Request* msg, MultiLibLoader loader, size_t size = 1);
};
  void ros2_control_msgs_msg_QueryCalibrationStateRequest_common::copy_from_struct(control_msgs::srv::QueryCalibrationState::Request* msg, const matlab::data::Struct& arr,
               MultiLibLoader loader) {
  }
  //----------------------------------------------------------------------------
  MDArray_T ros2_control_msgs_msg_QueryCalibrationStateRequest_common::get_arr(MDFactory_T& factory, const control_msgs::srv::QueryCalibrationState::Request* msg,
       MultiLibLoader loader, size_t size) {
    auto outArray = factory.createStructArray({size,1},{"MessageType"});
    for(size_t ctr = 0; ctr < size; ctr++){
    outArray[ctr]["MessageType"] = factory.createCharArray("control_msgs/QueryCalibrationStateRequest");
    }
    return std::move(outArray);
  }
class CONTROL_MSGS_EXPORT ros2_control_msgs_msg_QueryCalibrationStateResponse_common : public MATLABROS2MsgInterface<control_msgs::srv::QueryCalibrationState::Response> {
  public:
    virtual ~ros2_control_msgs_msg_QueryCalibrationStateResponse_common(){}
    virtual void copy_from_struct(control_msgs::srv::QueryCalibrationState::Response* msg, const matlab::data::Struct& arr, MultiLibLoader loader); 
    virtual MDArray_T get_arr(MDFactory_T& factory, const control_msgs::srv::QueryCalibrationState::Response* msg, MultiLibLoader loader, size_t size = 1);
};
  void ros2_control_msgs_msg_QueryCalibrationStateResponse_common::copy_from_struct(control_msgs::srv::QueryCalibrationState::Response* msg, const matlab::data::Struct& arr,
               MultiLibLoader loader) {
    try {
        //is_calibrated
        const matlab::data::TypedArray<bool> is_calibrated_arr = arr["is_calibrated"];
        msg->is_calibrated = is_calibrated_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'is_calibrated' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'is_calibrated' is wrong type; expected a logical.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T ros2_control_msgs_msg_QueryCalibrationStateResponse_common::get_arr(MDFactory_T& factory, const control_msgs::srv::QueryCalibrationState::Response* msg,
       MultiLibLoader loader, size_t size) {
    auto outArray = factory.createStructArray({size,1},{"MessageType","is_calibrated"});
    for(size_t ctr = 0; ctr < size; ctr++){
    outArray[ctr]["MessageType"] = factory.createCharArray("control_msgs/QueryCalibrationStateResponse");
    // is_calibrated
    auto currentElement_is_calibrated = (msg + ctr)->is_calibrated;
    outArray[ctr]["is_calibrated"] = factory.createScalar(currentElement_is_calibrated);
    }
    return std::move(outArray);
  } 
class CONTROL_MSGS_EXPORT ros2_control_msgs_QueryCalibrationState_service : public ROS2MsgElementInterfaceFactory {
  public:
    virtual ~ros2_control_msgs_QueryCalibrationState_service(){}
    virtual std::shared_ptr<MATLABPublisherInterface> generatePublisherInterface(ElementType type);
    virtual std::shared_ptr<MATLABSubscriberInterface> generateSubscriberInterface(ElementType type);
    virtual std::shared_ptr<MATLABSvcServerInterface> generateSvcServerInterface();
    virtual std::shared_ptr<MATLABSvcClientInterface> generateSvcClientInterface();
    virtual std::shared_ptr<void> generateCppMessage(ElementType /*type*/, const matlab::data::StructArray& /* arr */, MultiLibLoader /* loader */, std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* /*commonObjMap*/);
    virtual matlab::data::StructArray generateMLMessage(ElementType  /*type*/ ,void*  /* msg */, MultiLibLoader /* loader */ , std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* /*commonObjMap*/);
};  
  std::shared_ptr<MATLABPublisherInterface> 
          ros2_control_msgs_QueryCalibrationState_service::generatePublisherInterface(ElementType type){
    if(type == eRequest){
        return std::make_shared<ROS2PublisherImpl<control_msgs::srv::QueryCalibrationState::Request,ros2_control_msgs_msg_QueryCalibrationStateRequest_common>>();
    }else if(type == eResponse){
        return std::make_shared<ROS2PublisherImpl<control_msgs::srv::QueryCalibrationState::Response,ros2_control_msgs_msg_QueryCalibrationStateResponse_common>>();
    }else{
        throw std::invalid_argument("Wrong input, Expected 'Request' or 'Response'");
    }
  }
  std::shared_ptr<MATLABSubscriberInterface> 
          ros2_control_msgs_QueryCalibrationState_service::generateSubscriberInterface(ElementType type){
    if(type == eRequest){
        return std::make_shared<ROS2SubscriberImpl<control_msgs::srv::QueryCalibrationState::Request,ros2_control_msgs_msg_QueryCalibrationStateRequest_common>>();
    }else if(type == eResponse){
        return std::make_shared<ROS2SubscriberImpl<control_msgs::srv::QueryCalibrationState::Response,ros2_control_msgs_msg_QueryCalibrationStateResponse_common>>();
    }else{
        throw std::invalid_argument("Wrong input, Expected 'Request' or 'Response'");
    }
  }
  std::shared_ptr<void> ros2_control_msgs_QueryCalibrationState_service::generateCppMessage(ElementType type, 
                                           const matlab::data::StructArray& arr,
                                           MultiLibLoader loader,
                                           std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* commonObjMap){
    if(type == eRequest){
        auto msg = std::make_shared<control_msgs::srv::QueryCalibrationState::Request>();
        ros2_control_msgs_msg_QueryCalibrationStateRequest_common commonObj;
        commonObj.mCommonObjMap = commonObjMap;
        commonObj.copy_from_struct(msg.get(), arr[0], loader);
        return msg;
    }else if(type == eResponse){
        auto msg = std::make_shared<control_msgs::srv::QueryCalibrationState::Response>();
        ros2_control_msgs_msg_QueryCalibrationStateResponse_common commonObj;
        commonObj.mCommonObjMap = commonObjMap;
        commonObj.copy_from_struct(msg.get(), arr[0], loader);
        return msg;
    }else{
        throw std::invalid_argument("Wrong input, Expected 'Request' or 'Response'");
    }
  }
  std::shared_ptr<MATLABSvcServerInterface> 
          ros2_control_msgs_QueryCalibrationState_service::generateSvcServerInterface(){
    return std::make_shared<ROS2SvcServerImpl<control_msgs::srv::QueryCalibrationState,control_msgs::srv::QueryCalibrationState::Request,control_msgs::srv::QueryCalibrationState::Response,ros2_control_msgs_msg_QueryCalibrationStateRequest_common,ros2_control_msgs_msg_QueryCalibrationStateResponse_common>>();
  }
  std::shared_ptr<MATLABSvcClientInterface> 
          ros2_control_msgs_QueryCalibrationState_service::generateSvcClientInterface(){
    return std::make_shared<ROS2SvcClientImpl<control_msgs::srv::QueryCalibrationState,control_msgs::srv::QueryCalibrationState::Request,control_msgs::srv::QueryCalibrationState::Response,ros2_control_msgs_msg_QueryCalibrationStateRequest_common,ros2_control_msgs_msg_QueryCalibrationStateResponse_common,rclcpp::Client<control_msgs::srv::QueryCalibrationState>::SharedFuture>>();
  }
  matlab::data::StructArray ros2_control_msgs_QueryCalibrationState_service::generateMLMessage(ElementType type, 
                                                    void*  msgPtr ,
                                                    MultiLibLoader  loader ,
                                                    std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* commonObjMap){
    if(type == eRequest){
	    ros2_control_msgs_msg_QueryCalibrationStateRequest_common commonObj;	
        commonObj.mCommonObjMap = commonObjMap;
	    MDFactory_T factory;
	    return commonObj.get_arr(factory, (control_msgs::srv::QueryCalibrationState::Request*)msgPtr, loader);
    }else if(type == eResponse){
        ros2_control_msgs_msg_QueryCalibrationStateResponse_common commonObj;	
        commonObj.mCommonObjMap = commonObjMap;	
	    MDFactory_T factory;
	    return commonObj.get_arr(factory, (control_msgs::srv::QueryCalibrationState::Response*)msgPtr, loader);
    }else{
        throw std::invalid_argument("Wrong input, Expected 'Request' or 'Response'");
    }
  }
#include "class_loader/register_macro.hpp"
// Register the component with class_loader.
// This acts as a sort of entry point, allowing the component to be discoverable when its library
// is being loaded into a running process.
CLASS_LOADER_REGISTER_CLASS(ros2_control_msgs_msg_QueryCalibrationStateRequest_common, MATLABROS2MsgInterface<control_msgs::srv::QueryCalibrationState::Request>)
CLASS_LOADER_REGISTER_CLASS(ros2_control_msgs_msg_QueryCalibrationStateResponse_common, MATLABROS2MsgInterface<control_msgs::srv::QueryCalibrationState::Response>)
CLASS_LOADER_REGISTER_CLASS(ros2_control_msgs_QueryCalibrationState_service, ROS2MsgElementInterfaceFactory)
#ifdef _MSC_VER
#pragma warning(pop)
#else
#pragma GCC diagnostic pop
#endif //_MSC_VER
//gen-1
