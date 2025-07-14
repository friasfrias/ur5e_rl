// Copyright 2020-2022 The MathWorks, Inc.
// Common copy functions for sensor_msgs/JoyFeedback
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
#include "sensor_msgs/msg/joy_feedback.hpp"
#include "visibility_control.h"
#include "class_loader/multi_library_class_loader.hpp"
#include "ROS2PubSubTemplates.hpp"
class SENSOR_MSGS_EXPORT ros2_sensor_msgs_msg_JoyFeedback_common : public MATLABROS2MsgInterface<sensor_msgs::msg::JoyFeedback> {
  public:
    virtual ~ros2_sensor_msgs_msg_JoyFeedback_common(){}
    virtual void copy_from_struct(sensor_msgs::msg::JoyFeedback* msg, const matlab::data::Struct& arr, MultiLibLoader loader); 
    //----------------------------------------------------------------------------
    virtual MDArray_T get_arr(MDFactory_T& factory, const sensor_msgs::msg::JoyFeedback* msg, MultiLibLoader loader, size_t size = 1);
};
  void ros2_sensor_msgs_msg_JoyFeedback_common::copy_from_struct(sensor_msgs::msg::JoyFeedback* msg, const matlab::data::Struct& arr,
               MultiLibLoader loader) {
    try {
        //type
        const matlab::data::TypedArray<uint8_t> type_arr = arr["type"];
        msg->type = type_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'type' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'type' is wrong type; expected a uint8.");
    }
    try {
        //id
        const matlab::data::TypedArray<uint8_t> id_arr = arr["id"];
        msg->id = id_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'id' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'id' is wrong type; expected a uint8.");
    }
    try {
        //intensity
        const matlab::data::TypedArray<float> intensity_arr = arr["intensity"];
        msg->intensity = intensity_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'intensity' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'intensity' is wrong type; expected a single.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T ros2_sensor_msgs_msg_JoyFeedback_common::get_arr(MDFactory_T& factory, const sensor_msgs::msg::JoyFeedback* msg,
       MultiLibLoader loader, size_t size) {
    auto outArray = factory.createStructArray({size,1},{"MessageType","TYPE_LED","TYPE_RUMBLE","TYPE_BUZZER","type","id","intensity"});
    for(size_t ctr = 0; ctr < size; ctr++){
    outArray[ctr]["MessageType"] = factory.createCharArray("sensor_msgs/JoyFeedback");
    // TYPE_LED
    auto currentElement_TYPE_LED = (msg + ctr)->TYPE_LED;
    outArray[ctr]["TYPE_LED"] = factory.createScalar(currentElement_TYPE_LED);
    // TYPE_RUMBLE
    auto currentElement_TYPE_RUMBLE = (msg + ctr)->TYPE_RUMBLE;
    outArray[ctr]["TYPE_RUMBLE"] = factory.createScalar(currentElement_TYPE_RUMBLE);
    // TYPE_BUZZER
    auto currentElement_TYPE_BUZZER = (msg + ctr)->TYPE_BUZZER;
    outArray[ctr]["TYPE_BUZZER"] = factory.createScalar(currentElement_TYPE_BUZZER);
    // type
    auto currentElement_type = (msg + ctr)->type;
    outArray[ctr]["type"] = factory.createScalar(currentElement_type);
    // id
    auto currentElement_id = (msg + ctr)->id;
    outArray[ctr]["id"] = factory.createScalar(currentElement_id);
    // intensity
    auto currentElement_intensity = (msg + ctr)->intensity;
    outArray[ctr]["intensity"] = factory.createScalar(currentElement_intensity);
    }
    return std::move(outArray);
  } 
class SENSOR_MSGS_EXPORT ros2_sensor_msgs_JoyFeedback_message : public ROS2MsgElementInterfaceFactory {
  public:
    virtual ~ros2_sensor_msgs_JoyFeedback_message(){}
    virtual std::shared_ptr<MATLABPublisherInterface> generatePublisherInterface(ElementType /*type*/);
    virtual std::shared_ptr<MATLABSubscriberInterface> generateSubscriberInterface(ElementType /*type*/);
    virtual std::shared_ptr<void> generateCppMessage(ElementType /*type*/, const matlab::data::StructArray& /* arr */, MultiLibLoader /* loader */, std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* /*commonObjMap*/);
    virtual matlab::data::StructArray generateMLMessage(ElementType  /*type*/ ,void*  /* msg */, MultiLibLoader /* loader */ , std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* /*commonObjMap*/);
};  
  std::shared_ptr<MATLABPublisherInterface> 
          ros2_sensor_msgs_JoyFeedback_message::generatePublisherInterface(ElementType /*type*/){
    return std::make_shared<ROS2PublisherImpl<sensor_msgs::msg::JoyFeedback,ros2_sensor_msgs_msg_JoyFeedback_common>>();
  }
  std::shared_ptr<MATLABSubscriberInterface> 
         ros2_sensor_msgs_JoyFeedback_message::generateSubscriberInterface(ElementType /*type*/){
    return std::make_shared<ROS2SubscriberImpl<sensor_msgs::msg::JoyFeedback,ros2_sensor_msgs_msg_JoyFeedback_common>>();
  }
  std::shared_ptr<void> ros2_sensor_msgs_JoyFeedback_message::generateCppMessage(ElementType /*type*/, 
                                           const matlab::data::StructArray& arr,
                                           MultiLibLoader loader,
                                           std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* commonObjMap){
    auto msg = std::make_shared<sensor_msgs::msg::JoyFeedback>();
    ros2_sensor_msgs_msg_JoyFeedback_common commonObj;
    commonObj.mCommonObjMap = commonObjMap;
    commonObj.copy_from_struct(msg.get(), arr[0], loader);
    return msg;
  }
  matlab::data::StructArray ros2_sensor_msgs_JoyFeedback_message::generateMLMessage(ElementType  /*type*/ ,
                                                    void*  msg ,
                                                    MultiLibLoader  loader ,
                                                    std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>*  commonObjMap ){
    ros2_sensor_msgs_msg_JoyFeedback_common commonObj;	
    commonObj.mCommonObjMap = commonObjMap;	
    MDFactory_T factory;
    return commonObj.get_arr(factory, (sensor_msgs::msg::JoyFeedback*)msg, loader);			
 }
#include "class_loader/register_macro.hpp"
// Register the component with class_loader.
// This acts as a sort of entry point, allowing the component to be discoverable when its library
// is being loaded into a running process.
CLASS_LOADER_REGISTER_CLASS(ros2_sensor_msgs_msg_JoyFeedback_common, MATLABROS2MsgInterface<sensor_msgs::msg::JoyFeedback>)
CLASS_LOADER_REGISTER_CLASS(ros2_sensor_msgs_JoyFeedback_message, ROS2MsgElementInterfaceFactory)
#ifdef _MSC_VER
#pragma warning(pop)
#else
#pragma GCC diagnostic pop
#endif //_MSC_VER