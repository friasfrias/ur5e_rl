// Copyright 2020-2022 The MathWorks, Inc.
// Common copy functions for sensor_msgs/PointCloud
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
#include "sensor_msgs/msg/point_cloud.hpp"
#include "visibility_control.h"
#include "class_loader/multi_library_class_loader.hpp"
#include "ROS2PubSubTemplates.hpp"
class SENSOR_MSGS_EXPORT ros2_sensor_msgs_msg_PointCloud_common : public MATLABROS2MsgInterface<sensor_msgs::msg::PointCloud> {
  public:
    virtual ~ros2_sensor_msgs_msg_PointCloud_common(){}
    virtual void copy_from_struct(sensor_msgs::msg::PointCloud* msg, const matlab::data::Struct& arr, MultiLibLoader loader); 
    //----------------------------------------------------------------------------
    virtual MDArray_T get_arr(MDFactory_T& factory, const sensor_msgs::msg::PointCloud* msg, MultiLibLoader loader, size_t size = 1);
};
  void ros2_sensor_msgs_msg_PointCloud_common::copy_from_struct(sensor_msgs::msg::PointCloud* msg, const matlab::data::Struct& arr,
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
        //points
        const matlab::data::StructArray points_arr = arr["points"];
        for (auto _pointsarr : points_arr) {
        	geometry_msgs::msg::Point32 _val;
        auto msgClassPtr_points = getCommonObject<geometry_msgs::msg::Point32>("ros2_geometry_msgs_msg_Point32_common",loader);
        msgClassPtr_points->copy_from_struct(&_val,_pointsarr,loader);
        	msg->points.push_back(_val);
        }
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'points' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'points' is wrong type; expected a struct.");
    }
    try {
        //channels
        const matlab::data::StructArray channels_arr = arr["channels"];
        for (auto _channelsarr : channels_arr) {
        	sensor_msgs::msg::ChannelFloat32 _val;
        auto msgClassPtr_channels = getCommonObject<sensor_msgs::msg::ChannelFloat32>("ros2_sensor_msgs_msg_ChannelFloat32_common",loader);
        msgClassPtr_channels->copy_from_struct(&_val,_channelsarr,loader);
        	msg->channels.push_back(_val);
        }
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'channels' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'channels' is wrong type; expected a struct.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T ros2_sensor_msgs_msg_PointCloud_common::get_arr(MDFactory_T& factory, const sensor_msgs::msg::PointCloud* msg,
       MultiLibLoader loader, size_t size) {
    auto outArray = factory.createStructArray({size,1},{"MessageType","header","points","channels"});
    for(size_t ctr = 0; ctr < size; ctr++){
    outArray[ctr]["MessageType"] = factory.createCharArray("sensor_msgs/PointCloud");
    // header
    auto currentElement_header = (msg + ctr)->header;
    auto msgClassPtr_header = getCommonObject<std_msgs::msg::Header>("ros2_std_msgs_msg_Header_common",loader);
    outArray[ctr]["header"] = msgClassPtr_header->get_arr(factory, &currentElement_header, loader);
    // points
    auto currentElement_points = (msg + ctr)->points;
    auto msgClassPtr_points = getCommonObject<geometry_msgs::msg::Point32>("ros2_geometry_msgs_msg_Point32_common",loader);
    outArray[ctr]["points"] = msgClassPtr_points->get_arr(factory,&currentElement_points[0],loader,currentElement_points.size());
    // channels
    auto currentElement_channels = (msg + ctr)->channels;
    auto msgClassPtr_channels = getCommonObject<sensor_msgs::msg::ChannelFloat32>("ros2_sensor_msgs_msg_ChannelFloat32_common",loader);
    outArray[ctr]["channels"] = msgClassPtr_channels->get_arr(factory,&currentElement_channels[0],loader,currentElement_channels.size());
    }
    return std::move(outArray);
  } 
class SENSOR_MSGS_EXPORT ros2_sensor_msgs_PointCloud_message : public ROS2MsgElementInterfaceFactory {
  public:
    virtual ~ros2_sensor_msgs_PointCloud_message(){}
    virtual std::shared_ptr<MATLABPublisherInterface> generatePublisherInterface(ElementType /*type*/);
    virtual std::shared_ptr<MATLABSubscriberInterface> generateSubscriberInterface(ElementType /*type*/);
    virtual std::shared_ptr<void> generateCppMessage(ElementType /*type*/, const matlab::data::StructArray& /* arr */, MultiLibLoader /* loader */, std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* /*commonObjMap*/);
    virtual matlab::data::StructArray generateMLMessage(ElementType  /*type*/ ,void*  /* msg */, MultiLibLoader /* loader */ , std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* /*commonObjMap*/);
};  
  std::shared_ptr<MATLABPublisherInterface> 
          ros2_sensor_msgs_PointCloud_message::generatePublisherInterface(ElementType /*type*/){
    return std::make_shared<ROS2PublisherImpl<sensor_msgs::msg::PointCloud,ros2_sensor_msgs_msg_PointCloud_common>>();
  }
  std::shared_ptr<MATLABSubscriberInterface> 
         ros2_sensor_msgs_PointCloud_message::generateSubscriberInterface(ElementType /*type*/){
    return std::make_shared<ROS2SubscriberImpl<sensor_msgs::msg::PointCloud,ros2_sensor_msgs_msg_PointCloud_common>>();
  }
  std::shared_ptr<void> ros2_sensor_msgs_PointCloud_message::generateCppMessage(ElementType /*type*/, 
                                           const matlab::data::StructArray& arr,
                                           MultiLibLoader loader,
                                           std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* commonObjMap){
    auto msg = std::make_shared<sensor_msgs::msg::PointCloud>();
    ros2_sensor_msgs_msg_PointCloud_common commonObj;
    commonObj.mCommonObjMap = commonObjMap;
    commonObj.copy_from_struct(msg.get(), arr[0], loader);
    return msg;
  }
  matlab::data::StructArray ros2_sensor_msgs_PointCloud_message::generateMLMessage(ElementType  /*type*/ ,
                                                    void*  msg ,
                                                    MultiLibLoader  loader ,
                                                    std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>*  commonObjMap ){
    ros2_sensor_msgs_msg_PointCloud_common commonObj;	
    commonObj.mCommonObjMap = commonObjMap;	
    MDFactory_T factory;
    return commonObj.get_arr(factory, (sensor_msgs::msg::PointCloud*)msg, loader);			
 }
#include "class_loader/register_macro.hpp"
// Register the component with class_loader.
// This acts as a sort of entry point, allowing the component to be discoverable when its library
// is being loaded into a running process.
CLASS_LOADER_REGISTER_CLASS(ros2_sensor_msgs_msg_PointCloud_common, MATLABROS2MsgInterface<sensor_msgs::msg::PointCloud>)
CLASS_LOADER_REGISTER_CLASS(ros2_sensor_msgs_PointCloud_message, ROS2MsgElementInterfaceFactory)
#ifdef _MSC_VER
#pragma warning(pop)
#else
#pragma GCC diagnostic pop
#endif //_MSC_VER