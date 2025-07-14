// Copyright 2020-2022 The MathWorks, Inc.
// Common copy functions for sensor_msgs/Imu
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
#include "sensor_msgs/msg/imu.hpp"
#include "visibility_control.h"
#include "class_loader/multi_library_class_loader.hpp"
#include "ROS2PubSubTemplates.hpp"
class SENSOR_MSGS_EXPORT ros2_sensor_msgs_msg_Imu_common : public MATLABROS2MsgInterface<sensor_msgs::msg::Imu> {
  public:
    virtual ~ros2_sensor_msgs_msg_Imu_common(){}
    virtual void copy_from_struct(sensor_msgs::msg::Imu* msg, const matlab::data::Struct& arr, MultiLibLoader loader); 
    //----------------------------------------------------------------------------
    virtual MDArray_T get_arr(MDFactory_T& factory, const sensor_msgs::msg::Imu* msg, MultiLibLoader loader, size_t size = 1);
};
  void ros2_sensor_msgs_msg_Imu_common::copy_from_struct(sensor_msgs::msg::Imu* msg, const matlab::data::Struct& arr,
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
        //orientation
        const matlab::data::StructArray orientation_arr = arr["orientation"];
        auto msgClassPtr_orientation = getCommonObject<geometry_msgs::msg::Quaternion>("ros2_geometry_msgs_msg_Quaternion_common",loader);
        msgClassPtr_orientation->copy_from_struct(&msg->orientation,orientation_arr[0],loader);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'orientation' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'orientation' is wrong type; expected a struct.");
    }
    try {
        //orientation_covariance
        const matlab::data::TypedArray<double> orientation_covariance_arr = arr["orientation_covariance"];
        size_t nelem = 9;
        	std::copy(orientation_covariance_arr.begin(), orientation_covariance_arr.begin()+nelem, msg->orientation_covariance.begin());
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'orientation_covariance' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'orientation_covariance' is wrong type; expected a double.");
    }
    try {
        //angular_velocity
        const matlab::data::StructArray angular_velocity_arr = arr["angular_velocity"];
        auto msgClassPtr_angular_velocity = getCommonObject<geometry_msgs::msg::Vector3>("ros2_geometry_msgs_msg_Vector3_common",loader);
        msgClassPtr_angular_velocity->copy_from_struct(&msg->angular_velocity,angular_velocity_arr[0],loader);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'angular_velocity' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'angular_velocity' is wrong type; expected a struct.");
    }
    try {
        //angular_velocity_covariance
        const matlab::data::TypedArray<double> angular_velocity_covariance_arr = arr["angular_velocity_covariance"];
        size_t nelem = 9;
        	std::copy(angular_velocity_covariance_arr.begin(), angular_velocity_covariance_arr.begin()+nelem, msg->angular_velocity_covariance.begin());
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'angular_velocity_covariance' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'angular_velocity_covariance' is wrong type; expected a double.");
    }
    try {
        //linear_acceleration
        const matlab::data::StructArray linear_acceleration_arr = arr["linear_acceleration"];
        auto msgClassPtr_linear_acceleration = getCommonObject<geometry_msgs::msg::Vector3>("ros2_geometry_msgs_msg_Vector3_common",loader);
        msgClassPtr_linear_acceleration->copy_from_struct(&msg->linear_acceleration,linear_acceleration_arr[0],loader);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'linear_acceleration' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'linear_acceleration' is wrong type; expected a struct.");
    }
    try {
        //linear_acceleration_covariance
        const matlab::data::TypedArray<double> linear_acceleration_covariance_arr = arr["linear_acceleration_covariance"];
        size_t nelem = 9;
        	std::copy(linear_acceleration_covariance_arr.begin(), linear_acceleration_covariance_arr.begin()+nelem, msg->linear_acceleration_covariance.begin());
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'linear_acceleration_covariance' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'linear_acceleration_covariance' is wrong type; expected a double.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T ros2_sensor_msgs_msg_Imu_common::get_arr(MDFactory_T& factory, const sensor_msgs::msg::Imu* msg,
       MultiLibLoader loader, size_t size) {
    auto outArray = factory.createStructArray({size,1},{"MessageType","header","orientation","orientation_covariance","angular_velocity","angular_velocity_covariance","linear_acceleration","linear_acceleration_covariance"});
    for(size_t ctr = 0; ctr < size; ctr++){
    outArray[ctr]["MessageType"] = factory.createCharArray("sensor_msgs/Imu");
    // header
    auto currentElement_header = (msg + ctr)->header;
    auto msgClassPtr_header = getCommonObject<std_msgs::msg::Header>("ros2_std_msgs_msg_Header_common",loader);
    outArray[ctr]["header"] = msgClassPtr_header->get_arr(factory, &currentElement_header, loader);
    // orientation
    auto currentElement_orientation = (msg + ctr)->orientation;
    auto msgClassPtr_orientation = getCommonObject<geometry_msgs::msg::Quaternion>("ros2_geometry_msgs_msg_Quaternion_common",loader);
    outArray[ctr]["orientation"] = msgClassPtr_orientation->get_arr(factory, &currentElement_orientation, loader);
    // orientation_covariance
    auto currentElement_orientation_covariance = (msg + ctr)->orientation_covariance;
    outArray[ctr]["orientation_covariance"] = factory.createArray<sensor_msgs::msg::Imu::_orientation_covariance_type::const_iterator, double>({currentElement_orientation_covariance.size(), 1}, currentElement_orientation_covariance.begin(), currentElement_orientation_covariance.end());
    // angular_velocity
    auto currentElement_angular_velocity = (msg + ctr)->angular_velocity;
    auto msgClassPtr_angular_velocity = getCommonObject<geometry_msgs::msg::Vector3>("ros2_geometry_msgs_msg_Vector3_common",loader);
    outArray[ctr]["angular_velocity"] = msgClassPtr_angular_velocity->get_arr(factory, &currentElement_angular_velocity, loader);
    // angular_velocity_covariance
    auto currentElement_angular_velocity_covariance = (msg + ctr)->angular_velocity_covariance;
    outArray[ctr]["angular_velocity_covariance"] = factory.createArray<sensor_msgs::msg::Imu::_angular_velocity_covariance_type::const_iterator, double>({currentElement_angular_velocity_covariance.size(), 1}, currentElement_angular_velocity_covariance.begin(), currentElement_angular_velocity_covariance.end());
    // linear_acceleration
    auto currentElement_linear_acceleration = (msg + ctr)->linear_acceleration;
    auto msgClassPtr_linear_acceleration = getCommonObject<geometry_msgs::msg::Vector3>("ros2_geometry_msgs_msg_Vector3_common",loader);
    outArray[ctr]["linear_acceleration"] = msgClassPtr_linear_acceleration->get_arr(factory, &currentElement_linear_acceleration, loader);
    // linear_acceleration_covariance
    auto currentElement_linear_acceleration_covariance = (msg + ctr)->linear_acceleration_covariance;
    outArray[ctr]["linear_acceleration_covariance"] = factory.createArray<sensor_msgs::msg::Imu::_linear_acceleration_covariance_type::const_iterator, double>({currentElement_linear_acceleration_covariance.size(), 1}, currentElement_linear_acceleration_covariance.begin(), currentElement_linear_acceleration_covariance.end());
    }
    return std::move(outArray);
  } 
class SENSOR_MSGS_EXPORT ros2_sensor_msgs_Imu_message : public ROS2MsgElementInterfaceFactory {
  public:
    virtual ~ros2_sensor_msgs_Imu_message(){}
    virtual std::shared_ptr<MATLABPublisherInterface> generatePublisherInterface(ElementType /*type*/);
    virtual std::shared_ptr<MATLABSubscriberInterface> generateSubscriberInterface(ElementType /*type*/);
    virtual std::shared_ptr<void> generateCppMessage(ElementType /*type*/, const matlab::data::StructArray& /* arr */, MultiLibLoader /* loader */, std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* /*commonObjMap*/);
    virtual matlab::data::StructArray generateMLMessage(ElementType  /*type*/ ,void*  /* msg */, MultiLibLoader /* loader */ , std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* /*commonObjMap*/);
};  
  std::shared_ptr<MATLABPublisherInterface> 
          ros2_sensor_msgs_Imu_message::generatePublisherInterface(ElementType /*type*/){
    return std::make_shared<ROS2PublisherImpl<sensor_msgs::msg::Imu,ros2_sensor_msgs_msg_Imu_common>>();
  }
  std::shared_ptr<MATLABSubscriberInterface> 
         ros2_sensor_msgs_Imu_message::generateSubscriberInterface(ElementType /*type*/){
    return std::make_shared<ROS2SubscriberImpl<sensor_msgs::msg::Imu,ros2_sensor_msgs_msg_Imu_common>>();
  }
  std::shared_ptr<void> ros2_sensor_msgs_Imu_message::generateCppMessage(ElementType /*type*/, 
                                           const matlab::data::StructArray& arr,
                                           MultiLibLoader loader,
                                           std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* commonObjMap){
    auto msg = std::make_shared<sensor_msgs::msg::Imu>();
    ros2_sensor_msgs_msg_Imu_common commonObj;
    commonObj.mCommonObjMap = commonObjMap;
    commonObj.copy_from_struct(msg.get(), arr[0], loader);
    return msg;
  }
  matlab::data::StructArray ros2_sensor_msgs_Imu_message::generateMLMessage(ElementType  /*type*/ ,
                                                    void*  msg ,
                                                    MultiLibLoader  loader ,
                                                    std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>*  commonObjMap ){
    ros2_sensor_msgs_msg_Imu_common commonObj;	
    commonObj.mCommonObjMap = commonObjMap;	
    MDFactory_T factory;
    return commonObj.get_arr(factory, (sensor_msgs::msg::Imu*)msg, loader);			
 }
#include "class_loader/register_macro.hpp"
// Register the component with class_loader.
// This acts as a sort of entry point, allowing the component to be discoverable when its library
// is being loaded into a running process.
CLASS_LOADER_REGISTER_CLASS(ros2_sensor_msgs_msg_Imu_common, MATLABROS2MsgInterface<sensor_msgs::msg::Imu>)
CLASS_LOADER_REGISTER_CLASS(ros2_sensor_msgs_Imu_message, ROS2MsgElementInterfaceFactory)
#ifdef _MSC_VER
#pragma warning(pop)
#else
#pragma GCC diagnostic pop
#endif //_MSC_VER