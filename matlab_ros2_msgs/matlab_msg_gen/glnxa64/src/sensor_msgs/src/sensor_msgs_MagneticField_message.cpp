// Copyright 2020-2022 The MathWorks, Inc.
// Common copy functions for sensor_msgs/MagneticField
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
#include "sensor_msgs/msg/magnetic_field.hpp"
#include "visibility_control.h"
#include "class_loader/multi_library_class_loader.hpp"
#include "ROS2PubSubTemplates.hpp"
class SENSOR_MSGS_EXPORT ros2_sensor_msgs_msg_MagneticField_common : public MATLABROS2MsgInterface<sensor_msgs::msg::MagneticField> {
  public:
    virtual ~ros2_sensor_msgs_msg_MagneticField_common(){}
    virtual void copy_from_struct(sensor_msgs::msg::MagneticField* msg, const matlab::data::Struct& arr, MultiLibLoader loader); 
    //----------------------------------------------------------------------------
    virtual MDArray_T get_arr(MDFactory_T& factory, const sensor_msgs::msg::MagneticField* msg, MultiLibLoader loader, size_t size = 1);
};
  void ros2_sensor_msgs_msg_MagneticField_common::copy_from_struct(sensor_msgs::msg::MagneticField* msg, const matlab::data::Struct& arr,
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
        //magnetic_field
        const matlab::data::StructArray magnetic_field_arr = arr["magnetic_field"];
        auto msgClassPtr_magnetic_field = getCommonObject<geometry_msgs::msg::Vector3>("ros2_geometry_msgs_msg_Vector3_common",loader);
        msgClassPtr_magnetic_field->copy_from_struct(&msg->magnetic_field,magnetic_field_arr[0],loader);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'magnetic_field' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'magnetic_field' is wrong type; expected a struct.");
    }
    try {
        //magnetic_field_covariance
        const matlab::data::TypedArray<double> magnetic_field_covariance_arr = arr["magnetic_field_covariance"];
        size_t nelem = 9;
        	std::copy(magnetic_field_covariance_arr.begin(), magnetic_field_covariance_arr.begin()+nelem, msg->magnetic_field_covariance.begin());
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'magnetic_field_covariance' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'magnetic_field_covariance' is wrong type; expected a double.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T ros2_sensor_msgs_msg_MagneticField_common::get_arr(MDFactory_T& factory, const sensor_msgs::msg::MagneticField* msg,
       MultiLibLoader loader, size_t size) {
    auto outArray = factory.createStructArray({size,1},{"MessageType","header","magnetic_field","magnetic_field_covariance"});
    for(size_t ctr = 0; ctr < size; ctr++){
    outArray[ctr]["MessageType"] = factory.createCharArray("sensor_msgs/MagneticField");
    // header
    auto currentElement_header = (msg + ctr)->header;
    auto msgClassPtr_header = getCommonObject<std_msgs::msg::Header>("ros2_std_msgs_msg_Header_common",loader);
    outArray[ctr]["header"] = msgClassPtr_header->get_arr(factory, &currentElement_header, loader);
    // magnetic_field
    auto currentElement_magnetic_field = (msg + ctr)->magnetic_field;
    auto msgClassPtr_magnetic_field = getCommonObject<geometry_msgs::msg::Vector3>("ros2_geometry_msgs_msg_Vector3_common",loader);
    outArray[ctr]["magnetic_field"] = msgClassPtr_magnetic_field->get_arr(factory, &currentElement_magnetic_field, loader);
    // magnetic_field_covariance
    auto currentElement_magnetic_field_covariance = (msg + ctr)->magnetic_field_covariance;
    outArray[ctr]["magnetic_field_covariance"] = factory.createArray<sensor_msgs::msg::MagneticField::_magnetic_field_covariance_type::const_iterator, double>({currentElement_magnetic_field_covariance.size(), 1}, currentElement_magnetic_field_covariance.begin(), currentElement_magnetic_field_covariance.end());
    }
    return std::move(outArray);
  } 
class SENSOR_MSGS_EXPORT ros2_sensor_msgs_MagneticField_message : public ROS2MsgElementInterfaceFactory {
  public:
    virtual ~ros2_sensor_msgs_MagneticField_message(){}
    virtual std::shared_ptr<MATLABPublisherInterface> generatePublisherInterface(ElementType /*type*/);
    virtual std::shared_ptr<MATLABSubscriberInterface> generateSubscriberInterface(ElementType /*type*/);
    virtual std::shared_ptr<void> generateCppMessage(ElementType /*type*/, const matlab::data::StructArray& /* arr */, MultiLibLoader /* loader */, std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* /*commonObjMap*/);
    virtual matlab::data::StructArray generateMLMessage(ElementType  /*type*/ ,void*  /* msg */, MultiLibLoader /* loader */ , std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* /*commonObjMap*/);
};  
  std::shared_ptr<MATLABPublisherInterface> 
          ros2_sensor_msgs_MagneticField_message::generatePublisherInterface(ElementType /*type*/){
    return std::make_shared<ROS2PublisherImpl<sensor_msgs::msg::MagneticField,ros2_sensor_msgs_msg_MagneticField_common>>();
  }
  std::shared_ptr<MATLABSubscriberInterface> 
         ros2_sensor_msgs_MagneticField_message::generateSubscriberInterface(ElementType /*type*/){
    return std::make_shared<ROS2SubscriberImpl<sensor_msgs::msg::MagneticField,ros2_sensor_msgs_msg_MagneticField_common>>();
  }
  std::shared_ptr<void> ros2_sensor_msgs_MagneticField_message::generateCppMessage(ElementType /*type*/, 
                                           const matlab::data::StructArray& arr,
                                           MultiLibLoader loader,
                                           std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* commonObjMap){
    auto msg = std::make_shared<sensor_msgs::msg::MagneticField>();
    ros2_sensor_msgs_msg_MagneticField_common commonObj;
    commonObj.mCommonObjMap = commonObjMap;
    commonObj.copy_from_struct(msg.get(), arr[0], loader);
    return msg;
  }
  matlab::data::StructArray ros2_sensor_msgs_MagneticField_message::generateMLMessage(ElementType  /*type*/ ,
                                                    void*  msg ,
                                                    MultiLibLoader  loader ,
                                                    std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>*  commonObjMap ){
    ros2_sensor_msgs_msg_MagneticField_common commonObj;	
    commonObj.mCommonObjMap = commonObjMap;	
    MDFactory_T factory;
    return commonObj.get_arr(factory, (sensor_msgs::msg::MagneticField*)msg, loader);			
 }
#include "class_loader/register_macro.hpp"
// Register the component with class_loader.
// This acts as a sort of entry point, allowing the component to be discoverable when its library
// is being loaded into a running process.
CLASS_LOADER_REGISTER_CLASS(ros2_sensor_msgs_msg_MagneticField_common, MATLABROS2MsgInterface<sensor_msgs::msg::MagneticField>)
CLASS_LOADER_REGISTER_CLASS(ros2_sensor_msgs_MagneticField_message, ROS2MsgElementInterfaceFactory)
#ifdef _MSC_VER
#pragma warning(pop)
#else
#pragma GCC diagnostic pop
#endif //_MSC_VER