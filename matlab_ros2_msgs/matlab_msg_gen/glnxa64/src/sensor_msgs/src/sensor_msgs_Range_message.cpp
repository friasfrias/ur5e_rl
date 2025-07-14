// Copyright 2020-2022 The MathWorks, Inc.
// Common copy functions for sensor_msgs/Range
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
#include "sensor_msgs/msg/range.hpp"
#include "visibility_control.h"
#include "class_loader/multi_library_class_loader.hpp"
#include "ROS2PubSubTemplates.hpp"
class SENSOR_MSGS_EXPORT ros2_sensor_msgs_msg_Range_common : public MATLABROS2MsgInterface<sensor_msgs::msg::Range> {
  public:
    virtual ~ros2_sensor_msgs_msg_Range_common(){}
    virtual void copy_from_struct(sensor_msgs::msg::Range* msg, const matlab::data::Struct& arr, MultiLibLoader loader); 
    //----------------------------------------------------------------------------
    virtual MDArray_T get_arr(MDFactory_T& factory, const sensor_msgs::msg::Range* msg, MultiLibLoader loader, size_t size = 1);
};
  void ros2_sensor_msgs_msg_Range_common::copy_from_struct(sensor_msgs::msg::Range* msg, const matlab::data::Struct& arr,
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
        //radiation_type
        const matlab::data::TypedArray<uint8_t> radiation_type_arr = arr["radiation_type"];
        msg->radiation_type = radiation_type_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'radiation_type' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'radiation_type' is wrong type; expected a uint8.");
    }
    try {
        //field_of_view
        const matlab::data::TypedArray<float> field_of_view_arr = arr["field_of_view"];
        msg->field_of_view = field_of_view_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'field_of_view' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'field_of_view' is wrong type; expected a single.");
    }
    try {
        //min_range
        const matlab::data::TypedArray<float> min_range_arr = arr["min_range"];
        msg->min_range = min_range_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'min_range' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'min_range' is wrong type; expected a single.");
    }
    try {
        //max_range
        const matlab::data::TypedArray<float> max_range_arr = arr["max_range"];
        msg->max_range = max_range_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'max_range' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'max_range' is wrong type; expected a single.");
    }
    try {
        //range
        const matlab::data::TypedArray<float> range_arr = arr["range"];
        msg->range = range_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'range' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'range' is wrong type; expected a single.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T ros2_sensor_msgs_msg_Range_common::get_arr(MDFactory_T& factory, const sensor_msgs::msg::Range* msg,
       MultiLibLoader loader, size_t size) {
    auto outArray = factory.createStructArray({size,1},{"MessageType","header","ULTRASOUND","INFRARED","radiation_type","field_of_view","min_range","max_range","range"});
    for(size_t ctr = 0; ctr < size; ctr++){
    outArray[ctr]["MessageType"] = factory.createCharArray("sensor_msgs/Range");
    // header
    auto currentElement_header = (msg + ctr)->header;
    auto msgClassPtr_header = getCommonObject<std_msgs::msg::Header>("ros2_std_msgs_msg_Header_common",loader);
    outArray[ctr]["header"] = msgClassPtr_header->get_arr(factory, &currentElement_header, loader);
    // ULTRASOUND
    auto currentElement_ULTRASOUND = (msg + ctr)->ULTRASOUND;
    outArray[ctr]["ULTRASOUND"] = factory.createScalar(currentElement_ULTRASOUND);
    // INFRARED
    auto currentElement_INFRARED = (msg + ctr)->INFRARED;
    outArray[ctr]["INFRARED"] = factory.createScalar(currentElement_INFRARED);
    // radiation_type
    auto currentElement_radiation_type = (msg + ctr)->radiation_type;
    outArray[ctr]["radiation_type"] = factory.createScalar(currentElement_radiation_type);
    // field_of_view
    auto currentElement_field_of_view = (msg + ctr)->field_of_view;
    outArray[ctr]["field_of_view"] = factory.createScalar(currentElement_field_of_view);
    // min_range
    auto currentElement_min_range = (msg + ctr)->min_range;
    outArray[ctr]["min_range"] = factory.createScalar(currentElement_min_range);
    // max_range
    auto currentElement_max_range = (msg + ctr)->max_range;
    outArray[ctr]["max_range"] = factory.createScalar(currentElement_max_range);
    // range
    auto currentElement_range = (msg + ctr)->range;
    outArray[ctr]["range"] = factory.createScalar(currentElement_range);
    }
    return std::move(outArray);
  } 
class SENSOR_MSGS_EXPORT ros2_sensor_msgs_Range_message : public ROS2MsgElementInterfaceFactory {
  public:
    virtual ~ros2_sensor_msgs_Range_message(){}
    virtual std::shared_ptr<MATLABPublisherInterface> generatePublisherInterface(ElementType /*type*/);
    virtual std::shared_ptr<MATLABSubscriberInterface> generateSubscriberInterface(ElementType /*type*/);
    virtual std::shared_ptr<void> generateCppMessage(ElementType /*type*/, const matlab::data::StructArray& /* arr */, MultiLibLoader /* loader */, std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* /*commonObjMap*/);
    virtual matlab::data::StructArray generateMLMessage(ElementType  /*type*/ ,void*  /* msg */, MultiLibLoader /* loader */ , std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* /*commonObjMap*/);
};  
  std::shared_ptr<MATLABPublisherInterface> 
          ros2_sensor_msgs_Range_message::generatePublisherInterface(ElementType /*type*/){
    return std::make_shared<ROS2PublisherImpl<sensor_msgs::msg::Range,ros2_sensor_msgs_msg_Range_common>>();
  }
  std::shared_ptr<MATLABSubscriberInterface> 
         ros2_sensor_msgs_Range_message::generateSubscriberInterface(ElementType /*type*/){
    return std::make_shared<ROS2SubscriberImpl<sensor_msgs::msg::Range,ros2_sensor_msgs_msg_Range_common>>();
  }
  std::shared_ptr<void> ros2_sensor_msgs_Range_message::generateCppMessage(ElementType /*type*/, 
                                           const matlab::data::StructArray& arr,
                                           MultiLibLoader loader,
                                           std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* commonObjMap){
    auto msg = std::make_shared<sensor_msgs::msg::Range>();
    ros2_sensor_msgs_msg_Range_common commonObj;
    commonObj.mCommonObjMap = commonObjMap;
    commonObj.copy_from_struct(msg.get(), arr[0], loader);
    return msg;
  }
  matlab::data::StructArray ros2_sensor_msgs_Range_message::generateMLMessage(ElementType  /*type*/ ,
                                                    void*  msg ,
                                                    MultiLibLoader  loader ,
                                                    std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>*  commonObjMap ){
    ros2_sensor_msgs_msg_Range_common commonObj;	
    commonObj.mCommonObjMap = commonObjMap;	
    MDFactory_T factory;
    return commonObj.get_arr(factory, (sensor_msgs::msg::Range*)msg, loader);			
 }
#include "class_loader/register_macro.hpp"
// Register the component with class_loader.
// This acts as a sort of entry point, allowing the component to be discoverable when its library
// is being loaded into a running process.
CLASS_LOADER_REGISTER_CLASS(ros2_sensor_msgs_msg_Range_common, MATLABROS2MsgInterface<sensor_msgs::msg::Range>)
CLASS_LOADER_REGISTER_CLASS(ros2_sensor_msgs_Range_message, ROS2MsgElementInterfaceFactory)
#ifdef _MSC_VER
#pragma warning(pop)
#else
#pragma GCC diagnostic pop
#endif //_MSC_VER