// Copyright 2021-2022 The MathWorks, Inc.
// Common copy functions for sensor_msgs/SetCameraInfoRequest
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
#include "sensor_msgs/srv/set_camera_info.hpp"
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
class SENSOR_MSGS_EXPORT ros2_sensor_msgs_msg_SetCameraInfoRequest_common : public MATLABROS2MsgInterface<sensor_msgs::srv::SetCameraInfo::Request> {
  public:
    virtual ~ros2_sensor_msgs_msg_SetCameraInfoRequest_common(){}
    virtual void copy_from_struct(sensor_msgs::srv::SetCameraInfo::Request* msg, const matlab::data::Struct& arr, MultiLibLoader loader); 
    virtual MDArray_T get_arr(MDFactory_T& factory, const sensor_msgs::srv::SetCameraInfo::Request* msg, MultiLibLoader loader, size_t size = 1);
};
  void ros2_sensor_msgs_msg_SetCameraInfoRequest_common::copy_from_struct(sensor_msgs::srv::SetCameraInfo::Request* msg, const matlab::data::Struct& arr,
               MultiLibLoader loader) {
    try {
        //camera_info
        const matlab::data::StructArray camera_info_arr = arr["camera_info"];
        auto msgClassPtr_camera_info = getCommonObject<sensor_msgs::msg::CameraInfo>("ros2_sensor_msgs_msg_CameraInfo_common",loader);
        msgClassPtr_camera_info->copy_from_struct(&msg->camera_info,camera_info_arr[0],loader);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'camera_info' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'camera_info' is wrong type; expected a struct.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T ros2_sensor_msgs_msg_SetCameraInfoRequest_common::get_arr(MDFactory_T& factory, const sensor_msgs::srv::SetCameraInfo::Request* msg,
       MultiLibLoader loader, size_t size) {
    auto outArray = factory.createStructArray({size,1},{"MessageType","camera_info"});
    for(size_t ctr = 0; ctr < size; ctr++){
    outArray[ctr]["MessageType"] = factory.createCharArray("sensor_msgs/SetCameraInfoRequest");
    // camera_info
    auto currentElement_camera_info = (msg + ctr)->camera_info;
    auto msgClassPtr_camera_info = getCommonObject<sensor_msgs::msg::CameraInfo>("ros2_sensor_msgs_msg_CameraInfo_common",loader);
    outArray[ctr]["camera_info"] = msgClassPtr_camera_info->get_arr(factory, &currentElement_camera_info, loader);
    }
    return std::move(outArray);
  }
class SENSOR_MSGS_EXPORT ros2_sensor_msgs_msg_SetCameraInfoResponse_common : public MATLABROS2MsgInterface<sensor_msgs::srv::SetCameraInfo::Response> {
  public:
    virtual ~ros2_sensor_msgs_msg_SetCameraInfoResponse_common(){}
    virtual void copy_from_struct(sensor_msgs::srv::SetCameraInfo::Response* msg, const matlab::data::Struct& arr, MultiLibLoader loader); 
    virtual MDArray_T get_arr(MDFactory_T& factory, const sensor_msgs::srv::SetCameraInfo::Response* msg, MultiLibLoader loader, size_t size = 1);
};
  void ros2_sensor_msgs_msg_SetCameraInfoResponse_common::copy_from_struct(sensor_msgs::srv::SetCameraInfo::Response* msg, const matlab::data::Struct& arr,
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
        //status_message
        const matlab::data::CharArray status_message_arr = arr["status_message"];
        msg->status_message = status_message_arr.toAscii();
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'status_message' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'status_message' is wrong type; expected a string.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T ros2_sensor_msgs_msg_SetCameraInfoResponse_common::get_arr(MDFactory_T& factory, const sensor_msgs::srv::SetCameraInfo::Response* msg,
       MultiLibLoader loader, size_t size) {
    auto outArray = factory.createStructArray({size,1},{"MessageType","success","status_message"});
    for(size_t ctr = 0; ctr < size; ctr++){
    outArray[ctr]["MessageType"] = factory.createCharArray("sensor_msgs/SetCameraInfoResponse");
    // success
    auto currentElement_success = (msg + ctr)->success;
    outArray[ctr]["success"] = factory.createScalar(currentElement_success);
    // status_message
    auto currentElement_status_message = (msg + ctr)->status_message;
    outArray[ctr]["status_message"] = factory.createCharArray(currentElement_status_message);
    }
    return std::move(outArray);
  } 
class SENSOR_MSGS_EXPORT ros2_sensor_msgs_SetCameraInfo_service : public ROS2MsgElementInterfaceFactory {
  public:
    virtual ~ros2_sensor_msgs_SetCameraInfo_service(){}
    virtual std::shared_ptr<MATLABPublisherInterface> generatePublisherInterface(ElementType type);
    virtual std::shared_ptr<MATLABSubscriberInterface> generateSubscriberInterface(ElementType type);
    virtual std::shared_ptr<MATLABSvcServerInterface> generateSvcServerInterface();
    virtual std::shared_ptr<MATLABSvcClientInterface> generateSvcClientInterface();
    virtual std::shared_ptr<void> generateCppMessage(ElementType /*type*/, const matlab::data::StructArray& /* arr */, MultiLibLoader /* loader */, std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* /*commonObjMap*/);
    virtual matlab::data::StructArray generateMLMessage(ElementType  /*type*/ ,void*  /* msg */, MultiLibLoader /* loader */ , std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* /*commonObjMap*/);
};  
  std::shared_ptr<MATLABPublisherInterface> 
          ros2_sensor_msgs_SetCameraInfo_service::generatePublisherInterface(ElementType type){
    if(type == eRequest){
        return std::make_shared<ROS2PublisherImpl<sensor_msgs::srv::SetCameraInfo::Request,ros2_sensor_msgs_msg_SetCameraInfoRequest_common>>();
    }else if(type == eResponse){
        return std::make_shared<ROS2PublisherImpl<sensor_msgs::srv::SetCameraInfo::Response,ros2_sensor_msgs_msg_SetCameraInfoResponse_common>>();
    }else{
        throw std::invalid_argument("Wrong input, Expected 'Request' or 'Response'");
    }
  }
  std::shared_ptr<MATLABSubscriberInterface> 
          ros2_sensor_msgs_SetCameraInfo_service::generateSubscriberInterface(ElementType type){
    if(type == eRequest){
        return std::make_shared<ROS2SubscriberImpl<sensor_msgs::srv::SetCameraInfo::Request,ros2_sensor_msgs_msg_SetCameraInfoRequest_common>>();
    }else if(type == eResponse){
        return std::make_shared<ROS2SubscriberImpl<sensor_msgs::srv::SetCameraInfo::Response,ros2_sensor_msgs_msg_SetCameraInfoResponse_common>>();
    }else{
        throw std::invalid_argument("Wrong input, Expected 'Request' or 'Response'");
    }
  }
  std::shared_ptr<void> ros2_sensor_msgs_SetCameraInfo_service::generateCppMessage(ElementType type, 
                                           const matlab::data::StructArray& arr,
                                           MultiLibLoader loader,
                                           std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* commonObjMap){
    if(type == eRequest){
        auto msg = std::make_shared<sensor_msgs::srv::SetCameraInfo::Request>();
        ros2_sensor_msgs_msg_SetCameraInfoRequest_common commonObj;
        commonObj.mCommonObjMap = commonObjMap;
        commonObj.copy_from_struct(msg.get(), arr[0], loader);
        return msg;
    }else if(type == eResponse){
        auto msg = std::make_shared<sensor_msgs::srv::SetCameraInfo::Response>();
        ros2_sensor_msgs_msg_SetCameraInfoResponse_common commonObj;
        commonObj.mCommonObjMap = commonObjMap;
        commonObj.copy_from_struct(msg.get(), arr[0], loader);
        return msg;
    }else{
        throw std::invalid_argument("Wrong input, Expected 'Request' or 'Response'");
    }
  }
  std::shared_ptr<MATLABSvcServerInterface> 
          ros2_sensor_msgs_SetCameraInfo_service::generateSvcServerInterface(){
    return std::make_shared<ROS2SvcServerImpl<sensor_msgs::srv::SetCameraInfo,sensor_msgs::srv::SetCameraInfo::Request,sensor_msgs::srv::SetCameraInfo::Response,ros2_sensor_msgs_msg_SetCameraInfoRequest_common,ros2_sensor_msgs_msg_SetCameraInfoResponse_common>>();
  }
  std::shared_ptr<MATLABSvcClientInterface> 
          ros2_sensor_msgs_SetCameraInfo_service::generateSvcClientInterface(){
    return std::make_shared<ROS2SvcClientImpl<sensor_msgs::srv::SetCameraInfo,sensor_msgs::srv::SetCameraInfo::Request,sensor_msgs::srv::SetCameraInfo::Response,ros2_sensor_msgs_msg_SetCameraInfoRequest_common,ros2_sensor_msgs_msg_SetCameraInfoResponse_common,rclcpp::Client<sensor_msgs::srv::SetCameraInfo>::SharedFuture>>();
  }
  matlab::data::StructArray ros2_sensor_msgs_SetCameraInfo_service::generateMLMessage(ElementType type, 
                                                    void*  msgPtr ,
                                                    MultiLibLoader  loader ,
                                                    std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* commonObjMap){
    if(type == eRequest){
	    ros2_sensor_msgs_msg_SetCameraInfoRequest_common commonObj;	
        commonObj.mCommonObjMap = commonObjMap;
	    MDFactory_T factory;
	    return commonObj.get_arr(factory, (sensor_msgs::srv::SetCameraInfo::Request*)msgPtr, loader);
    }else if(type == eResponse){
        ros2_sensor_msgs_msg_SetCameraInfoResponse_common commonObj;	
        commonObj.mCommonObjMap = commonObjMap;	
	    MDFactory_T factory;
	    return commonObj.get_arr(factory, (sensor_msgs::srv::SetCameraInfo::Response*)msgPtr, loader);
    }else{
        throw std::invalid_argument("Wrong input, Expected 'Request' or 'Response'");
    }
  }
#include "class_loader/register_macro.hpp"
// Register the component with class_loader.
// This acts as a sort of entry point, allowing the component to be discoverable when its library
// is being loaded into a running process.
CLASS_LOADER_REGISTER_CLASS(ros2_sensor_msgs_msg_SetCameraInfoRequest_common, MATLABROS2MsgInterface<sensor_msgs::srv::SetCameraInfo::Request>)
CLASS_LOADER_REGISTER_CLASS(ros2_sensor_msgs_msg_SetCameraInfoResponse_common, MATLABROS2MsgInterface<sensor_msgs::srv::SetCameraInfo::Response>)
CLASS_LOADER_REGISTER_CLASS(ros2_sensor_msgs_SetCameraInfo_service, ROS2MsgElementInterfaceFactory)
#ifdef _MSC_VER
#pragma warning(pop)
#else
#pragma GCC diagnostic pop
#endif //_MSC_VER
//gen-1
