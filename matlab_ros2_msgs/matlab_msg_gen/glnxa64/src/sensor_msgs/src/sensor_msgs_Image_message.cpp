// Copyright 2020-2022 The MathWorks, Inc.
// Common copy functions for sensor_msgs/Image
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
#include "sensor_msgs/msg/image.hpp"
#include "visibility_control.h"
#include "class_loader/multi_library_class_loader.hpp"
#include "ROS2PubSubTemplates.hpp"
class SENSOR_MSGS_EXPORT ros2_sensor_msgs_msg_Image_common : public MATLABROS2MsgInterface<sensor_msgs::msg::Image> {
  public:
    virtual ~ros2_sensor_msgs_msg_Image_common(){}
    virtual void copy_from_struct(sensor_msgs::msg::Image* msg, const matlab::data::Struct& arr, MultiLibLoader loader); 
    //----------------------------------------------------------------------------
    virtual MDArray_T get_arr(MDFactory_T& factory, const sensor_msgs::msg::Image* msg, MultiLibLoader loader, size_t size = 1);
};
  void ros2_sensor_msgs_msg_Image_common::copy_from_struct(sensor_msgs::msg::Image* msg, const matlab::data::Struct& arr,
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
        //encoding
        const matlab::data::CharArray encoding_arr = arr["encoding"];
        msg->encoding = encoding_arr.toAscii();
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'encoding' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'encoding' is wrong type; expected a string.");
    }
    try {
        //is_bigendian
        const matlab::data::TypedArray<uint8_t> is_bigendian_arr = arr["is_bigendian"];
        msg->is_bigendian = is_bigendian_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'is_bigendian' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'is_bigendian' is wrong type; expected a uint8.");
    }
    try {
        //step
        const matlab::data::TypedArray<uint32_t> step_arr = arr["step"];
        msg->step = step_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'step' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'step' is wrong type; expected a uint32.");
    }
    try {
        //data
        const matlab::data::TypedArray<uint8_t> data_arr = arr["data"];
        size_t nelem = data_arr.getNumberOfElements();
        	msg->data.resize(nelem);
        	std::copy(data_arr.begin(), data_arr.begin()+nelem, msg->data.begin());
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'data' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'data' is wrong type; expected a uint8.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T ros2_sensor_msgs_msg_Image_common::get_arr(MDFactory_T& factory, const sensor_msgs::msg::Image* msg,
       MultiLibLoader loader, size_t size) {
    auto outArray = factory.createStructArray({size,1},{"MessageType","header","height","width","encoding","is_bigendian","step","data"});
    for(size_t ctr = 0; ctr < size; ctr++){
    outArray[ctr]["MessageType"] = factory.createCharArray("sensor_msgs/Image");
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
    // encoding
    auto currentElement_encoding = (msg + ctr)->encoding;
    outArray[ctr]["encoding"] = factory.createCharArray(currentElement_encoding);
    // is_bigendian
    auto currentElement_is_bigendian = (msg + ctr)->is_bigendian;
    outArray[ctr]["is_bigendian"] = factory.createScalar(currentElement_is_bigendian);
    // step
    auto currentElement_step = (msg + ctr)->step;
    outArray[ctr]["step"] = factory.createScalar(currentElement_step);
    // data
    auto currentElement_data = (msg + ctr)->data;
    outArray[ctr]["data"] = factory.createArray<sensor_msgs::msg::Image::_data_type::const_iterator, uint8_t>({currentElement_data.size(), 1}, currentElement_data.begin(), currentElement_data.end());
    }
    return std::move(outArray);
  } 
class SENSOR_MSGS_EXPORT ros2_sensor_msgs_Image_message : public ROS2MsgElementInterfaceFactory {
  public:
    virtual ~ros2_sensor_msgs_Image_message(){}
    virtual std::shared_ptr<MATLABPublisherInterface> generatePublisherInterface(ElementType /*type*/);
    virtual std::shared_ptr<MATLABSubscriberInterface> generateSubscriberInterface(ElementType /*type*/);
    virtual std::shared_ptr<void> generateCppMessage(ElementType /*type*/, const matlab::data::StructArray& /* arr */, MultiLibLoader /* loader */, std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* /*commonObjMap*/);
    virtual matlab::data::StructArray generateMLMessage(ElementType  /*type*/ ,void*  /* msg */, MultiLibLoader /* loader */ , std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* /*commonObjMap*/);
};  
  std::shared_ptr<MATLABPublisherInterface> 
          ros2_sensor_msgs_Image_message::generatePublisherInterface(ElementType /*type*/){
    return std::make_shared<ROS2PublisherImpl<sensor_msgs::msg::Image,ros2_sensor_msgs_msg_Image_common>>();
  }
  std::shared_ptr<MATLABSubscriberInterface> 
         ros2_sensor_msgs_Image_message::generateSubscriberInterface(ElementType /*type*/){
    return std::make_shared<ROS2SubscriberImpl<sensor_msgs::msg::Image,ros2_sensor_msgs_msg_Image_common>>();
  }
  std::shared_ptr<void> ros2_sensor_msgs_Image_message::generateCppMessage(ElementType /*type*/, 
                                           const matlab::data::StructArray& arr,
                                           MultiLibLoader loader,
                                           std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* commonObjMap){
    auto msg = std::make_shared<sensor_msgs::msg::Image>();
    ros2_sensor_msgs_msg_Image_common commonObj;
    commonObj.mCommonObjMap = commonObjMap;
    commonObj.copy_from_struct(msg.get(), arr[0], loader);
    return msg;
  }
  matlab::data::StructArray ros2_sensor_msgs_Image_message::generateMLMessage(ElementType  /*type*/ ,
                                                    void*  msg ,
                                                    MultiLibLoader  loader ,
                                                    std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>*  commonObjMap ){
    ros2_sensor_msgs_msg_Image_common commonObj;	
    commonObj.mCommonObjMap = commonObjMap;	
    MDFactory_T factory;
    return commonObj.get_arr(factory, (sensor_msgs::msg::Image*)msg, loader);			
 }
#include "class_loader/register_macro.hpp"
// Register the component with class_loader.
// This acts as a sort of entry point, allowing the component to be discoverable when its library
// is being loaded into a running process.
CLASS_LOADER_REGISTER_CLASS(ros2_sensor_msgs_msg_Image_common, MATLABROS2MsgInterface<sensor_msgs::msg::Image>)
CLASS_LOADER_REGISTER_CLASS(ros2_sensor_msgs_Image_message, ROS2MsgElementInterfaceFactory)
#ifdef _MSC_VER
#pragma warning(pop)
#else
#pragma GCC diagnostic pop
#endif //_MSC_VER