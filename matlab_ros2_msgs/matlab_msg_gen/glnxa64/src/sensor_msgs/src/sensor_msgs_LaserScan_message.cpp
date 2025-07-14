// Copyright 2020-2022 The MathWorks, Inc.
// Common copy functions for sensor_msgs/LaserScan
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
#include "sensor_msgs/msg/laser_scan.hpp"
#include "visibility_control.h"
#include "class_loader/multi_library_class_loader.hpp"
#include "ROS2PubSubTemplates.hpp"
class SENSOR_MSGS_EXPORT ros2_sensor_msgs_msg_LaserScan_common : public MATLABROS2MsgInterface<sensor_msgs::msg::LaserScan> {
  public:
    virtual ~ros2_sensor_msgs_msg_LaserScan_common(){}
    virtual void copy_from_struct(sensor_msgs::msg::LaserScan* msg, const matlab::data::Struct& arr, MultiLibLoader loader); 
    //----------------------------------------------------------------------------
    virtual MDArray_T get_arr(MDFactory_T& factory, const sensor_msgs::msg::LaserScan* msg, MultiLibLoader loader, size_t size = 1);
};
  void ros2_sensor_msgs_msg_LaserScan_common::copy_from_struct(sensor_msgs::msg::LaserScan* msg, const matlab::data::Struct& arr,
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
        //angle_min
        const matlab::data::TypedArray<float> angle_min_arr = arr["angle_min"];
        msg->angle_min = angle_min_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'angle_min' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'angle_min' is wrong type; expected a single.");
    }
    try {
        //angle_max
        const matlab::data::TypedArray<float> angle_max_arr = arr["angle_max"];
        msg->angle_max = angle_max_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'angle_max' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'angle_max' is wrong type; expected a single.");
    }
    try {
        //angle_increment
        const matlab::data::TypedArray<float> angle_increment_arr = arr["angle_increment"];
        msg->angle_increment = angle_increment_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'angle_increment' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'angle_increment' is wrong type; expected a single.");
    }
    try {
        //time_increment
        const matlab::data::TypedArray<float> time_increment_arr = arr["time_increment"];
        msg->time_increment = time_increment_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'time_increment' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'time_increment' is wrong type; expected a single.");
    }
    try {
        //scan_time
        const matlab::data::TypedArray<float> scan_time_arr = arr["scan_time"];
        msg->scan_time = scan_time_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'scan_time' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'scan_time' is wrong type; expected a single.");
    }
    try {
        //range_min
        const matlab::data::TypedArray<float> range_min_arr = arr["range_min"];
        msg->range_min = range_min_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'range_min' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'range_min' is wrong type; expected a single.");
    }
    try {
        //range_max
        const matlab::data::TypedArray<float> range_max_arr = arr["range_max"];
        msg->range_max = range_max_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'range_max' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'range_max' is wrong type; expected a single.");
    }
    try {
        //ranges
        const matlab::data::TypedArray<float> ranges_arr = arr["ranges"];
        size_t nelem = ranges_arr.getNumberOfElements();
        	msg->ranges.resize(nelem);
        	std::copy(ranges_arr.begin(), ranges_arr.begin()+nelem, msg->ranges.begin());
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'ranges' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'ranges' is wrong type; expected a single.");
    }
    try {
        //intensities
        const matlab::data::TypedArray<float> intensities_arr = arr["intensities"];
        size_t nelem = intensities_arr.getNumberOfElements();
        	msg->intensities.resize(nelem);
        	std::copy(intensities_arr.begin(), intensities_arr.begin()+nelem, msg->intensities.begin());
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'intensities' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'intensities' is wrong type; expected a single.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T ros2_sensor_msgs_msg_LaserScan_common::get_arr(MDFactory_T& factory, const sensor_msgs::msg::LaserScan* msg,
       MultiLibLoader loader, size_t size) {
    auto outArray = factory.createStructArray({size,1},{"MessageType","header","angle_min","angle_max","angle_increment","time_increment","scan_time","range_min","range_max","ranges","intensities"});
    for(size_t ctr = 0; ctr < size; ctr++){
    outArray[ctr]["MessageType"] = factory.createCharArray("sensor_msgs/LaserScan");
    // header
    auto currentElement_header = (msg + ctr)->header;
    auto msgClassPtr_header = getCommonObject<std_msgs::msg::Header>("ros2_std_msgs_msg_Header_common",loader);
    outArray[ctr]["header"] = msgClassPtr_header->get_arr(factory, &currentElement_header, loader);
    // angle_min
    auto currentElement_angle_min = (msg + ctr)->angle_min;
    outArray[ctr]["angle_min"] = factory.createScalar(currentElement_angle_min);
    // angle_max
    auto currentElement_angle_max = (msg + ctr)->angle_max;
    outArray[ctr]["angle_max"] = factory.createScalar(currentElement_angle_max);
    // angle_increment
    auto currentElement_angle_increment = (msg + ctr)->angle_increment;
    outArray[ctr]["angle_increment"] = factory.createScalar(currentElement_angle_increment);
    // time_increment
    auto currentElement_time_increment = (msg + ctr)->time_increment;
    outArray[ctr]["time_increment"] = factory.createScalar(currentElement_time_increment);
    // scan_time
    auto currentElement_scan_time = (msg + ctr)->scan_time;
    outArray[ctr]["scan_time"] = factory.createScalar(currentElement_scan_time);
    // range_min
    auto currentElement_range_min = (msg + ctr)->range_min;
    outArray[ctr]["range_min"] = factory.createScalar(currentElement_range_min);
    // range_max
    auto currentElement_range_max = (msg + ctr)->range_max;
    outArray[ctr]["range_max"] = factory.createScalar(currentElement_range_max);
    // ranges
    auto currentElement_ranges = (msg + ctr)->ranges;
    outArray[ctr]["ranges"] = factory.createArray<sensor_msgs::msg::LaserScan::_ranges_type::const_iterator, float>({currentElement_ranges.size(), 1}, currentElement_ranges.begin(), currentElement_ranges.end());
    // intensities
    auto currentElement_intensities = (msg + ctr)->intensities;
    outArray[ctr]["intensities"] = factory.createArray<sensor_msgs::msg::LaserScan::_intensities_type::const_iterator, float>({currentElement_intensities.size(), 1}, currentElement_intensities.begin(), currentElement_intensities.end());
    }
    return std::move(outArray);
  } 
class SENSOR_MSGS_EXPORT ros2_sensor_msgs_LaserScan_message : public ROS2MsgElementInterfaceFactory {
  public:
    virtual ~ros2_sensor_msgs_LaserScan_message(){}
    virtual std::shared_ptr<MATLABPublisherInterface> generatePublisherInterface(ElementType /*type*/);
    virtual std::shared_ptr<MATLABSubscriberInterface> generateSubscriberInterface(ElementType /*type*/);
    virtual std::shared_ptr<void> generateCppMessage(ElementType /*type*/, const matlab::data::StructArray& /* arr */, MultiLibLoader /* loader */, std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* /*commonObjMap*/);
    virtual matlab::data::StructArray generateMLMessage(ElementType  /*type*/ ,void*  /* msg */, MultiLibLoader /* loader */ , std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* /*commonObjMap*/);
};  
  std::shared_ptr<MATLABPublisherInterface> 
          ros2_sensor_msgs_LaserScan_message::generatePublisherInterface(ElementType /*type*/){
    return std::make_shared<ROS2PublisherImpl<sensor_msgs::msg::LaserScan,ros2_sensor_msgs_msg_LaserScan_common>>();
  }
  std::shared_ptr<MATLABSubscriberInterface> 
         ros2_sensor_msgs_LaserScan_message::generateSubscriberInterface(ElementType /*type*/){
    return std::make_shared<ROS2SubscriberImpl<sensor_msgs::msg::LaserScan,ros2_sensor_msgs_msg_LaserScan_common>>();
  }
  std::shared_ptr<void> ros2_sensor_msgs_LaserScan_message::generateCppMessage(ElementType /*type*/, 
                                           const matlab::data::StructArray& arr,
                                           MultiLibLoader loader,
                                           std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* commonObjMap){
    auto msg = std::make_shared<sensor_msgs::msg::LaserScan>();
    ros2_sensor_msgs_msg_LaserScan_common commonObj;
    commonObj.mCommonObjMap = commonObjMap;
    commonObj.copy_from_struct(msg.get(), arr[0], loader);
    return msg;
  }
  matlab::data::StructArray ros2_sensor_msgs_LaserScan_message::generateMLMessage(ElementType  /*type*/ ,
                                                    void*  msg ,
                                                    MultiLibLoader  loader ,
                                                    std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>*  commonObjMap ){
    ros2_sensor_msgs_msg_LaserScan_common commonObj;	
    commonObj.mCommonObjMap = commonObjMap;	
    MDFactory_T factory;
    return commonObj.get_arr(factory, (sensor_msgs::msg::LaserScan*)msg, loader);			
 }
#include "class_loader/register_macro.hpp"
// Register the component with class_loader.
// This acts as a sort of entry point, allowing the component to be discoverable when its library
// is being loaded into a running process.
CLASS_LOADER_REGISTER_CLASS(ros2_sensor_msgs_msg_LaserScan_common, MATLABROS2MsgInterface<sensor_msgs::msg::LaserScan>)
CLASS_LOADER_REGISTER_CLASS(ros2_sensor_msgs_LaserScan_message, ROS2MsgElementInterfaceFactory)
#ifdef _MSC_VER
#pragma warning(pop)
#else
#pragma GCC diagnostic pop
#endif //_MSC_VER