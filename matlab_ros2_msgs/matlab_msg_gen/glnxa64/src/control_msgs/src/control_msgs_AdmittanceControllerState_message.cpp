// Copyright 2020-2022 The MathWorks, Inc.
// Common copy functions for control_msgs/AdmittanceControllerState
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
#include "control_msgs/msg/admittance_controller_state.hpp"
#include "visibility_control.h"
#include "class_loader/multi_library_class_loader.hpp"
#include "ROS2PubSubTemplates.hpp"
class CONTROL_MSGS_EXPORT ros2_control_msgs_msg_AdmittanceControllerState_common : public MATLABROS2MsgInterface<control_msgs::msg::AdmittanceControllerState> {
  public:
    virtual ~ros2_control_msgs_msg_AdmittanceControllerState_common(){}
    virtual void copy_from_struct(control_msgs::msg::AdmittanceControllerState* msg, const matlab::data::Struct& arr, MultiLibLoader loader); 
    //----------------------------------------------------------------------------
    virtual MDArray_T get_arr(MDFactory_T& factory, const control_msgs::msg::AdmittanceControllerState* msg, MultiLibLoader loader, size_t size = 1);
};
  void ros2_control_msgs_msg_AdmittanceControllerState_common::copy_from_struct(control_msgs::msg::AdmittanceControllerState* msg, const matlab::data::Struct& arr,
               MultiLibLoader loader) {
    try {
        //mass
        const matlab::data::StructArray mass_arr = arr["mass"];
        auto msgClassPtr_mass = getCommonObject<std_msgs::msg::Float64MultiArray>("ros2_std_msgs_msg_Float64MultiArray_common",loader);
        msgClassPtr_mass->copy_from_struct(&msg->mass,mass_arr[0],loader);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'mass' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'mass' is wrong type; expected a struct.");
    }
    try {
        //damping
        const matlab::data::StructArray damping_arr = arr["damping"];
        auto msgClassPtr_damping = getCommonObject<std_msgs::msg::Float64MultiArray>("ros2_std_msgs_msg_Float64MultiArray_common",loader);
        msgClassPtr_damping->copy_from_struct(&msg->damping,damping_arr[0],loader);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'damping' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'damping' is wrong type; expected a struct.");
    }
    try {
        //stiffness
        const matlab::data::StructArray stiffness_arr = arr["stiffness"];
        auto msgClassPtr_stiffness = getCommonObject<std_msgs::msg::Float64MultiArray>("ros2_std_msgs_msg_Float64MultiArray_common",loader);
        msgClassPtr_stiffness->copy_from_struct(&msg->stiffness,stiffness_arr[0],loader);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'stiffness' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'stiffness' is wrong type; expected a struct.");
    }
    try {
        //rot_base_control
        const matlab::data::StructArray rot_base_control_arr = arr["rot_base_control"];
        auto msgClassPtr_rot_base_control = getCommonObject<geometry_msgs::msg::Quaternion>("ros2_geometry_msgs_msg_Quaternion_common",loader);
        msgClassPtr_rot_base_control->copy_from_struct(&msg->rot_base_control,rot_base_control_arr[0],loader);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'rot_base_control' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'rot_base_control' is wrong type; expected a struct.");
    }
    try {
        //ref_trans_base_ft
        const matlab::data::StructArray ref_trans_base_ft_arr = arr["ref_trans_base_ft"];
        auto msgClassPtr_ref_trans_base_ft = getCommonObject<geometry_msgs::msg::TransformStamped>("ros2_geometry_msgs_msg_TransformStamped_common",loader);
        msgClassPtr_ref_trans_base_ft->copy_from_struct(&msg->ref_trans_base_ft,ref_trans_base_ft_arr[0],loader);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'ref_trans_base_ft' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'ref_trans_base_ft' is wrong type; expected a struct.");
    }
    try {
        //selected_axes
        const matlab::data::StructArray selected_axes_arr = arr["selected_axes"];
        auto msgClassPtr_selected_axes = getCommonObject<std_msgs::msg::Int8MultiArray>("ros2_std_msgs_msg_Int8MultiArray_common",loader);
        msgClassPtr_selected_axes->copy_from_struct(&msg->selected_axes,selected_axes_arr[0],loader);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'selected_axes' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'selected_axes' is wrong type; expected a struct.");
    }
    try {
        //ft_sensor_frame
        const matlab::data::StructArray ft_sensor_frame_arr = arr["ft_sensor_frame"];
        auto msgClassPtr_ft_sensor_frame = getCommonObject<std_msgs::msg::String>("ros2_std_msgs_msg_String_common",loader);
        msgClassPtr_ft_sensor_frame->copy_from_struct(&msg->ft_sensor_frame,ft_sensor_frame_arr[0],loader);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'ft_sensor_frame' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'ft_sensor_frame' is wrong type; expected a struct.");
    }
    try {
        //admittance_position
        const matlab::data::StructArray admittance_position_arr = arr["admittance_position"];
        auto msgClassPtr_admittance_position = getCommonObject<geometry_msgs::msg::TransformStamped>("ros2_geometry_msgs_msg_TransformStamped_common",loader);
        msgClassPtr_admittance_position->copy_from_struct(&msg->admittance_position,admittance_position_arr[0],loader);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'admittance_position' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'admittance_position' is wrong type; expected a struct.");
    }
    try {
        //admittance_acceleration
        const matlab::data::StructArray admittance_acceleration_arr = arr["admittance_acceleration"];
        auto msgClassPtr_admittance_acceleration = getCommonObject<geometry_msgs::msg::TwistStamped>("ros2_geometry_msgs_msg_TwistStamped_common",loader);
        msgClassPtr_admittance_acceleration->copy_from_struct(&msg->admittance_acceleration,admittance_acceleration_arr[0],loader);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'admittance_acceleration' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'admittance_acceleration' is wrong type; expected a struct.");
    }
    try {
        //admittance_velocity
        const matlab::data::StructArray admittance_velocity_arr = arr["admittance_velocity"];
        auto msgClassPtr_admittance_velocity = getCommonObject<geometry_msgs::msg::TwistStamped>("ros2_geometry_msgs_msg_TwistStamped_common",loader);
        msgClassPtr_admittance_velocity->copy_from_struct(&msg->admittance_velocity,admittance_velocity_arr[0],loader);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'admittance_velocity' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'admittance_velocity' is wrong type; expected a struct.");
    }
    try {
        //wrench_base
        const matlab::data::StructArray wrench_base_arr = arr["wrench_base"];
        auto msgClassPtr_wrench_base = getCommonObject<geometry_msgs::msg::WrenchStamped>("ros2_geometry_msgs_msg_WrenchStamped_common",loader);
        msgClassPtr_wrench_base->copy_from_struct(&msg->wrench_base,wrench_base_arr[0],loader);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'wrench_base' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'wrench_base' is wrong type; expected a struct.");
    }
    try {
        //joint_state
        const matlab::data::StructArray joint_state_arr = arr["joint_state"];
        auto msgClassPtr_joint_state = getCommonObject<sensor_msgs::msg::JointState>("ros2_sensor_msgs_msg_JointState_common",loader);
        msgClassPtr_joint_state->copy_from_struct(&msg->joint_state,joint_state_arr[0],loader);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'joint_state' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'joint_state' is wrong type; expected a struct.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T ros2_control_msgs_msg_AdmittanceControllerState_common::get_arr(MDFactory_T& factory, const control_msgs::msg::AdmittanceControllerState* msg,
       MultiLibLoader loader, size_t size) {
    auto outArray = factory.createStructArray({size,1},{"MessageType","mass","damping","stiffness","rot_base_control","ref_trans_base_ft","selected_axes","ft_sensor_frame","admittance_position","admittance_acceleration","admittance_velocity","wrench_base","joint_state"});
    for(size_t ctr = 0; ctr < size; ctr++){
    outArray[ctr]["MessageType"] = factory.createCharArray("control_msgs/AdmittanceControllerState");
    // mass
    auto currentElement_mass = (msg + ctr)->mass;
    auto msgClassPtr_mass = getCommonObject<std_msgs::msg::Float64MultiArray>("ros2_std_msgs_msg_Float64MultiArray_common",loader);
    outArray[ctr]["mass"] = msgClassPtr_mass->get_arr(factory, &currentElement_mass, loader);
    // damping
    auto currentElement_damping = (msg + ctr)->damping;
    auto msgClassPtr_damping = getCommonObject<std_msgs::msg::Float64MultiArray>("ros2_std_msgs_msg_Float64MultiArray_common",loader);
    outArray[ctr]["damping"] = msgClassPtr_damping->get_arr(factory, &currentElement_damping, loader);
    // stiffness
    auto currentElement_stiffness = (msg + ctr)->stiffness;
    auto msgClassPtr_stiffness = getCommonObject<std_msgs::msg::Float64MultiArray>("ros2_std_msgs_msg_Float64MultiArray_common",loader);
    outArray[ctr]["stiffness"] = msgClassPtr_stiffness->get_arr(factory, &currentElement_stiffness, loader);
    // rot_base_control
    auto currentElement_rot_base_control = (msg + ctr)->rot_base_control;
    auto msgClassPtr_rot_base_control = getCommonObject<geometry_msgs::msg::Quaternion>("ros2_geometry_msgs_msg_Quaternion_common",loader);
    outArray[ctr]["rot_base_control"] = msgClassPtr_rot_base_control->get_arr(factory, &currentElement_rot_base_control, loader);
    // ref_trans_base_ft
    auto currentElement_ref_trans_base_ft = (msg + ctr)->ref_trans_base_ft;
    auto msgClassPtr_ref_trans_base_ft = getCommonObject<geometry_msgs::msg::TransformStamped>("ros2_geometry_msgs_msg_TransformStamped_common",loader);
    outArray[ctr]["ref_trans_base_ft"] = msgClassPtr_ref_trans_base_ft->get_arr(factory, &currentElement_ref_trans_base_ft, loader);
    // selected_axes
    auto currentElement_selected_axes = (msg + ctr)->selected_axes;
    auto msgClassPtr_selected_axes = getCommonObject<std_msgs::msg::Int8MultiArray>("ros2_std_msgs_msg_Int8MultiArray_common",loader);
    outArray[ctr]["selected_axes"] = msgClassPtr_selected_axes->get_arr(factory, &currentElement_selected_axes, loader);
    // ft_sensor_frame
    auto currentElement_ft_sensor_frame = (msg + ctr)->ft_sensor_frame;
    auto msgClassPtr_ft_sensor_frame = getCommonObject<std_msgs::msg::String>("ros2_std_msgs_msg_String_common",loader);
    outArray[ctr]["ft_sensor_frame"] = msgClassPtr_ft_sensor_frame->get_arr(factory, &currentElement_ft_sensor_frame, loader);
    // admittance_position
    auto currentElement_admittance_position = (msg + ctr)->admittance_position;
    auto msgClassPtr_admittance_position = getCommonObject<geometry_msgs::msg::TransformStamped>("ros2_geometry_msgs_msg_TransformStamped_common",loader);
    outArray[ctr]["admittance_position"] = msgClassPtr_admittance_position->get_arr(factory, &currentElement_admittance_position, loader);
    // admittance_acceleration
    auto currentElement_admittance_acceleration = (msg + ctr)->admittance_acceleration;
    auto msgClassPtr_admittance_acceleration = getCommonObject<geometry_msgs::msg::TwistStamped>("ros2_geometry_msgs_msg_TwistStamped_common",loader);
    outArray[ctr]["admittance_acceleration"] = msgClassPtr_admittance_acceleration->get_arr(factory, &currentElement_admittance_acceleration, loader);
    // admittance_velocity
    auto currentElement_admittance_velocity = (msg + ctr)->admittance_velocity;
    auto msgClassPtr_admittance_velocity = getCommonObject<geometry_msgs::msg::TwistStamped>("ros2_geometry_msgs_msg_TwistStamped_common",loader);
    outArray[ctr]["admittance_velocity"] = msgClassPtr_admittance_velocity->get_arr(factory, &currentElement_admittance_velocity, loader);
    // wrench_base
    auto currentElement_wrench_base = (msg + ctr)->wrench_base;
    auto msgClassPtr_wrench_base = getCommonObject<geometry_msgs::msg::WrenchStamped>("ros2_geometry_msgs_msg_WrenchStamped_common",loader);
    outArray[ctr]["wrench_base"] = msgClassPtr_wrench_base->get_arr(factory, &currentElement_wrench_base, loader);
    // joint_state
    auto currentElement_joint_state = (msg + ctr)->joint_state;
    auto msgClassPtr_joint_state = getCommonObject<sensor_msgs::msg::JointState>("ros2_sensor_msgs_msg_JointState_common",loader);
    outArray[ctr]["joint_state"] = msgClassPtr_joint_state->get_arr(factory, &currentElement_joint_state, loader);
    }
    return std::move(outArray);
  } 
class CONTROL_MSGS_EXPORT ros2_control_msgs_AdmittanceControllerState_message : public ROS2MsgElementInterfaceFactory {
  public:
    virtual ~ros2_control_msgs_AdmittanceControllerState_message(){}
    virtual std::shared_ptr<MATLABPublisherInterface> generatePublisherInterface(ElementType /*type*/);
    virtual std::shared_ptr<MATLABSubscriberInterface> generateSubscriberInterface(ElementType /*type*/);
    virtual std::shared_ptr<void> generateCppMessage(ElementType /*type*/, const matlab::data::StructArray& /* arr */, MultiLibLoader /* loader */, std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* /*commonObjMap*/);
    virtual matlab::data::StructArray generateMLMessage(ElementType  /*type*/ ,void*  /* msg */, MultiLibLoader /* loader */ , std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* /*commonObjMap*/);
};  
  std::shared_ptr<MATLABPublisherInterface> 
          ros2_control_msgs_AdmittanceControllerState_message::generatePublisherInterface(ElementType /*type*/){
    return std::make_shared<ROS2PublisherImpl<control_msgs::msg::AdmittanceControllerState,ros2_control_msgs_msg_AdmittanceControllerState_common>>();
  }
  std::shared_ptr<MATLABSubscriberInterface> 
         ros2_control_msgs_AdmittanceControllerState_message::generateSubscriberInterface(ElementType /*type*/){
    return std::make_shared<ROS2SubscriberImpl<control_msgs::msg::AdmittanceControllerState,ros2_control_msgs_msg_AdmittanceControllerState_common>>();
  }
  std::shared_ptr<void> ros2_control_msgs_AdmittanceControllerState_message::generateCppMessage(ElementType /*type*/, 
                                           const matlab::data::StructArray& arr,
                                           MultiLibLoader loader,
                                           std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* commonObjMap){
    auto msg = std::make_shared<control_msgs::msg::AdmittanceControllerState>();
    ros2_control_msgs_msg_AdmittanceControllerState_common commonObj;
    commonObj.mCommonObjMap = commonObjMap;
    commonObj.copy_from_struct(msg.get(), arr[0], loader);
    return msg;
  }
  matlab::data::StructArray ros2_control_msgs_AdmittanceControllerState_message::generateMLMessage(ElementType  /*type*/ ,
                                                    void*  msg ,
                                                    MultiLibLoader  loader ,
                                                    std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>*  commonObjMap ){
    ros2_control_msgs_msg_AdmittanceControllerState_common commonObj;	
    commonObj.mCommonObjMap = commonObjMap;	
    MDFactory_T factory;
    return commonObj.get_arr(factory, (control_msgs::msg::AdmittanceControllerState*)msg, loader);			
 }
#include "class_loader/register_macro.hpp"
// Register the component with class_loader.
// This acts as a sort of entry point, allowing the component to be discoverable when its library
// is being loaded into a running process.
CLASS_LOADER_REGISTER_CLASS(ros2_control_msgs_msg_AdmittanceControllerState_common, MATLABROS2MsgInterface<control_msgs::msg::AdmittanceControllerState>)
CLASS_LOADER_REGISTER_CLASS(ros2_control_msgs_AdmittanceControllerState_message, ROS2MsgElementInterfaceFactory)
#ifdef _MSC_VER
#pragma warning(pop)
#else
#pragma GCC diagnostic pop
#endif //_MSC_VER