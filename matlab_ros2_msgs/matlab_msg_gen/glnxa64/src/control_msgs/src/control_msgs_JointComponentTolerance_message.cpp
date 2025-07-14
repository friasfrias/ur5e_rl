// Copyright 2020-2022 The MathWorks, Inc.
// Common copy functions for control_msgs/JointComponentTolerance
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
#include "control_msgs/msg/joint_component_tolerance.hpp"
#include "visibility_control.h"
#include "class_loader/multi_library_class_loader.hpp"
#include "ROS2PubSubTemplates.hpp"
class CONTROL_MSGS_EXPORT ros2_control_msgs_msg_JointComponentTolerance_common : public MATLABROS2MsgInterface<control_msgs::msg::JointComponentTolerance> {
  public:
    virtual ~ros2_control_msgs_msg_JointComponentTolerance_common(){}
    virtual void copy_from_struct(control_msgs::msg::JointComponentTolerance* msg, const matlab::data::Struct& arr, MultiLibLoader loader); 
    //----------------------------------------------------------------------------
    virtual MDArray_T get_arr(MDFactory_T& factory, const control_msgs::msg::JointComponentTolerance* msg, MultiLibLoader loader, size_t size = 1);
};
  void ros2_control_msgs_msg_JointComponentTolerance_common::copy_from_struct(control_msgs::msg::JointComponentTolerance* msg, const matlab::data::Struct& arr,
               MultiLibLoader loader) {
    try {
        //joint_name
        const matlab::data::CharArray joint_name_arr = arr["joint_name"];
        msg->joint_name = joint_name_arr.toAscii();
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'joint_name' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'joint_name' is wrong type; expected a string.");
    }
    try {
        //component
        const matlab::data::TypedArray<uint16_t> component_arr = arr["component"];
        msg->component = component_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'component' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'component' is wrong type; expected a uint16.");
    }
    try {
        //position
        const matlab::data::TypedArray<double> position_arr = arr["position"];
        msg->position = position_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'position' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'position' is wrong type; expected a double.");
    }
    try {
        //velocity
        const matlab::data::TypedArray<double> velocity_arr = arr["velocity"];
        msg->velocity = velocity_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'velocity' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'velocity' is wrong type; expected a double.");
    }
    try {
        //acceleration
        const matlab::data::TypedArray<double> acceleration_arr = arr["acceleration"];
        msg->acceleration = acceleration_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'acceleration' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'acceleration' is wrong type; expected a double.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T ros2_control_msgs_msg_JointComponentTolerance_common::get_arr(MDFactory_T& factory, const control_msgs::msg::JointComponentTolerance* msg,
       MultiLibLoader loader, size_t size) {
    auto outArray = factory.createStructArray({size,1},{"MessageType","X_AXIS","Y_AXIS","Z_AXIS","TRANSLATION","ROTATION","joint_name","component","position","velocity","acceleration"});
    for(size_t ctr = 0; ctr < size; ctr++){
    outArray[ctr]["MessageType"] = factory.createCharArray("control_msgs/JointComponentTolerance");
    // X_AXIS
    auto currentElement_X_AXIS = (msg + ctr)->X_AXIS;
    outArray[ctr]["X_AXIS"] = factory.createScalar(currentElement_X_AXIS);
    // Y_AXIS
    auto currentElement_Y_AXIS = (msg + ctr)->Y_AXIS;
    outArray[ctr]["Y_AXIS"] = factory.createScalar(currentElement_Y_AXIS);
    // Z_AXIS
    auto currentElement_Z_AXIS = (msg + ctr)->Z_AXIS;
    outArray[ctr]["Z_AXIS"] = factory.createScalar(currentElement_Z_AXIS);
    // TRANSLATION
    auto currentElement_TRANSLATION = (msg + ctr)->TRANSLATION;
    outArray[ctr]["TRANSLATION"] = factory.createScalar(currentElement_TRANSLATION);
    // ROTATION
    auto currentElement_ROTATION = (msg + ctr)->ROTATION;
    outArray[ctr]["ROTATION"] = factory.createScalar(currentElement_ROTATION);
    // joint_name
    auto currentElement_joint_name = (msg + ctr)->joint_name;
    outArray[ctr]["joint_name"] = factory.createCharArray(currentElement_joint_name);
    // component
    auto currentElement_component = (msg + ctr)->component;
    outArray[ctr]["component"] = factory.createScalar(currentElement_component);
    // position
    auto currentElement_position = (msg + ctr)->position;
    outArray[ctr]["position"] = factory.createScalar(currentElement_position);
    // velocity
    auto currentElement_velocity = (msg + ctr)->velocity;
    outArray[ctr]["velocity"] = factory.createScalar(currentElement_velocity);
    // acceleration
    auto currentElement_acceleration = (msg + ctr)->acceleration;
    outArray[ctr]["acceleration"] = factory.createScalar(currentElement_acceleration);
    }
    return std::move(outArray);
  } 
class CONTROL_MSGS_EXPORT ros2_control_msgs_JointComponentTolerance_message : public ROS2MsgElementInterfaceFactory {
  public:
    virtual ~ros2_control_msgs_JointComponentTolerance_message(){}
    virtual std::shared_ptr<MATLABPublisherInterface> generatePublisherInterface(ElementType /*type*/);
    virtual std::shared_ptr<MATLABSubscriberInterface> generateSubscriberInterface(ElementType /*type*/);
    virtual std::shared_ptr<void> generateCppMessage(ElementType /*type*/, const matlab::data::StructArray& /* arr */, MultiLibLoader /* loader */, std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* /*commonObjMap*/);
    virtual matlab::data::StructArray generateMLMessage(ElementType  /*type*/ ,void*  /* msg */, MultiLibLoader /* loader */ , std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* /*commonObjMap*/);
};  
  std::shared_ptr<MATLABPublisherInterface> 
          ros2_control_msgs_JointComponentTolerance_message::generatePublisherInterface(ElementType /*type*/){
    return std::make_shared<ROS2PublisherImpl<control_msgs::msg::JointComponentTolerance,ros2_control_msgs_msg_JointComponentTolerance_common>>();
  }
  std::shared_ptr<MATLABSubscriberInterface> 
         ros2_control_msgs_JointComponentTolerance_message::generateSubscriberInterface(ElementType /*type*/){
    return std::make_shared<ROS2SubscriberImpl<control_msgs::msg::JointComponentTolerance,ros2_control_msgs_msg_JointComponentTolerance_common>>();
  }
  std::shared_ptr<void> ros2_control_msgs_JointComponentTolerance_message::generateCppMessage(ElementType /*type*/, 
                                           const matlab::data::StructArray& arr,
                                           MultiLibLoader loader,
                                           std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* commonObjMap){
    auto msg = std::make_shared<control_msgs::msg::JointComponentTolerance>();
    ros2_control_msgs_msg_JointComponentTolerance_common commonObj;
    commonObj.mCommonObjMap = commonObjMap;
    commonObj.copy_from_struct(msg.get(), arr[0], loader);
    return msg;
  }
  matlab::data::StructArray ros2_control_msgs_JointComponentTolerance_message::generateMLMessage(ElementType  /*type*/ ,
                                                    void*  msg ,
                                                    MultiLibLoader  loader ,
                                                    std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>*  commonObjMap ){
    ros2_control_msgs_msg_JointComponentTolerance_common commonObj;	
    commonObj.mCommonObjMap = commonObjMap;	
    MDFactory_T factory;
    return commonObj.get_arr(factory, (control_msgs::msg::JointComponentTolerance*)msg, loader);			
 }
#include "class_loader/register_macro.hpp"
// Register the component with class_loader.
// This acts as a sort of entry point, allowing the component to be discoverable when its library
// is being loaded into a running process.
CLASS_LOADER_REGISTER_CLASS(ros2_control_msgs_msg_JointComponentTolerance_common, MATLABROS2MsgInterface<control_msgs::msg::JointComponentTolerance>)
CLASS_LOADER_REGISTER_CLASS(ros2_control_msgs_JointComponentTolerance_message, ROS2MsgElementInterfaceFactory)
#ifdef _MSC_VER
#pragma warning(pop)
#else
#pragma GCC diagnostic pop
#endif //_MSC_VER