// Copyright 2020-2022 The MathWorks, Inc.
// Common copy functions for control_msgs/MecanumDriveControllerState
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
#include "control_msgs/msg/mecanum_drive_controller_state.hpp"
#include "visibility_control.h"
#include "class_loader/multi_library_class_loader.hpp"
#include "ROS2PubSubTemplates.hpp"
class CONTROL_MSGS_EXPORT ros2_control_msgs_msg_MecanumDriveControllerState_common : public MATLABROS2MsgInterface<control_msgs::msg::MecanumDriveControllerState> {
  public:
    virtual ~ros2_control_msgs_msg_MecanumDriveControllerState_common(){}
    virtual void copy_from_struct(control_msgs::msg::MecanumDriveControllerState* msg, const matlab::data::Struct& arr, MultiLibLoader loader); 
    //----------------------------------------------------------------------------
    virtual MDArray_T get_arr(MDFactory_T& factory, const control_msgs::msg::MecanumDriveControllerState* msg, MultiLibLoader loader, size_t size = 1);
};
  void ros2_control_msgs_msg_MecanumDriveControllerState_common::copy_from_struct(control_msgs::msg::MecanumDriveControllerState* msg, const matlab::data::Struct& arr,
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
        //front_left_wheel_velocity
        const matlab::data::TypedArray<double> front_left_wheel_velocity_arr = arr["front_left_wheel_velocity"];
        msg->front_left_wheel_velocity = front_left_wheel_velocity_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'front_left_wheel_velocity' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'front_left_wheel_velocity' is wrong type; expected a double.");
    }
    try {
        //back_left_wheel_velocity
        const matlab::data::TypedArray<double> back_left_wheel_velocity_arr = arr["back_left_wheel_velocity"];
        msg->back_left_wheel_velocity = back_left_wheel_velocity_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'back_left_wheel_velocity' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'back_left_wheel_velocity' is wrong type; expected a double.");
    }
    try {
        //back_right_wheel_velocity
        const matlab::data::TypedArray<double> back_right_wheel_velocity_arr = arr["back_right_wheel_velocity"];
        msg->back_right_wheel_velocity = back_right_wheel_velocity_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'back_right_wheel_velocity' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'back_right_wheel_velocity' is wrong type; expected a double.");
    }
    try {
        //front_right_wheel_velocity
        const matlab::data::TypedArray<double> front_right_wheel_velocity_arr = arr["front_right_wheel_velocity"];
        msg->front_right_wheel_velocity = front_right_wheel_velocity_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'front_right_wheel_velocity' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'front_right_wheel_velocity' is wrong type; expected a double.");
    }
    try {
        //reference_velocity
        const matlab::data::StructArray reference_velocity_arr = arr["reference_velocity"];
        auto msgClassPtr_reference_velocity = getCommonObject<geometry_msgs::msg::Twist>("ros2_geometry_msgs_msg_Twist_common",loader);
        msgClassPtr_reference_velocity->copy_from_struct(&msg->reference_velocity,reference_velocity_arr[0],loader);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'reference_velocity' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'reference_velocity' is wrong type; expected a struct.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T ros2_control_msgs_msg_MecanumDriveControllerState_common::get_arr(MDFactory_T& factory, const control_msgs::msg::MecanumDriveControllerState* msg,
       MultiLibLoader loader, size_t size) {
    auto outArray = factory.createStructArray({size,1},{"MessageType","header","front_left_wheel_velocity","back_left_wheel_velocity","back_right_wheel_velocity","front_right_wheel_velocity","reference_velocity"});
    for(size_t ctr = 0; ctr < size; ctr++){
    outArray[ctr]["MessageType"] = factory.createCharArray("control_msgs/MecanumDriveControllerState");
    // header
    auto currentElement_header = (msg + ctr)->header;
    auto msgClassPtr_header = getCommonObject<std_msgs::msg::Header>("ros2_std_msgs_msg_Header_common",loader);
    outArray[ctr]["header"] = msgClassPtr_header->get_arr(factory, &currentElement_header, loader);
    // front_left_wheel_velocity
    auto currentElement_front_left_wheel_velocity = (msg + ctr)->front_left_wheel_velocity;
    outArray[ctr]["front_left_wheel_velocity"] = factory.createScalar(currentElement_front_left_wheel_velocity);
    // back_left_wheel_velocity
    auto currentElement_back_left_wheel_velocity = (msg + ctr)->back_left_wheel_velocity;
    outArray[ctr]["back_left_wheel_velocity"] = factory.createScalar(currentElement_back_left_wheel_velocity);
    // back_right_wheel_velocity
    auto currentElement_back_right_wheel_velocity = (msg + ctr)->back_right_wheel_velocity;
    outArray[ctr]["back_right_wheel_velocity"] = factory.createScalar(currentElement_back_right_wheel_velocity);
    // front_right_wheel_velocity
    auto currentElement_front_right_wheel_velocity = (msg + ctr)->front_right_wheel_velocity;
    outArray[ctr]["front_right_wheel_velocity"] = factory.createScalar(currentElement_front_right_wheel_velocity);
    // reference_velocity
    auto currentElement_reference_velocity = (msg + ctr)->reference_velocity;
    auto msgClassPtr_reference_velocity = getCommonObject<geometry_msgs::msg::Twist>("ros2_geometry_msgs_msg_Twist_common",loader);
    outArray[ctr]["reference_velocity"] = msgClassPtr_reference_velocity->get_arr(factory, &currentElement_reference_velocity, loader);
    }
    return std::move(outArray);
  } 
class CONTROL_MSGS_EXPORT ros2_control_msgs_MecanumDriveControllerState_message : public ROS2MsgElementInterfaceFactory {
  public:
    virtual ~ros2_control_msgs_MecanumDriveControllerState_message(){}
    virtual std::shared_ptr<MATLABPublisherInterface> generatePublisherInterface(ElementType /*type*/);
    virtual std::shared_ptr<MATLABSubscriberInterface> generateSubscriberInterface(ElementType /*type*/);
    virtual std::shared_ptr<void> generateCppMessage(ElementType /*type*/, const matlab::data::StructArray& /* arr */, MultiLibLoader /* loader */, std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* /*commonObjMap*/);
    virtual matlab::data::StructArray generateMLMessage(ElementType  /*type*/ ,void*  /* msg */, MultiLibLoader /* loader */ , std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* /*commonObjMap*/);
};  
  std::shared_ptr<MATLABPublisherInterface> 
          ros2_control_msgs_MecanumDriveControllerState_message::generatePublisherInterface(ElementType /*type*/){
    return std::make_shared<ROS2PublisherImpl<control_msgs::msg::MecanumDriveControllerState,ros2_control_msgs_msg_MecanumDriveControllerState_common>>();
  }
  std::shared_ptr<MATLABSubscriberInterface> 
         ros2_control_msgs_MecanumDriveControllerState_message::generateSubscriberInterface(ElementType /*type*/){
    return std::make_shared<ROS2SubscriberImpl<control_msgs::msg::MecanumDriveControllerState,ros2_control_msgs_msg_MecanumDriveControllerState_common>>();
  }
  std::shared_ptr<void> ros2_control_msgs_MecanumDriveControllerState_message::generateCppMessage(ElementType /*type*/, 
                                           const matlab::data::StructArray& arr,
                                           MultiLibLoader loader,
                                           std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* commonObjMap){
    auto msg = std::make_shared<control_msgs::msg::MecanumDriveControllerState>();
    ros2_control_msgs_msg_MecanumDriveControllerState_common commonObj;
    commonObj.mCommonObjMap = commonObjMap;
    commonObj.copy_from_struct(msg.get(), arr[0], loader);
    return msg;
  }
  matlab::data::StructArray ros2_control_msgs_MecanumDriveControllerState_message::generateMLMessage(ElementType  /*type*/ ,
                                                    void*  msg ,
                                                    MultiLibLoader  loader ,
                                                    std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>*  commonObjMap ){
    ros2_control_msgs_msg_MecanumDriveControllerState_common commonObj;	
    commonObj.mCommonObjMap = commonObjMap;	
    MDFactory_T factory;
    return commonObj.get_arr(factory, (control_msgs::msg::MecanumDriveControllerState*)msg, loader);			
 }
#include "class_loader/register_macro.hpp"
// Register the component with class_loader.
// This acts as a sort of entry point, allowing the component to be discoverable when its library
// is being loaded into a running process.
CLASS_LOADER_REGISTER_CLASS(ros2_control_msgs_msg_MecanumDriveControllerState_common, MATLABROS2MsgInterface<control_msgs::msg::MecanumDriveControllerState>)
CLASS_LOADER_REGISTER_CLASS(ros2_control_msgs_MecanumDriveControllerState_message, ROS2MsgElementInterfaceFactory)
#ifdef _MSC_VER
#pragma warning(pop)
#else
#pragma GCC diagnostic pop
#endif //_MSC_VER