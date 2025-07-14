// Copyright 2020-2022 The MathWorks, Inc.
// Common copy functions for control_msgs/JointControllerState
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
#include "control_msgs/msg/joint_controller_state.hpp"
#include "visibility_control.h"
#include "class_loader/multi_library_class_loader.hpp"
#include "ROS2PubSubTemplates.hpp"
class CONTROL_MSGS_EXPORT ros2_control_msgs_msg_JointControllerState_common : public MATLABROS2MsgInterface<control_msgs::msg::JointControllerState> {
  public:
    virtual ~ros2_control_msgs_msg_JointControllerState_common(){}
    virtual void copy_from_struct(control_msgs::msg::JointControllerState* msg, const matlab::data::Struct& arr, MultiLibLoader loader); 
    //----------------------------------------------------------------------------
    virtual MDArray_T get_arr(MDFactory_T& factory, const control_msgs::msg::JointControllerState* msg, MultiLibLoader loader, size_t size = 1);
};
  void ros2_control_msgs_msg_JointControllerState_common::copy_from_struct(control_msgs::msg::JointControllerState* msg, const matlab::data::Struct& arr,
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
        //set_point
        const matlab::data::TypedArray<double> set_point_arr = arr["set_point"];
        msg->set_point = set_point_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'set_point' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'set_point' is wrong type; expected a double.");
    }
    try {
        //process_value
        const matlab::data::TypedArray<double> process_value_arr = arr["process_value"];
        msg->process_value = process_value_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'process_value' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'process_value' is wrong type; expected a double.");
    }
    try {
        //process_value_dot
        const matlab::data::TypedArray<double> process_value_dot_arr = arr["process_value_dot"];
        msg->process_value_dot = process_value_dot_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'process_value_dot' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'process_value_dot' is wrong type; expected a double.");
    }
    try {
        //error
        const matlab::data::TypedArray<double> error_arr = arr["error"];
        msg->error = error_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'error' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'error' is wrong type; expected a double.");
    }
    try {
        //time_step
        const matlab::data::TypedArray<double> time_step_arr = arr["time_step"];
        msg->time_step = time_step_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'time_step' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'time_step' is wrong type; expected a double.");
    }
    try {
        //command
        const matlab::data::TypedArray<double> command_arr = arr["command"];
        msg->command = command_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'command' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'command' is wrong type; expected a double.");
    }
    try {
        //p
        const matlab::data::TypedArray<double> p_arr = arr["p"];
        msg->p = p_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'p' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'p' is wrong type; expected a double.");
    }
    try {
        //i
        const matlab::data::TypedArray<double> i_arr = arr["i"];
        msg->i = i_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'i' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'i' is wrong type; expected a double.");
    }
    try {
        //d
        const matlab::data::TypedArray<double> d_arr = arr["d"];
        msg->d = d_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'd' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'd' is wrong type; expected a double.");
    }
    try {
        //i_clamp
        const matlab::data::TypedArray<double> i_clamp_arr = arr["i_clamp"];
        msg->i_clamp = i_clamp_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'i_clamp' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'i_clamp' is wrong type; expected a double.");
    }
    try {
        //antiwindup
        const matlab::data::TypedArray<bool> antiwindup_arr = arr["antiwindup"];
        msg->antiwindup = antiwindup_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'antiwindup' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'antiwindup' is wrong type; expected a logical.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T ros2_control_msgs_msg_JointControllerState_common::get_arr(MDFactory_T& factory, const control_msgs::msg::JointControllerState* msg,
       MultiLibLoader loader, size_t size) {
    auto outArray = factory.createStructArray({size,1},{"MessageType","header","set_point","process_value","process_value_dot","error","time_step","command","p","i","d","i_clamp","antiwindup"});
    for(size_t ctr = 0; ctr < size; ctr++){
    outArray[ctr]["MessageType"] = factory.createCharArray("control_msgs/JointControllerState");
    // header
    auto currentElement_header = (msg + ctr)->header;
    auto msgClassPtr_header = getCommonObject<std_msgs::msg::Header>("ros2_std_msgs_msg_Header_common",loader);
    outArray[ctr]["header"] = msgClassPtr_header->get_arr(factory, &currentElement_header, loader);
    // set_point
    auto currentElement_set_point = (msg + ctr)->set_point;
    outArray[ctr]["set_point"] = factory.createScalar(currentElement_set_point);
    // process_value
    auto currentElement_process_value = (msg + ctr)->process_value;
    outArray[ctr]["process_value"] = factory.createScalar(currentElement_process_value);
    // process_value_dot
    auto currentElement_process_value_dot = (msg + ctr)->process_value_dot;
    outArray[ctr]["process_value_dot"] = factory.createScalar(currentElement_process_value_dot);
    // error
    auto currentElement_error = (msg + ctr)->error;
    outArray[ctr]["error"] = factory.createScalar(currentElement_error);
    // time_step
    auto currentElement_time_step = (msg + ctr)->time_step;
    outArray[ctr]["time_step"] = factory.createScalar(currentElement_time_step);
    // command
    auto currentElement_command = (msg + ctr)->command;
    outArray[ctr]["command"] = factory.createScalar(currentElement_command);
    // p
    auto currentElement_p = (msg + ctr)->p;
    outArray[ctr]["p"] = factory.createScalar(currentElement_p);
    // i
    auto currentElement_i = (msg + ctr)->i;
    outArray[ctr]["i"] = factory.createScalar(currentElement_i);
    // d
    auto currentElement_d = (msg + ctr)->d;
    outArray[ctr]["d"] = factory.createScalar(currentElement_d);
    // i_clamp
    auto currentElement_i_clamp = (msg + ctr)->i_clamp;
    outArray[ctr]["i_clamp"] = factory.createScalar(currentElement_i_clamp);
    // antiwindup
    auto currentElement_antiwindup = (msg + ctr)->antiwindup;
    outArray[ctr]["antiwindup"] = factory.createScalar(currentElement_antiwindup);
    }
    return std::move(outArray);
  } 
class CONTROL_MSGS_EXPORT ros2_control_msgs_JointControllerState_message : public ROS2MsgElementInterfaceFactory {
  public:
    virtual ~ros2_control_msgs_JointControllerState_message(){}
    virtual std::shared_ptr<MATLABPublisherInterface> generatePublisherInterface(ElementType /*type*/);
    virtual std::shared_ptr<MATLABSubscriberInterface> generateSubscriberInterface(ElementType /*type*/);
    virtual std::shared_ptr<void> generateCppMessage(ElementType /*type*/, const matlab::data::StructArray& /* arr */, MultiLibLoader /* loader */, std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* /*commonObjMap*/);
    virtual matlab::data::StructArray generateMLMessage(ElementType  /*type*/ ,void*  /* msg */, MultiLibLoader /* loader */ , std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* /*commonObjMap*/);
};  
  std::shared_ptr<MATLABPublisherInterface> 
          ros2_control_msgs_JointControllerState_message::generatePublisherInterface(ElementType /*type*/){
    return std::make_shared<ROS2PublisherImpl<control_msgs::msg::JointControllerState,ros2_control_msgs_msg_JointControllerState_common>>();
  }
  std::shared_ptr<MATLABSubscriberInterface> 
         ros2_control_msgs_JointControllerState_message::generateSubscriberInterface(ElementType /*type*/){
    return std::make_shared<ROS2SubscriberImpl<control_msgs::msg::JointControllerState,ros2_control_msgs_msg_JointControllerState_common>>();
  }
  std::shared_ptr<void> ros2_control_msgs_JointControllerState_message::generateCppMessage(ElementType /*type*/, 
                                           const matlab::data::StructArray& arr,
                                           MultiLibLoader loader,
                                           std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* commonObjMap){
    auto msg = std::make_shared<control_msgs::msg::JointControllerState>();
    ros2_control_msgs_msg_JointControllerState_common commonObj;
    commonObj.mCommonObjMap = commonObjMap;
    commonObj.copy_from_struct(msg.get(), arr[0], loader);
    return msg;
  }
  matlab::data::StructArray ros2_control_msgs_JointControllerState_message::generateMLMessage(ElementType  /*type*/ ,
                                                    void*  msg ,
                                                    MultiLibLoader  loader ,
                                                    std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>*  commonObjMap ){
    ros2_control_msgs_msg_JointControllerState_common commonObj;	
    commonObj.mCommonObjMap = commonObjMap;	
    MDFactory_T factory;
    return commonObj.get_arr(factory, (control_msgs::msg::JointControllerState*)msg, loader);			
 }
#include "class_loader/register_macro.hpp"
// Register the component with class_loader.
// This acts as a sort of entry point, allowing the component to be discoverable when its library
// is being loaded into a running process.
CLASS_LOADER_REGISTER_CLASS(ros2_control_msgs_msg_JointControllerState_common, MATLABROS2MsgInterface<control_msgs::msg::JointControllerState>)
CLASS_LOADER_REGISTER_CLASS(ros2_control_msgs_JointControllerState_message, ROS2MsgElementInterfaceFactory)
#ifdef _MSC_VER
#pragma warning(pop)
#else
#pragma GCC diagnostic pop
#endif //_MSC_VER