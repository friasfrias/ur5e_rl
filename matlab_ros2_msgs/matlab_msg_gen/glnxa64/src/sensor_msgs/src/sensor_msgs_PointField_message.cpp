// Copyright 2020-2022 The MathWorks, Inc.
// Common copy functions for sensor_msgs/PointField
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
#include "sensor_msgs/msg/point_field.hpp"
#include "visibility_control.h"
#include "class_loader/multi_library_class_loader.hpp"
#include "ROS2PubSubTemplates.hpp"
class SENSOR_MSGS_EXPORT ros2_sensor_msgs_msg_PointField_common : public MATLABROS2MsgInterface<sensor_msgs::msg::PointField> {
  public:
    virtual ~ros2_sensor_msgs_msg_PointField_common(){}
    virtual void copy_from_struct(sensor_msgs::msg::PointField* msg, const matlab::data::Struct& arr, MultiLibLoader loader); 
    //----------------------------------------------------------------------------
    virtual MDArray_T get_arr(MDFactory_T& factory, const sensor_msgs::msg::PointField* msg, MultiLibLoader loader, size_t size = 1);
};
  void ros2_sensor_msgs_msg_PointField_common::copy_from_struct(sensor_msgs::msg::PointField* msg, const matlab::data::Struct& arr,
               MultiLibLoader loader) {
    try {
        //name
        const matlab::data::CharArray name_arr = arr["name"];
        msg->name = name_arr.toAscii();
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'name' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'name' is wrong type; expected a string.");
    }
    try {
        //offset
        const matlab::data::TypedArray<uint32_t> offset_arr = arr["offset"];
        msg->offset = offset_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'offset' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'offset' is wrong type; expected a uint32.");
    }
    try {
        //datatype
        const matlab::data::TypedArray<uint8_t> datatype_arr = arr["datatype"];
        msg->datatype = datatype_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'datatype' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'datatype' is wrong type; expected a uint8.");
    }
    try {
        //count
        const matlab::data::TypedArray<uint32_t> count_arr = arr["count"];
        msg->count = count_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'count' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'count' is wrong type; expected a uint32.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T ros2_sensor_msgs_msg_PointField_common::get_arr(MDFactory_T& factory, const sensor_msgs::msg::PointField* msg,
       MultiLibLoader loader, size_t size) {
    auto outArray = factory.createStructArray({size,1},{"MessageType","INT8","UINT8","INT16","UINT16","INT32","UINT32","FLOAT32","FLOAT64","name","offset","datatype","count"});
    for(size_t ctr = 0; ctr < size; ctr++){
    outArray[ctr]["MessageType"] = factory.createCharArray("sensor_msgs/PointField");
    // INT8
    auto currentElement_INT8 = (msg + ctr)->INT8;
    outArray[ctr]["INT8"] = factory.createScalar(currentElement_INT8);
    // UINT8
    auto currentElement_UINT8 = (msg + ctr)->UINT8;
    outArray[ctr]["UINT8"] = factory.createScalar(currentElement_UINT8);
    // INT16
    auto currentElement_INT16 = (msg + ctr)->INT16;
    outArray[ctr]["INT16"] = factory.createScalar(currentElement_INT16);
    // UINT16
    auto currentElement_UINT16 = (msg + ctr)->UINT16;
    outArray[ctr]["UINT16"] = factory.createScalar(currentElement_UINT16);
    // INT32
    auto currentElement_INT32 = (msg + ctr)->INT32;
    outArray[ctr]["INT32"] = factory.createScalar(currentElement_INT32);
    // UINT32
    auto currentElement_UINT32 = (msg + ctr)->UINT32;
    outArray[ctr]["UINT32"] = factory.createScalar(currentElement_UINT32);
    // FLOAT32
    auto currentElement_FLOAT32 = (msg + ctr)->FLOAT32;
    outArray[ctr]["FLOAT32"] = factory.createScalar(currentElement_FLOAT32);
    // FLOAT64
    auto currentElement_FLOAT64 = (msg + ctr)->FLOAT64;
    outArray[ctr]["FLOAT64"] = factory.createScalar(currentElement_FLOAT64);
    // name
    auto currentElement_name = (msg + ctr)->name;
    outArray[ctr]["name"] = factory.createCharArray(currentElement_name);
    // offset
    auto currentElement_offset = (msg + ctr)->offset;
    outArray[ctr]["offset"] = factory.createScalar(currentElement_offset);
    // datatype
    auto currentElement_datatype = (msg + ctr)->datatype;
    outArray[ctr]["datatype"] = factory.createScalar(currentElement_datatype);
    // count
    auto currentElement_count = (msg + ctr)->count;
    outArray[ctr]["count"] = factory.createScalar(currentElement_count);
    }
    return std::move(outArray);
  } 
class SENSOR_MSGS_EXPORT ros2_sensor_msgs_PointField_message : public ROS2MsgElementInterfaceFactory {
  public:
    virtual ~ros2_sensor_msgs_PointField_message(){}
    virtual std::shared_ptr<MATLABPublisherInterface> generatePublisherInterface(ElementType /*type*/);
    virtual std::shared_ptr<MATLABSubscriberInterface> generateSubscriberInterface(ElementType /*type*/);
    virtual std::shared_ptr<void> generateCppMessage(ElementType /*type*/, const matlab::data::StructArray& /* arr */, MultiLibLoader /* loader */, std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* /*commonObjMap*/);
    virtual matlab::data::StructArray generateMLMessage(ElementType  /*type*/ ,void*  /* msg */, MultiLibLoader /* loader */ , std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* /*commonObjMap*/);
};  
  std::shared_ptr<MATLABPublisherInterface> 
          ros2_sensor_msgs_PointField_message::generatePublisherInterface(ElementType /*type*/){
    return std::make_shared<ROS2PublisherImpl<sensor_msgs::msg::PointField,ros2_sensor_msgs_msg_PointField_common>>();
  }
  std::shared_ptr<MATLABSubscriberInterface> 
         ros2_sensor_msgs_PointField_message::generateSubscriberInterface(ElementType /*type*/){
    return std::make_shared<ROS2SubscriberImpl<sensor_msgs::msg::PointField,ros2_sensor_msgs_msg_PointField_common>>();
  }
  std::shared_ptr<void> ros2_sensor_msgs_PointField_message::generateCppMessage(ElementType /*type*/, 
                                           const matlab::data::StructArray& arr,
                                           MultiLibLoader loader,
                                           std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* commonObjMap){
    auto msg = std::make_shared<sensor_msgs::msg::PointField>();
    ros2_sensor_msgs_msg_PointField_common commonObj;
    commonObj.mCommonObjMap = commonObjMap;
    commonObj.copy_from_struct(msg.get(), arr[0], loader);
    return msg;
  }
  matlab::data::StructArray ros2_sensor_msgs_PointField_message::generateMLMessage(ElementType  /*type*/ ,
                                                    void*  msg ,
                                                    MultiLibLoader  loader ,
                                                    std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>*  commonObjMap ){
    ros2_sensor_msgs_msg_PointField_common commonObj;	
    commonObj.mCommonObjMap = commonObjMap;	
    MDFactory_T factory;
    return commonObj.get_arr(factory, (sensor_msgs::msg::PointField*)msg, loader);			
 }
#include "class_loader/register_macro.hpp"
// Register the component with class_loader.
// This acts as a sort of entry point, allowing the component to be discoverable when its library
// is being loaded into a running process.
CLASS_LOADER_REGISTER_CLASS(ros2_sensor_msgs_msg_PointField_common, MATLABROS2MsgInterface<sensor_msgs::msg::PointField>)
CLASS_LOADER_REGISTER_CLASS(ros2_sensor_msgs_PointField_message, ROS2MsgElementInterfaceFactory)
#ifdef _MSC_VER
#pragma warning(pop)
#else
#pragma GCC diagnostic pop
#endif //_MSC_VER