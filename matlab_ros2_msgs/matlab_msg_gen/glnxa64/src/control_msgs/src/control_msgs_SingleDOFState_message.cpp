// Copyright 2020-2022 The MathWorks, Inc.
// Common copy functions for control_msgs/SingleDOFState
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
#include "control_msgs/msg/single_dof_state.hpp"
#include "visibility_control.h"
#include "class_loader/multi_library_class_loader.hpp"
#include "ROS2PubSubTemplates.hpp"
class CONTROL_MSGS_EXPORT ros2_control_msgs_msg_SingleDOFState_common : public MATLABROS2MsgInterface<control_msgs::msg::SingleDOFState> {
  public:
    virtual ~ros2_control_msgs_msg_SingleDOFState_common(){}
    virtual void copy_from_struct(control_msgs::msg::SingleDOFState* msg, const matlab::data::Struct& arr, MultiLibLoader loader); 
    //----------------------------------------------------------------------------
    virtual MDArray_T get_arr(MDFactory_T& factory, const control_msgs::msg::SingleDOFState* msg, MultiLibLoader loader, size_t size = 1);
};
  void ros2_control_msgs_msg_SingleDOFState_common::copy_from_struct(control_msgs::msg::SingleDOFState* msg, const matlab::data::Struct& arr,
               MultiLibLoader loader) {
    try {
        //name
        const matlab::data::CharArray name_arr = arr["name"];
        msg->name = name_arr.toAscii();
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'name' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'name' is wrong type; expected a string.");
    }
    try {
        //reference
        const matlab::data::TypedArray<double> reference_arr = arr["reference"];
        msg->reference = reference_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'reference' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'reference' is wrong type; expected a double.");
    }
    try {
        //feedback
        const matlab::data::TypedArray<double> feedback_arr = arr["feedback"];
        msg->feedback = feedback_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'feedback' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'feedback' is wrong type; expected a double.");
    }
    try {
        //feedback_dot
        const matlab::data::TypedArray<double> feedback_dot_arr = arr["feedback_dot"];
        msg->feedback_dot = feedback_dot_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'feedback_dot' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'feedback_dot' is wrong type; expected a double.");
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
        //time_step
        const matlab::data::TypedArray<double> time_step_arr = arr["time_step"];
        msg->time_step = time_step_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'time_step' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'time_step' is wrong type; expected a double.");
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
  MDArray_T ros2_control_msgs_msg_SingleDOFState_common::get_arr(MDFactory_T& factory, const control_msgs::msg::SingleDOFState* msg,
       MultiLibLoader loader, size_t size) {
    auto outArray = factory.createStructArray({size,1},{"MessageType","name","reference","feedback","feedback_dot","error","error_dot","time_step","output"});
    for(size_t ctr = 0; ctr < size; ctr++){
    outArray[ctr]["MessageType"] = factory.createCharArray("control_msgs/SingleDOFState");
    // name
    auto currentElement_name = (msg + ctr)->name;
    outArray[ctr]["name"] = factory.createCharArray(currentElement_name);
    // reference
    auto currentElement_reference = (msg + ctr)->reference;
    outArray[ctr]["reference"] = factory.createScalar(currentElement_reference);
    // feedback
    auto currentElement_feedback = (msg + ctr)->feedback;
    outArray[ctr]["feedback"] = factory.createScalar(currentElement_feedback);
    // feedback_dot
    auto currentElement_feedback_dot = (msg + ctr)->feedback_dot;
    outArray[ctr]["feedback_dot"] = factory.createScalar(currentElement_feedback_dot);
    // error
    auto currentElement_error = (msg + ctr)->error;
    outArray[ctr]["error"] = factory.createScalar(currentElement_error);
    // error_dot
    auto currentElement_error_dot = (msg + ctr)->error_dot;
    outArray[ctr]["error_dot"] = factory.createScalar(currentElement_error_dot);
    // time_step
    auto currentElement_time_step = (msg + ctr)->time_step;
    outArray[ctr]["time_step"] = factory.createScalar(currentElement_time_step);
    // output
    auto currentElement_output = (msg + ctr)->output;
    outArray[ctr]["output"] = factory.createScalar(currentElement_output);
    }
    return std::move(outArray);
  } 
class CONTROL_MSGS_EXPORT ros2_control_msgs_SingleDOFState_message : public ROS2MsgElementInterfaceFactory {
  public:
    virtual ~ros2_control_msgs_SingleDOFState_message(){}
    virtual std::shared_ptr<MATLABPublisherInterface> generatePublisherInterface(ElementType /*type*/);
    virtual std::shared_ptr<MATLABSubscriberInterface> generateSubscriberInterface(ElementType /*type*/);
    virtual std::shared_ptr<void> generateCppMessage(ElementType /*type*/, const matlab::data::StructArray& /* arr */, MultiLibLoader /* loader */, std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* /*commonObjMap*/);
    virtual matlab::data::StructArray generateMLMessage(ElementType  /*type*/ ,void*  /* msg */, MultiLibLoader /* loader */ , std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* /*commonObjMap*/);
};  
  std::shared_ptr<MATLABPublisherInterface> 
          ros2_control_msgs_SingleDOFState_message::generatePublisherInterface(ElementType /*type*/){
    return std::make_shared<ROS2PublisherImpl<control_msgs::msg::SingleDOFState,ros2_control_msgs_msg_SingleDOFState_common>>();
  }
  std::shared_ptr<MATLABSubscriberInterface> 
         ros2_control_msgs_SingleDOFState_message::generateSubscriberInterface(ElementType /*type*/){
    return std::make_shared<ROS2SubscriberImpl<control_msgs::msg::SingleDOFState,ros2_control_msgs_msg_SingleDOFState_common>>();
  }
  std::shared_ptr<void> ros2_control_msgs_SingleDOFState_message::generateCppMessage(ElementType /*type*/, 
                                           const matlab::data::StructArray& arr,
                                           MultiLibLoader loader,
                                           std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* commonObjMap){
    auto msg = std::make_shared<control_msgs::msg::SingleDOFState>();
    ros2_control_msgs_msg_SingleDOFState_common commonObj;
    commonObj.mCommonObjMap = commonObjMap;
    commonObj.copy_from_struct(msg.get(), arr[0], loader);
    return msg;
  }
  matlab::data::StructArray ros2_control_msgs_SingleDOFState_message::generateMLMessage(ElementType  /*type*/ ,
                                                    void*  msg ,
                                                    MultiLibLoader  loader ,
                                                    std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>*  commonObjMap ){
    ros2_control_msgs_msg_SingleDOFState_common commonObj;	
    commonObj.mCommonObjMap = commonObjMap;	
    MDFactory_T factory;
    return commonObj.get_arr(factory, (control_msgs::msg::SingleDOFState*)msg, loader);			
 }
#include "class_loader/register_macro.hpp"
// Register the component with class_loader.
// This acts as a sort of entry point, allowing the component to be discoverable when its library
// is being loaded into a running process.
CLASS_LOADER_REGISTER_CLASS(ros2_control_msgs_msg_SingleDOFState_common, MATLABROS2MsgInterface<control_msgs::msg::SingleDOFState>)
CLASS_LOADER_REGISTER_CLASS(ros2_control_msgs_SingleDOFState_message, ROS2MsgElementInterfaceFactory)
#ifdef _MSC_VER
#pragma warning(pop)
#else
#pragma GCC diagnostic pop
#endif //_MSC_VER