// Copyright 2020-2022 The MathWorks, Inc.
// Common copy functions for control_msgs/PidState
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
#include "control_msgs/msg/pid_state.hpp"
#include "visibility_control.h"
#include "class_loader/multi_library_class_loader.hpp"
#include "ROS2PubSubTemplates.hpp"
class CONTROL_MSGS_EXPORT ros2_control_msgs_msg_PidState_common : public MATLABROS2MsgInterface<control_msgs::msg::PidState> {
  public:
    virtual ~ros2_control_msgs_msg_PidState_common(){}
    virtual void copy_from_struct(control_msgs::msg::PidState* msg, const matlab::data::Struct& arr, MultiLibLoader loader); 
    //----------------------------------------------------------------------------
    virtual MDArray_T get_arr(MDFactory_T& factory, const control_msgs::msg::PidState* msg, MultiLibLoader loader, size_t size = 1);
};
  void ros2_control_msgs_msg_PidState_common::copy_from_struct(control_msgs::msg::PidState* msg, const matlab::data::Struct& arr,
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
        //timestep
        const matlab::data::StructArray timestep_arr = arr["timestep"];
        auto msgClassPtr_timestep = getCommonObject<builtin_interfaces::msg::Duration>("ros2_builtin_interfaces_msg_Duration_common",loader);
        msgClassPtr_timestep->copy_from_struct(&msg->timestep,timestep_arr[0],loader);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'timestep' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'timestep' is wrong type; expected a struct.");
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
        //error_dot
        const matlab::data::TypedArray<double> error_dot_arr = arr["error_dot"];
        msg->error_dot = error_dot_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'error_dot' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'error_dot' is wrong type; expected a double.");
    }
    try {
        //p_error
        const matlab::data::TypedArray<double> p_error_arr = arr["p_error"];
        msg->p_error = p_error_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'p_error' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'p_error' is wrong type; expected a double.");
    }
    try {
        //i_error
        const matlab::data::TypedArray<double> i_error_arr = arr["i_error"];
        msg->i_error = i_error_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'i_error' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'i_error' is wrong type; expected a double.");
    }
    try {
        //d_error
        const matlab::data::TypedArray<double> d_error_arr = arr["d_error"];
        msg->d_error = d_error_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'd_error' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'd_error' is wrong type; expected a double.");
    }
    try {
        //p_term
        const matlab::data::TypedArray<double> p_term_arr = arr["p_term"];
        msg->p_term = p_term_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'p_term' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'p_term' is wrong type; expected a double.");
    }
    try {
        //i_term
        const matlab::data::TypedArray<double> i_term_arr = arr["i_term"];
        msg->i_term = i_term_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'i_term' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'i_term' is wrong type; expected a double.");
    }
    try {
        //d_term
        const matlab::data::TypedArray<double> d_term_arr = arr["d_term"];
        msg->d_term = d_term_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'd_term' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'd_term' is wrong type; expected a double.");
    }
    try {
        //i_max
        const matlab::data::TypedArray<double> i_max_arr = arr["i_max"];
        msg->i_max = i_max_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'i_max' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'i_max' is wrong type; expected a double.");
    }
    try {
        //i_min
        const matlab::data::TypedArray<double> i_min_arr = arr["i_min"];
        msg->i_min = i_min_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'i_min' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'i_min' is wrong type; expected a double.");
    }
    try {
        //output
        const matlab::data::TypedArray<double> output_arr = arr["output"];
        msg->output = output_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'output' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'output' is wrong type; expected a double.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T ros2_control_msgs_msg_PidState_common::get_arr(MDFactory_T& factory, const control_msgs::msg::PidState* msg,
       MultiLibLoader loader, size_t size) {
    auto outArray = factory.createStructArray({size,1},{"MessageType","header","timestep","error","error_dot","p_error","i_error","d_error","p_term","i_term","d_term","i_max","i_min","output"});
    for(size_t ctr = 0; ctr < size; ctr++){
    outArray[ctr]["MessageType"] = factory.createCharArray("control_msgs/PidState");
    // header
    auto currentElement_header = (msg + ctr)->header;
    auto msgClassPtr_header = getCommonObject<std_msgs::msg::Header>("ros2_std_msgs_msg_Header_common",loader);
    outArray[ctr]["header"] = msgClassPtr_header->get_arr(factory, &currentElement_header, loader);
    // timestep
    auto currentElement_timestep = (msg + ctr)->timestep;
    auto msgClassPtr_timestep = getCommonObject<builtin_interfaces::msg::Duration>("ros2_builtin_interfaces_msg_Duration_common",loader);
    outArray[ctr]["timestep"] = msgClassPtr_timestep->get_arr(factory, &currentElement_timestep, loader);
    // error
    auto currentElement_error = (msg + ctr)->error;
    outArray[ctr]["error"] = factory.createScalar(currentElement_error);
    // error_dot
    auto currentElement_error_dot = (msg + ctr)->error_dot;
    outArray[ctr]["error_dot"] = factory.createScalar(currentElement_error_dot);
    // p_error
    auto currentElement_p_error = (msg + ctr)->p_error;
    outArray[ctr]["p_error"] = factory.createScalar(currentElement_p_error);
    // i_error
    auto currentElement_i_error = (msg + ctr)->i_error;
    outArray[ctr]["i_error"] = factory.createScalar(currentElement_i_error);
    // d_error
    auto currentElement_d_error = (msg + ctr)->d_error;
    outArray[ctr]["d_error"] = factory.createScalar(currentElement_d_error);
    // p_term
    auto currentElement_p_term = (msg + ctr)->p_term;
    outArray[ctr]["p_term"] = factory.createScalar(currentElement_p_term);
    // i_term
    auto currentElement_i_term = (msg + ctr)->i_term;
    outArray[ctr]["i_term"] = factory.createScalar(currentElement_i_term);
    // d_term
    auto currentElement_d_term = (msg + ctr)->d_term;
    outArray[ctr]["d_term"] = factory.createScalar(currentElement_d_term);
    // i_max
    auto currentElement_i_max = (msg + ctr)->i_max;
    outArray[ctr]["i_max"] = factory.createScalar(currentElement_i_max);
    // i_min
    auto currentElement_i_min = (msg + ctr)->i_min;
    outArray[ctr]["i_min"] = factory.createScalar(currentElement_i_min);
    // output
    auto currentElement_output = (msg + ctr)->output;
    outArray[ctr]["output"] = factory.createScalar(currentElement_output);
    }
    return std::move(outArray);
  } 
class CONTROL_MSGS_EXPORT ros2_control_msgs_PidState_message : public ROS2MsgElementInterfaceFactory {
  public:
    virtual ~ros2_control_msgs_PidState_message(){}
    virtual std::shared_ptr<MATLABPublisherInterface> generatePublisherInterface(ElementType /*type*/);
    virtual std::shared_ptr<MATLABSubscriberInterface> generateSubscriberInterface(ElementType /*type*/);
    virtual std::shared_ptr<void> generateCppMessage(ElementType /*type*/, const matlab::data::StructArray& /* arr */, MultiLibLoader /* loader */, std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* /*commonObjMap*/);
    virtual matlab::data::StructArray generateMLMessage(ElementType  /*type*/ ,void*  /* msg */, MultiLibLoader /* loader */ , std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* /*commonObjMap*/);
};  
  std::shared_ptr<MATLABPublisherInterface> 
          ros2_control_msgs_PidState_message::generatePublisherInterface(ElementType /*type*/){
    return std::make_shared<ROS2PublisherImpl<control_msgs::msg::PidState,ros2_control_msgs_msg_PidState_common>>();
  }
  std::shared_ptr<MATLABSubscriberInterface> 
         ros2_control_msgs_PidState_message::generateSubscriberInterface(ElementType /*type*/){
    return std::make_shared<ROS2SubscriberImpl<control_msgs::msg::PidState,ros2_control_msgs_msg_PidState_common>>();
  }
  std::shared_ptr<void> ros2_control_msgs_PidState_message::generateCppMessage(ElementType /*type*/, 
                                           const matlab::data::StructArray& arr,
                                           MultiLibLoader loader,
                                           std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* commonObjMap){
    auto msg = std::make_shared<control_msgs::msg::PidState>();
    ros2_control_msgs_msg_PidState_common commonObj;
    commonObj.mCommonObjMap = commonObjMap;
    commonObj.copy_from_struct(msg.get(), arr[0], loader);
    return msg;
  }
  matlab::data::StructArray ros2_control_msgs_PidState_message::generateMLMessage(ElementType  /*type*/ ,
                                                    void*  msg ,
                                                    MultiLibLoader  loader ,
                                                    std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>*  commonObjMap ){
    ros2_control_msgs_msg_PidState_common commonObj;	
    commonObj.mCommonObjMap = commonObjMap;	
    MDFactory_T factory;
    return commonObj.get_arr(factory, (control_msgs::msg::PidState*)msg, loader);			
 }
#include "class_loader/register_macro.hpp"
// Register the component with class_loader.
// This acts as a sort of entry point, allowing the component to be discoverable when its library
// is being loaded into a running process.
CLASS_LOADER_REGISTER_CLASS(ros2_control_msgs_msg_PidState_common, MATLABROS2MsgInterface<control_msgs::msg::PidState>)
CLASS_LOADER_REGISTER_CLASS(ros2_control_msgs_PidState_message, ROS2MsgElementInterfaceFactory)
#ifdef _MSC_VER
#pragma warning(pop)
#else
#pragma GCC diagnostic pop
#endif //_MSC_VER