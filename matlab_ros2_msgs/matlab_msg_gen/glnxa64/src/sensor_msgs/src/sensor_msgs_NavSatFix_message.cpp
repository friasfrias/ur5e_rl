// Copyright 2020-2022 The MathWorks, Inc.
// Common copy functions for sensor_msgs/NavSatFix
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
#include "sensor_msgs/msg/nav_sat_fix.hpp"
#include "visibility_control.h"
#include "class_loader/multi_library_class_loader.hpp"
#include "ROS2PubSubTemplates.hpp"
class SENSOR_MSGS_EXPORT ros2_sensor_msgs_msg_NavSatFix_common : public MATLABROS2MsgInterface<sensor_msgs::msg::NavSatFix> {
  public:
    virtual ~ros2_sensor_msgs_msg_NavSatFix_common(){}
    virtual void copy_from_struct(sensor_msgs::msg::NavSatFix* msg, const matlab::data::Struct& arr, MultiLibLoader loader); 
    //----------------------------------------------------------------------------
    virtual MDArray_T get_arr(MDFactory_T& factory, const sensor_msgs::msg::NavSatFix* msg, MultiLibLoader loader, size_t size = 1);
};
  void ros2_sensor_msgs_msg_NavSatFix_common::copy_from_struct(sensor_msgs::msg::NavSatFix* msg, const matlab::data::Struct& arr,
               MultiLibLoader loader) {
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
        //status
        const matlab::data::StructArray status_arr = arr["status"];
        auto msgClassPtr_status = getCommonObject<sensor_msgs::msg::NavSatStatus>("ros2_sensor_msgs_msg_NavSatStatus_common",loader);
        msgClassPtr_status->copy_from_struct(&msg->status,status_arr[0],loader);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'status' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'status' is wrong type; expected a struct.");
    }
    try {
        //latitude
        const matlab::data::TypedArray<double> latitude_arr = arr["latitude"];
        msg->latitude = latitude_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'latitude' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'latitude' is wrong type; expected a double.");
    }
    try {
        //longitude
        const matlab::data::TypedArray<double> longitude_arr = arr["longitude"];
        msg->longitude = longitude_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'longitude' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'longitude' is wrong type; expected a double.");
    }
    try {
        //altitude
        const matlab::data::TypedArray<double> altitude_arr = arr["altitude"];
        msg->altitude = altitude_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'altitude' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'altitude' is wrong type; expected a double.");
    }
    try {
        //position_covariance
        const matlab::data::TypedArray<double> position_covariance_arr = arr["position_covariance"];
        size_t nelem = 9;
        	std::copy(position_covariance_arr.begin(), position_covariance_arr.begin()+nelem, msg->position_covariance.begin());
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'position_covariance' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'position_covariance' is wrong type; expected a double.");
    }
    try {
        //position_covariance_type
        const matlab::data::TypedArray<uint8_t> position_covariance_type_arr = arr["position_covariance_type"];
        msg->position_covariance_type = position_covariance_type_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'position_covariance_type' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'position_covariance_type' is wrong type; expected a uint8.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T ros2_sensor_msgs_msg_NavSatFix_common::get_arr(MDFactory_T& factory, const sensor_msgs::msg::NavSatFix* msg,
       MultiLibLoader loader, size_t size) {
    auto outArray = factory.createStructArray({size,1},{"MessageType","header","status","latitude","longitude","altitude","position_covariance","COVARIANCE_TYPE_UNKNOWN","COVARIANCE_TYPE_APPROXIMATED","COVARIANCE_TYPE_DIAGONAL_KNOWN","COVARIANCE_TYPE_KNOWN","position_covariance_type"});
    for(size_t ctr = 0; ctr < size; ctr++){
    outArray[ctr]["MessageType"] = factory.createCharArray("sensor_msgs/NavSatFix");
    // header
    auto currentElement_header = (msg + ctr)->header;
    auto msgClassPtr_header = getCommonObject<std_msgs::msg::Header>("ros2_std_msgs_msg_Header_common",loader);
    outArray[ctr]["header"] = msgClassPtr_header->get_arr(factory, &currentElement_header, loader);
    // status
    auto currentElement_status = (msg + ctr)->status;
    auto msgClassPtr_status = getCommonObject<sensor_msgs::msg::NavSatStatus>("ros2_sensor_msgs_msg_NavSatStatus_common",loader);
    outArray[ctr]["status"] = msgClassPtr_status->get_arr(factory, &currentElement_status, loader);
    // latitude
    auto currentElement_latitude = (msg + ctr)->latitude;
    outArray[ctr]["latitude"] = factory.createScalar(currentElement_latitude);
    // longitude
    auto currentElement_longitude = (msg + ctr)->longitude;
    outArray[ctr]["longitude"] = factory.createScalar(currentElement_longitude);
    // altitude
    auto currentElement_altitude = (msg + ctr)->altitude;
    outArray[ctr]["altitude"] = factory.createScalar(currentElement_altitude);
    // position_covariance
    auto currentElement_position_covariance = (msg + ctr)->position_covariance;
    outArray[ctr]["position_covariance"] = factory.createArray<sensor_msgs::msg::NavSatFix::_position_covariance_type::const_iterator, double>({currentElement_position_covariance.size(), 1}, currentElement_position_covariance.begin(), currentElement_position_covariance.end());
    // COVARIANCE_TYPE_UNKNOWN
    auto currentElement_COVARIANCE_TYPE_UNKNOWN = (msg + ctr)->COVARIANCE_TYPE_UNKNOWN;
    outArray[ctr]["COVARIANCE_TYPE_UNKNOWN"] = factory.createScalar(currentElement_COVARIANCE_TYPE_UNKNOWN);
    // COVARIANCE_TYPE_APPROXIMATED
    auto currentElement_COVARIANCE_TYPE_APPROXIMATED = (msg + ctr)->COVARIANCE_TYPE_APPROXIMATED;
    outArray[ctr]["COVARIANCE_TYPE_APPROXIMATED"] = factory.createScalar(currentElement_COVARIANCE_TYPE_APPROXIMATED);
    // COVARIANCE_TYPE_DIAGONAL_KNOWN
    auto currentElement_COVARIANCE_TYPE_DIAGONAL_KNOWN = (msg + ctr)->COVARIANCE_TYPE_DIAGONAL_KNOWN;
    outArray[ctr]["COVARIANCE_TYPE_DIAGONAL_KNOWN"] = factory.createScalar(currentElement_COVARIANCE_TYPE_DIAGONAL_KNOWN);
    // COVARIANCE_TYPE_KNOWN
    auto currentElement_COVARIANCE_TYPE_KNOWN = (msg + ctr)->COVARIANCE_TYPE_KNOWN;
    outArray[ctr]["COVARIANCE_TYPE_KNOWN"] = factory.createScalar(currentElement_COVARIANCE_TYPE_KNOWN);
    // position_covariance_type
    auto currentElement_position_covariance_type = (msg + ctr)->position_covariance_type;
    outArray[ctr]["position_covariance_type"] = factory.createScalar(currentElement_position_covariance_type);
    }
    return std::move(outArray);
  } 
class SENSOR_MSGS_EXPORT ros2_sensor_msgs_NavSatFix_message : public ROS2MsgElementInterfaceFactory {
  public:
    virtual ~ros2_sensor_msgs_NavSatFix_message(){}
    virtual std::shared_ptr<MATLABPublisherInterface> generatePublisherInterface(ElementType /*type*/);
    virtual std::shared_ptr<MATLABSubscriberInterface> generateSubscriberInterface(ElementType /*type*/);
    virtual std::shared_ptr<void> generateCppMessage(ElementType /*type*/, const matlab::data::StructArray& /* arr */, MultiLibLoader /* loader */, std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* /*commonObjMap*/);
    virtual matlab::data::StructArray generateMLMessage(ElementType  /*type*/ ,void*  /* msg */, MultiLibLoader /* loader */ , std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* /*commonObjMap*/);
};  
  std::shared_ptr<MATLABPublisherInterface> 
          ros2_sensor_msgs_NavSatFix_message::generatePublisherInterface(ElementType /*type*/){
    return std::make_shared<ROS2PublisherImpl<sensor_msgs::msg::NavSatFix,ros2_sensor_msgs_msg_NavSatFix_common>>();
  }
  std::shared_ptr<MATLABSubscriberInterface> 
         ros2_sensor_msgs_NavSatFix_message::generateSubscriberInterface(ElementType /*type*/){
    return std::make_shared<ROS2SubscriberImpl<sensor_msgs::msg::NavSatFix,ros2_sensor_msgs_msg_NavSatFix_common>>();
  }
  std::shared_ptr<void> ros2_sensor_msgs_NavSatFix_message::generateCppMessage(ElementType /*type*/, 
                                           const matlab::data::StructArray& arr,
                                           MultiLibLoader loader,
                                           std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* commonObjMap){
    auto msg = std::make_shared<sensor_msgs::msg::NavSatFix>();
    ros2_sensor_msgs_msg_NavSatFix_common commonObj;
    commonObj.mCommonObjMap = commonObjMap;
    commonObj.copy_from_struct(msg.get(), arr[0], loader);
    return msg;
  }
  matlab::data::StructArray ros2_sensor_msgs_NavSatFix_message::generateMLMessage(ElementType  /*type*/ ,
                                                    void*  msg ,
                                                    MultiLibLoader  loader ,
                                                    std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>*  commonObjMap ){
    ros2_sensor_msgs_msg_NavSatFix_common commonObj;	
    commonObj.mCommonObjMap = commonObjMap;	
    MDFactory_T factory;
    return commonObj.get_arr(factory, (sensor_msgs::msg::NavSatFix*)msg, loader);			
 }
#include "class_loader/register_macro.hpp"
// Register the component with class_loader.
// This acts as a sort of entry point, allowing the component to be discoverable when its library
// is being loaded into a running process.
CLASS_LOADER_REGISTER_CLASS(ros2_sensor_msgs_msg_NavSatFix_common, MATLABROS2MsgInterface<sensor_msgs::msg::NavSatFix>)
CLASS_LOADER_REGISTER_CLASS(ros2_sensor_msgs_NavSatFix_message, ROS2MsgElementInterfaceFactory)
#ifdef _MSC_VER
#pragma warning(pop)
#else
#pragma GCC diagnostic pop
#endif //_MSC_VER