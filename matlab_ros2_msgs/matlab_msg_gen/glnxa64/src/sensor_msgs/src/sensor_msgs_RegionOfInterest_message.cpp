// Copyright 2020-2022 The MathWorks, Inc.
// Common copy functions for sensor_msgs/RegionOfInterest
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
#include "sensor_msgs/msg/region_of_interest.hpp"
#include "visibility_control.h"
#include "class_loader/multi_library_class_loader.hpp"
#include "ROS2PubSubTemplates.hpp"
class SENSOR_MSGS_EXPORT ros2_sensor_msgs_msg_RegionOfInterest_common : public MATLABROS2MsgInterface<sensor_msgs::msg::RegionOfInterest> {
  public:
    virtual ~ros2_sensor_msgs_msg_RegionOfInterest_common(){}
    virtual void copy_from_struct(sensor_msgs::msg::RegionOfInterest* msg, const matlab::data::Struct& arr, MultiLibLoader loader); 
    //----------------------------------------------------------------------------
    virtual MDArray_T get_arr(MDFactory_T& factory, const sensor_msgs::msg::RegionOfInterest* msg, MultiLibLoader loader, size_t size = 1);
};
  void ros2_sensor_msgs_msg_RegionOfInterest_common::copy_from_struct(sensor_msgs::msg::RegionOfInterest* msg, const matlab::data::Struct& arr,
               MultiLibLoader loader) {
    try {
        //x_offset
        const matlab::data::TypedArray<uint32_t> x_offset_arr = arr["x_offset"];
        msg->x_offset = x_offset_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'x_offset' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'x_offset' is wrong type; expected a uint32.");
    }
    try {
        //y_offset
        const matlab::data::TypedArray<uint32_t> y_offset_arr = arr["y_offset"];
        msg->y_offset = y_offset_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'y_offset' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'y_offset' is wrong type; expected a uint32.");
    }
    try {
        //height
        const matlab::data::TypedArray<uint32_t> height_arr = arr["height"];
        msg->height = height_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'height' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'height' is wrong type; expected a uint32.");
    }
    try {
        //width
        const matlab::data::TypedArray<uint32_t> width_arr = arr["width"];
        msg->width = width_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'width' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'width' is wrong type; expected a uint32.");
    }
    try {
        //do_rectify
        const matlab::data::TypedArray<bool> do_rectify_arr = arr["do_rectify"];
        msg->do_rectify = do_rectify_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'do_rectify' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'do_rectify' is wrong type; expected a logical.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T ros2_sensor_msgs_msg_RegionOfInterest_common::get_arr(MDFactory_T& factory, const sensor_msgs::msg::RegionOfInterest* msg,
       MultiLibLoader loader, size_t size) {
    auto outArray = factory.createStructArray({size,1},{"MessageType","x_offset","y_offset","height","width","do_rectify"});
    for(size_t ctr = 0; ctr < size; ctr++){
    outArray[ctr]["MessageType"] = factory.createCharArray("sensor_msgs/RegionOfInterest");
    // x_offset
    auto currentElement_x_offset = (msg + ctr)->x_offset;
    outArray[ctr]["x_offset"] = factory.createScalar(currentElement_x_offset);
    // y_offset
    auto currentElement_y_offset = (msg + ctr)->y_offset;
    outArray[ctr]["y_offset"] = factory.createScalar(currentElement_y_offset);
    // height
    auto currentElement_height = (msg + ctr)->height;
    outArray[ctr]["height"] = factory.createScalar(currentElement_height);
    // width
    auto currentElement_width = (msg + ctr)->width;
    outArray[ctr]["width"] = factory.createScalar(currentElement_width);
    // do_rectify
    auto currentElement_do_rectify = (msg + ctr)->do_rectify;
    outArray[ctr]["do_rectify"] = factory.createScalar(currentElement_do_rectify);
    }
    return std::move(outArray);
  } 
class SENSOR_MSGS_EXPORT ros2_sensor_msgs_RegionOfInterest_message : public ROS2MsgElementInterfaceFactory {
  public:
    virtual ~ros2_sensor_msgs_RegionOfInterest_message(){}
    virtual std::shared_ptr<MATLABPublisherInterface> generatePublisherInterface(ElementType /*type*/);
    virtual std::shared_ptr<MATLABSubscriberInterface> generateSubscriberInterface(ElementType /*type*/);
    virtual std::shared_ptr<void> generateCppMessage(ElementType /*type*/, const matlab::data::StructArray& /* arr */, MultiLibLoader /* loader */, std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* /*commonObjMap*/);
    virtual matlab::data::StructArray generateMLMessage(ElementType  /*type*/ ,void*  /* msg */, MultiLibLoader /* loader */ , std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* /*commonObjMap*/);
};  
  std::shared_ptr<MATLABPublisherInterface> 
          ros2_sensor_msgs_RegionOfInterest_message::generatePublisherInterface(ElementType /*type*/){
    return std::make_shared<ROS2PublisherImpl<sensor_msgs::msg::RegionOfInterest,ros2_sensor_msgs_msg_RegionOfInterest_common>>();
  }
  std::shared_ptr<MATLABSubscriberInterface> 
         ros2_sensor_msgs_RegionOfInterest_message::generateSubscriberInterface(ElementType /*type*/){
    return std::make_shared<ROS2SubscriberImpl<sensor_msgs::msg::RegionOfInterest,ros2_sensor_msgs_msg_RegionOfInterest_common>>();
  }
  std::shared_ptr<void> ros2_sensor_msgs_RegionOfInterest_message::generateCppMessage(ElementType /*type*/, 
                                           const matlab::data::StructArray& arr,
                                           MultiLibLoader loader,
                                           std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* commonObjMap){
    auto msg = std::make_shared<sensor_msgs::msg::RegionOfInterest>();
    ros2_sensor_msgs_msg_RegionOfInterest_common commonObj;
    commonObj.mCommonObjMap = commonObjMap;
    commonObj.copy_from_struct(msg.get(), arr[0], loader);
    return msg;
  }
  matlab::data::StructArray ros2_sensor_msgs_RegionOfInterest_message::generateMLMessage(ElementType  /*type*/ ,
                                                    void*  msg ,
                                                    MultiLibLoader  loader ,
                                                    std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>*  commonObjMap ){
    ros2_sensor_msgs_msg_RegionOfInterest_common commonObj;	
    commonObj.mCommonObjMap = commonObjMap;	
    MDFactory_T factory;
    return commonObj.get_arr(factory, (sensor_msgs::msg::RegionOfInterest*)msg, loader);			
 }
#include "class_loader/register_macro.hpp"
// Register the component with class_loader.
// This acts as a sort of entry point, allowing the component to be discoverable when its library
// is being loaded into a running process.
CLASS_LOADER_REGISTER_CLASS(ros2_sensor_msgs_msg_RegionOfInterest_common, MATLABROS2MsgInterface<sensor_msgs::msg::RegionOfInterest>)
CLASS_LOADER_REGISTER_CLASS(ros2_sensor_msgs_RegionOfInterest_message, ROS2MsgElementInterfaceFactory)
#ifdef _MSC_VER
#pragma warning(pop)
#else
#pragma GCC diagnostic pop
#endif //_MSC_VER