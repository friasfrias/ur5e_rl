// Copyright 2020-2022 The MathWorks, Inc.
// Common copy functions for sensor_msgs/CameraInfo
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
#include "sensor_msgs/msg/camera_info.hpp"
#include "visibility_control.h"
#include "class_loader/multi_library_class_loader.hpp"
#include "ROS2PubSubTemplates.hpp"
class SENSOR_MSGS_EXPORT ros2_sensor_msgs_msg_CameraInfo_common : public MATLABROS2MsgInterface<sensor_msgs::msg::CameraInfo> {
  public:
    virtual ~ros2_sensor_msgs_msg_CameraInfo_common(){}
    virtual void copy_from_struct(sensor_msgs::msg::CameraInfo* msg, const matlab::data::Struct& arr, MultiLibLoader loader); 
    //----------------------------------------------------------------------------
    virtual MDArray_T get_arr(MDFactory_T& factory, const sensor_msgs::msg::CameraInfo* msg, MultiLibLoader loader, size_t size = 1);
};
  void ros2_sensor_msgs_msg_CameraInfo_common::copy_from_struct(sensor_msgs::msg::CameraInfo* msg, const matlab::data::Struct& arr,
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
        //distortion_model
        const matlab::data::CharArray distortion_model_arr = arr["distortion_model"];
        msg->distortion_model = distortion_model_arr.toAscii();
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'distortion_model' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'distortion_model' is wrong type; expected a string.");
    }
    try {
        //d
        const matlab::data::TypedArray<double> d_arr = arr["d"];
        size_t nelem = d_arr.getNumberOfElements();
        	msg->d.resize(nelem);
        	std::copy(d_arr.begin(), d_arr.begin()+nelem, msg->d.begin());
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'd' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'd' is wrong type; expected a double.");
    }
    try {
        //k
        const matlab::data::TypedArray<double> k_arr = arr["k"];
        size_t nelem = 9;
        	std::copy(k_arr.begin(), k_arr.begin()+nelem, msg->k.begin());
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'k' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'k' is wrong type; expected a double.");
    }
    try {
        //r
        const matlab::data::TypedArray<double> r_arr = arr["r"];
        size_t nelem = 9;
        	std::copy(r_arr.begin(), r_arr.begin()+nelem, msg->r.begin());
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'r' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'r' is wrong type; expected a double.");
    }
    try {
        //p
        const matlab::data::TypedArray<double> p_arr = arr["p"];
        size_t nelem = 12;
        	std::copy(p_arr.begin(), p_arr.begin()+nelem, msg->p.begin());
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'p' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'p' is wrong type; expected a double.");
    }
    try {
        //binning_x
        const matlab::data::TypedArray<uint32_t> binning_x_arr = arr["binning_x"];
        msg->binning_x = binning_x_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'binning_x' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'binning_x' is wrong type; expected a uint32.");
    }
    try {
        //binning_y
        const matlab::data::TypedArray<uint32_t> binning_y_arr = arr["binning_y"];
        msg->binning_y = binning_y_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'binning_y' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'binning_y' is wrong type; expected a uint32.");
    }
    try {
        //roi
        const matlab::data::StructArray roi_arr = arr["roi"];
        auto msgClassPtr_roi = getCommonObject<sensor_msgs::msg::RegionOfInterest>("ros2_sensor_msgs_msg_RegionOfInterest_common",loader);
        msgClassPtr_roi->copy_from_struct(&msg->roi,roi_arr[0],loader);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'roi' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'roi' is wrong type; expected a struct.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T ros2_sensor_msgs_msg_CameraInfo_common::get_arr(MDFactory_T& factory, const sensor_msgs::msg::CameraInfo* msg,
       MultiLibLoader loader, size_t size) {
    auto outArray = factory.createStructArray({size,1},{"MessageType","header","height","width","distortion_model","d","k","r","p","binning_x","binning_y","roi"});
    for(size_t ctr = 0; ctr < size; ctr++){
    outArray[ctr]["MessageType"] = factory.createCharArray("sensor_msgs/CameraInfo");
    // header
    auto currentElement_header = (msg + ctr)->header;
    auto msgClassPtr_header = getCommonObject<std_msgs::msg::Header>("ros2_std_msgs_msg_Header_common",loader);
    outArray[ctr]["header"] = msgClassPtr_header->get_arr(factory, &currentElement_header, loader);
    // height
    auto currentElement_height = (msg + ctr)->height;
    outArray[ctr]["height"] = factory.createScalar(currentElement_height);
    // width
    auto currentElement_width = (msg + ctr)->width;
    outArray[ctr]["width"] = factory.createScalar(currentElement_width);
    // distortion_model
    auto currentElement_distortion_model = (msg + ctr)->distortion_model;
    outArray[ctr]["distortion_model"] = factory.createCharArray(currentElement_distortion_model);
    // d
    auto currentElement_d = (msg + ctr)->d;
    outArray[ctr]["d"] = factory.createArray<sensor_msgs::msg::CameraInfo::_d_type::const_iterator, double>({currentElement_d.size(), 1}, currentElement_d.begin(), currentElement_d.end());
    // k
    auto currentElement_k = (msg + ctr)->k;
    outArray[ctr]["k"] = factory.createArray<sensor_msgs::msg::CameraInfo::_k_type::const_iterator, double>({currentElement_k.size(), 1}, currentElement_k.begin(), currentElement_k.end());
    // r
    auto currentElement_r = (msg + ctr)->r;
    outArray[ctr]["r"] = factory.createArray<sensor_msgs::msg::CameraInfo::_r_type::const_iterator, double>({currentElement_r.size(), 1}, currentElement_r.begin(), currentElement_r.end());
    // p
    auto currentElement_p = (msg + ctr)->p;
    outArray[ctr]["p"] = factory.createArray<sensor_msgs::msg::CameraInfo::_p_type::const_iterator, double>({currentElement_p.size(), 1}, currentElement_p.begin(), currentElement_p.end());
    // binning_x
    auto currentElement_binning_x = (msg + ctr)->binning_x;
    outArray[ctr]["binning_x"] = factory.createScalar(currentElement_binning_x);
    // binning_y
    auto currentElement_binning_y = (msg + ctr)->binning_y;
    outArray[ctr]["binning_y"] = factory.createScalar(currentElement_binning_y);
    // roi
    auto currentElement_roi = (msg + ctr)->roi;
    auto msgClassPtr_roi = getCommonObject<sensor_msgs::msg::RegionOfInterest>("ros2_sensor_msgs_msg_RegionOfInterest_common",loader);
    outArray[ctr]["roi"] = msgClassPtr_roi->get_arr(factory, &currentElement_roi, loader);
    }
    return std::move(outArray);
  } 
class SENSOR_MSGS_EXPORT ros2_sensor_msgs_CameraInfo_message : public ROS2MsgElementInterfaceFactory {
  public:
    virtual ~ros2_sensor_msgs_CameraInfo_message(){}
    virtual std::shared_ptr<MATLABPublisherInterface> generatePublisherInterface(ElementType /*type*/);
    virtual std::shared_ptr<MATLABSubscriberInterface> generateSubscriberInterface(ElementType /*type*/);
    virtual std::shared_ptr<void> generateCppMessage(ElementType /*type*/, const matlab::data::StructArray& /* arr */, MultiLibLoader /* loader */, std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* /*commonObjMap*/);
    virtual matlab::data::StructArray generateMLMessage(ElementType  /*type*/ ,void*  /* msg */, MultiLibLoader /* loader */ , std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* /*commonObjMap*/);
};  
  std::shared_ptr<MATLABPublisherInterface> 
          ros2_sensor_msgs_CameraInfo_message::generatePublisherInterface(ElementType /*type*/){
    return std::make_shared<ROS2PublisherImpl<sensor_msgs::msg::CameraInfo,ros2_sensor_msgs_msg_CameraInfo_common>>();
  }
  std::shared_ptr<MATLABSubscriberInterface> 
         ros2_sensor_msgs_CameraInfo_message::generateSubscriberInterface(ElementType /*type*/){
    return std::make_shared<ROS2SubscriberImpl<sensor_msgs::msg::CameraInfo,ros2_sensor_msgs_msg_CameraInfo_common>>();
  }
  std::shared_ptr<void> ros2_sensor_msgs_CameraInfo_message::generateCppMessage(ElementType /*type*/, 
                                           const matlab::data::StructArray& arr,
                                           MultiLibLoader loader,
                                           std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* commonObjMap){
    auto msg = std::make_shared<sensor_msgs::msg::CameraInfo>();
    ros2_sensor_msgs_msg_CameraInfo_common commonObj;
    commonObj.mCommonObjMap = commonObjMap;
    commonObj.copy_from_struct(msg.get(), arr[0], loader);
    return msg;
  }
  matlab::data::StructArray ros2_sensor_msgs_CameraInfo_message::generateMLMessage(ElementType  /*type*/ ,
                                                    void*  msg ,
                                                    MultiLibLoader  loader ,
                                                    std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>*  commonObjMap ){
    ros2_sensor_msgs_msg_CameraInfo_common commonObj;	
    commonObj.mCommonObjMap = commonObjMap;	
    MDFactory_T factory;
    return commonObj.get_arr(factory, (sensor_msgs::msg::CameraInfo*)msg, loader);			
 }
#include "class_loader/register_macro.hpp"
// Register the component with class_loader.
// This acts as a sort of entry point, allowing the component to be discoverable when its library
// is being loaded into a running process.
CLASS_LOADER_REGISTER_CLASS(ros2_sensor_msgs_msg_CameraInfo_common, MATLABROS2MsgInterface<sensor_msgs::msg::CameraInfo>)
CLASS_LOADER_REGISTER_CLASS(ros2_sensor_msgs_CameraInfo_message, ROS2MsgElementInterfaceFactory)
#ifdef _MSC_VER
#pragma warning(pop)
#else
#pragma GCC diagnostic pop
#endif //_MSC_VER