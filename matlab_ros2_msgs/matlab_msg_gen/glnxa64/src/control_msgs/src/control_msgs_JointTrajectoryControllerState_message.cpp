// Copyright 2020-2022 The MathWorks, Inc.
// Common copy functions for control_msgs/JointTrajectoryControllerState
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
#include "control_msgs/msg/joint_trajectory_controller_state.hpp"
#include "visibility_control.h"
#include "class_loader/multi_library_class_loader.hpp"
#include "ROS2PubSubTemplates.hpp"
class CONTROL_MSGS_EXPORT ros2_control_msgs_msg_JointTrajectoryControllerState_common : public MATLABROS2MsgInterface<control_msgs::msg::JointTrajectoryControllerState> {
  public:
    virtual ~ros2_control_msgs_msg_JointTrajectoryControllerState_common(){}
    virtual void copy_from_struct(control_msgs::msg::JointTrajectoryControllerState* msg, const matlab::data::Struct& arr, MultiLibLoader loader); 
    //----------------------------------------------------------------------------
    virtual MDArray_T get_arr(MDFactory_T& factory, const control_msgs::msg::JointTrajectoryControllerState* msg, MultiLibLoader loader, size_t size = 1);
};
  void ros2_control_msgs_msg_JointTrajectoryControllerState_common::copy_from_struct(control_msgs::msg::JointTrajectoryControllerState* msg, const matlab::data::Struct& arr,
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
        //joint_names
        const matlab::data::CellArray joint_names_cellarr = arr["joint_names"];
        size_t nelem = joint_names_cellarr.getNumberOfElements();
        for (size_t idx=0; idx < nelem; ++idx){
        	const matlab::data::CharArray joint_names_arr = joint_names_cellarr[idx];
        	msg->joint_names.push_back(joint_names_arr.toAscii());
        }
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'joint_names' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'joint_names' is wrong type; expected a string.");
    }
    try {
        //reference
        const matlab::data::StructArray reference_arr = arr["reference"];
        auto msgClassPtr_reference = getCommonObject<trajectory_msgs::msg::JointTrajectoryPoint>("ros2_trajectory_msgs_msg_JointTrajectoryPoint_common",loader);
        msgClassPtr_reference->copy_from_struct(&msg->reference,reference_arr[0],loader);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'reference' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'reference' is wrong type; expected a struct.");
    }
    try {
        //feedback
        const matlab::data::StructArray feedback_arr = arr["feedback"];
        auto msgClassPtr_feedback = getCommonObject<trajectory_msgs::msg::JointTrajectoryPoint>("ros2_trajectory_msgs_msg_JointTrajectoryPoint_common",loader);
        msgClassPtr_feedback->copy_from_struct(&msg->feedback,feedback_arr[0],loader);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'feedback' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'feedback' is wrong type; expected a struct.");
    }
    try {
        //error
        const matlab::data::StructArray error_arr = arr["error"];
        auto msgClassPtr_error = getCommonObject<trajectory_msgs::msg::JointTrajectoryPoint>("ros2_trajectory_msgs_msg_JointTrajectoryPoint_common",loader);
        msgClassPtr_error->copy_from_struct(&msg->error,error_arr[0],loader);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'error' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'error' is wrong type; expected a struct.");
    }
    try {
        //output
        const matlab::data::StructArray output_arr = arr["output"];
        auto msgClassPtr_output = getCommonObject<trajectory_msgs::msg::JointTrajectoryPoint>("ros2_trajectory_msgs_msg_JointTrajectoryPoint_common",loader);
        msgClassPtr_output->copy_from_struct(&msg->output,output_arr[0],loader);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'output' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'output' is wrong type; expected a struct.");
    }
    try {
        //desired
        const matlab::data::StructArray desired_arr = arr["desired"];
        auto msgClassPtr_desired = getCommonObject<trajectory_msgs::msg::JointTrajectoryPoint>("ros2_trajectory_msgs_msg_JointTrajectoryPoint_common",loader);
        msgClassPtr_desired->copy_from_struct(&msg->desired,desired_arr[0],loader);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'desired' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'desired' is wrong type; expected a struct.");
    }
    try {
        //actual
        const matlab::data::StructArray actual_arr = arr["actual"];
        auto msgClassPtr_actual = getCommonObject<trajectory_msgs::msg::JointTrajectoryPoint>("ros2_trajectory_msgs_msg_JointTrajectoryPoint_common",loader);
        msgClassPtr_actual->copy_from_struct(&msg->actual,actual_arr[0],loader);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'actual' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'actual' is wrong type; expected a struct.");
    }
    try {
        //multi_dof_joint_names
        const matlab::data::CellArray multi_dof_joint_names_cellarr = arr["multi_dof_joint_names"];
        size_t nelem = multi_dof_joint_names_cellarr.getNumberOfElements();
        for (size_t idx=0; idx < nelem; ++idx){
        	const matlab::data::CharArray multi_dof_joint_names_arr = multi_dof_joint_names_cellarr[idx];
        	msg->multi_dof_joint_names.push_back(multi_dof_joint_names_arr.toAscii());
        }
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'multi_dof_joint_names' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'multi_dof_joint_names' is wrong type; expected a string.");
    }
    try {
        //multi_dof_reference
        const matlab::data::StructArray multi_dof_reference_arr = arr["multi_dof_reference"];
        auto msgClassPtr_multi_dof_reference = getCommonObject<trajectory_msgs::msg::MultiDOFJointTrajectoryPoint>("ros2_trajectory_msgs_msg_MultiDOFJointTrajectoryPoint_common",loader);
        msgClassPtr_multi_dof_reference->copy_from_struct(&msg->multi_dof_reference,multi_dof_reference_arr[0],loader);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'multi_dof_reference' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'multi_dof_reference' is wrong type; expected a struct.");
    }
    try {
        //multi_dof_feedback
        const matlab::data::StructArray multi_dof_feedback_arr = arr["multi_dof_feedback"];
        auto msgClassPtr_multi_dof_feedback = getCommonObject<trajectory_msgs::msg::MultiDOFJointTrajectoryPoint>("ros2_trajectory_msgs_msg_MultiDOFJointTrajectoryPoint_common",loader);
        msgClassPtr_multi_dof_feedback->copy_from_struct(&msg->multi_dof_feedback,multi_dof_feedback_arr[0],loader);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'multi_dof_feedback' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'multi_dof_feedback' is wrong type; expected a struct.");
    }
    try {
        //multi_dof_error
        const matlab::data::StructArray multi_dof_error_arr = arr["multi_dof_error"];
        auto msgClassPtr_multi_dof_error = getCommonObject<trajectory_msgs::msg::MultiDOFJointTrajectoryPoint>("ros2_trajectory_msgs_msg_MultiDOFJointTrajectoryPoint_common",loader);
        msgClassPtr_multi_dof_error->copy_from_struct(&msg->multi_dof_error,multi_dof_error_arr[0],loader);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'multi_dof_error' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'multi_dof_error' is wrong type; expected a struct.");
    }
    try {
        //multi_dof_output
        const matlab::data::StructArray multi_dof_output_arr = arr["multi_dof_output"];
        auto msgClassPtr_multi_dof_output = getCommonObject<trajectory_msgs::msg::MultiDOFJointTrajectoryPoint>("ros2_trajectory_msgs_msg_MultiDOFJointTrajectoryPoint_common",loader);
        msgClassPtr_multi_dof_output->copy_from_struct(&msg->multi_dof_output,multi_dof_output_arr[0],loader);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'multi_dof_output' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'multi_dof_output' is wrong type; expected a struct.");
    }
    try {
        //multi_dof_desired
        const matlab::data::StructArray multi_dof_desired_arr = arr["multi_dof_desired"];
        auto msgClassPtr_multi_dof_desired = getCommonObject<trajectory_msgs::msg::MultiDOFJointTrajectoryPoint>("ros2_trajectory_msgs_msg_MultiDOFJointTrajectoryPoint_common",loader);
        msgClassPtr_multi_dof_desired->copy_from_struct(&msg->multi_dof_desired,multi_dof_desired_arr[0],loader);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'multi_dof_desired' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'multi_dof_desired' is wrong type; expected a struct.");
    }
    try {
        //multi_dof_actual
        const matlab::data::StructArray multi_dof_actual_arr = arr["multi_dof_actual"];
        auto msgClassPtr_multi_dof_actual = getCommonObject<trajectory_msgs::msg::MultiDOFJointTrajectoryPoint>("ros2_trajectory_msgs_msg_MultiDOFJointTrajectoryPoint_common",loader);
        msgClassPtr_multi_dof_actual->copy_from_struct(&msg->multi_dof_actual,multi_dof_actual_arr[0],loader);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'multi_dof_actual' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'multi_dof_actual' is wrong type; expected a struct.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T ros2_control_msgs_msg_JointTrajectoryControllerState_common::get_arr(MDFactory_T& factory, const control_msgs::msg::JointTrajectoryControllerState* msg,
       MultiLibLoader loader, size_t size) {
    auto outArray = factory.createStructArray({size,1},{"MessageType","header","joint_names","reference","feedback","error","output","desired","actual","multi_dof_joint_names","multi_dof_reference","multi_dof_feedback","multi_dof_error","multi_dof_output","multi_dof_desired","multi_dof_actual"});
    for(size_t ctr = 0; ctr < size; ctr++){
    outArray[ctr]["MessageType"] = factory.createCharArray("control_msgs/JointTrajectoryControllerState");
    // header
    auto currentElement_header = (msg + ctr)->header;
    auto msgClassPtr_header = getCommonObject<std_msgs::msg::Header>("ros2_std_msgs_msg_Header_common",loader);
    outArray[ctr]["header"] = msgClassPtr_header->get_arr(factory, &currentElement_header, loader);
    // joint_names
    auto currentElement_joint_names = (msg + ctr)->joint_names;
    auto joint_namesoutCell = factory.createCellArray({currentElement_joint_names.size(),1});
    for(size_t idxin = 0; idxin < currentElement_joint_names.size(); ++ idxin){
    	joint_namesoutCell[idxin] = factory.createCharArray(currentElement_joint_names[idxin]);
    }
    outArray[ctr]["joint_names"] = joint_namesoutCell;
    // reference
    auto currentElement_reference = (msg + ctr)->reference;
    auto msgClassPtr_reference = getCommonObject<trajectory_msgs::msg::JointTrajectoryPoint>("ros2_trajectory_msgs_msg_JointTrajectoryPoint_common",loader);
    outArray[ctr]["reference"] = msgClassPtr_reference->get_arr(factory, &currentElement_reference, loader);
    // feedback
    auto currentElement_feedback = (msg + ctr)->feedback;
    auto msgClassPtr_feedback = getCommonObject<trajectory_msgs::msg::JointTrajectoryPoint>("ros2_trajectory_msgs_msg_JointTrajectoryPoint_common",loader);
    outArray[ctr]["feedback"] = msgClassPtr_feedback->get_arr(factory, &currentElement_feedback, loader);
    // error
    auto currentElement_error = (msg + ctr)->error;
    auto msgClassPtr_error = getCommonObject<trajectory_msgs::msg::JointTrajectoryPoint>("ros2_trajectory_msgs_msg_JointTrajectoryPoint_common",loader);
    outArray[ctr]["error"] = msgClassPtr_error->get_arr(factory, &currentElement_error, loader);
    // output
    auto currentElement_output = (msg + ctr)->output;
    auto msgClassPtr_output = getCommonObject<trajectory_msgs::msg::JointTrajectoryPoint>("ros2_trajectory_msgs_msg_JointTrajectoryPoint_common",loader);
    outArray[ctr]["output"] = msgClassPtr_output->get_arr(factory, &currentElement_output, loader);
    // desired
    auto currentElement_desired = (msg + ctr)->desired;
    auto msgClassPtr_desired = getCommonObject<trajectory_msgs::msg::JointTrajectoryPoint>("ros2_trajectory_msgs_msg_JointTrajectoryPoint_common",loader);
    outArray[ctr]["desired"] = msgClassPtr_desired->get_arr(factory, &currentElement_desired, loader);
    // actual
    auto currentElement_actual = (msg + ctr)->actual;
    auto msgClassPtr_actual = getCommonObject<trajectory_msgs::msg::JointTrajectoryPoint>("ros2_trajectory_msgs_msg_JointTrajectoryPoint_common",loader);
    outArray[ctr]["actual"] = msgClassPtr_actual->get_arr(factory, &currentElement_actual, loader);
    // multi_dof_joint_names
    auto currentElement_multi_dof_joint_names = (msg + ctr)->multi_dof_joint_names;
    auto multi_dof_joint_namesoutCell = factory.createCellArray({currentElement_multi_dof_joint_names.size(),1});
    for(size_t idxin = 0; idxin < currentElement_multi_dof_joint_names.size(); ++ idxin){
    	multi_dof_joint_namesoutCell[idxin] = factory.createCharArray(currentElement_multi_dof_joint_names[idxin]);
    }
    outArray[ctr]["multi_dof_joint_names"] = multi_dof_joint_namesoutCell;
    // multi_dof_reference
    auto currentElement_multi_dof_reference = (msg + ctr)->multi_dof_reference;
    auto msgClassPtr_multi_dof_reference = getCommonObject<trajectory_msgs::msg::MultiDOFJointTrajectoryPoint>("ros2_trajectory_msgs_msg_MultiDOFJointTrajectoryPoint_common",loader);
    outArray[ctr]["multi_dof_reference"] = msgClassPtr_multi_dof_reference->get_arr(factory, &currentElement_multi_dof_reference, loader);
    // multi_dof_feedback
    auto currentElement_multi_dof_feedback = (msg + ctr)->multi_dof_feedback;
    auto msgClassPtr_multi_dof_feedback = getCommonObject<trajectory_msgs::msg::MultiDOFJointTrajectoryPoint>("ros2_trajectory_msgs_msg_MultiDOFJointTrajectoryPoint_common",loader);
    outArray[ctr]["multi_dof_feedback"] = msgClassPtr_multi_dof_feedback->get_arr(factory, &currentElement_multi_dof_feedback, loader);
    // multi_dof_error
    auto currentElement_multi_dof_error = (msg + ctr)->multi_dof_error;
    auto msgClassPtr_multi_dof_error = getCommonObject<trajectory_msgs::msg::MultiDOFJointTrajectoryPoint>("ros2_trajectory_msgs_msg_MultiDOFJointTrajectoryPoint_common",loader);
    outArray[ctr]["multi_dof_error"] = msgClassPtr_multi_dof_error->get_arr(factory, &currentElement_multi_dof_error, loader);
    // multi_dof_output
    auto currentElement_multi_dof_output = (msg + ctr)->multi_dof_output;
    auto msgClassPtr_multi_dof_output = getCommonObject<trajectory_msgs::msg::MultiDOFJointTrajectoryPoint>("ros2_trajectory_msgs_msg_MultiDOFJointTrajectoryPoint_common",loader);
    outArray[ctr]["multi_dof_output"] = msgClassPtr_multi_dof_output->get_arr(factory, &currentElement_multi_dof_output, loader);
    // multi_dof_desired
    auto currentElement_multi_dof_desired = (msg + ctr)->multi_dof_desired;
    auto msgClassPtr_multi_dof_desired = getCommonObject<trajectory_msgs::msg::MultiDOFJointTrajectoryPoint>("ros2_trajectory_msgs_msg_MultiDOFJointTrajectoryPoint_common",loader);
    outArray[ctr]["multi_dof_desired"] = msgClassPtr_multi_dof_desired->get_arr(factory, &currentElement_multi_dof_desired, loader);
    // multi_dof_actual
    auto currentElement_multi_dof_actual = (msg + ctr)->multi_dof_actual;
    auto msgClassPtr_multi_dof_actual = getCommonObject<trajectory_msgs::msg::MultiDOFJointTrajectoryPoint>("ros2_trajectory_msgs_msg_MultiDOFJointTrajectoryPoint_common",loader);
    outArray[ctr]["multi_dof_actual"] = msgClassPtr_multi_dof_actual->get_arr(factory, &currentElement_multi_dof_actual, loader);
    }
    return std::move(outArray);
  } 
class CONTROL_MSGS_EXPORT ros2_control_msgs_JointTrajectoryControllerState_message : public ROS2MsgElementInterfaceFactory {
  public:
    virtual ~ros2_control_msgs_JointTrajectoryControllerState_message(){}
    virtual std::shared_ptr<MATLABPublisherInterface> generatePublisherInterface(ElementType /*type*/);
    virtual std::shared_ptr<MATLABSubscriberInterface> generateSubscriberInterface(ElementType /*type*/);
    virtual std::shared_ptr<void> generateCppMessage(ElementType /*type*/, const matlab::data::StructArray& /* arr */, MultiLibLoader /* loader */, std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* /*commonObjMap*/);
    virtual matlab::data::StructArray generateMLMessage(ElementType  /*type*/ ,void*  /* msg */, MultiLibLoader /* loader */ , std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* /*commonObjMap*/);
};  
  std::shared_ptr<MATLABPublisherInterface> 
          ros2_control_msgs_JointTrajectoryControllerState_message::generatePublisherInterface(ElementType /*type*/){
    return std::make_shared<ROS2PublisherImpl<control_msgs::msg::JointTrajectoryControllerState,ros2_control_msgs_msg_JointTrajectoryControllerState_common>>();
  }
  std::shared_ptr<MATLABSubscriberInterface> 
         ros2_control_msgs_JointTrajectoryControllerState_message::generateSubscriberInterface(ElementType /*type*/){
    return std::make_shared<ROS2SubscriberImpl<control_msgs::msg::JointTrajectoryControllerState,ros2_control_msgs_msg_JointTrajectoryControllerState_common>>();
  }
  std::shared_ptr<void> ros2_control_msgs_JointTrajectoryControllerState_message::generateCppMessage(ElementType /*type*/, 
                                           const matlab::data::StructArray& arr,
                                           MultiLibLoader loader,
                                           std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* commonObjMap){
    auto msg = std::make_shared<control_msgs::msg::JointTrajectoryControllerState>();
    ros2_control_msgs_msg_JointTrajectoryControllerState_common commonObj;
    commonObj.mCommonObjMap = commonObjMap;
    commonObj.copy_from_struct(msg.get(), arr[0], loader);
    return msg;
  }
  matlab::data::StructArray ros2_control_msgs_JointTrajectoryControllerState_message::generateMLMessage(ElementType  /*type*/ ,
                                                    void*  msg ,
                                                    MultiLibLoader  loader ,
                                                    std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>*  commonObjMap ){
    ros2_control_msgs_msg_JointTrajectoryControllerState_common commonObj;	
    commonObj.mCommonObjMap = commonObjMap;	
    MDFactory_T factory;
    return commonObj.get_arr(factory, (control_msgs::msg::JointTrajectoryControllerState*)msg, loader);			
 }
#include "class_loader/register_macro.hpp"
// Register the component with class_loader.
// This acts as a sort of entry point, allowing the component to be discoverable when its library
// is being loaded into a running process.
CLASS_LOADER_REGISTER_CLASS(ros2_control_msgs_msg_JointTrajectoryControllerState_common, MATLABROS2MsgInterface<control_msgs::msg::JointTrajectoryControllerState>)
CLASS_LOADER_REGISTER_CLASS(ros2_control_msgs_JointTrajectoryControllerState_message, ROS2MsgElementInterfaceFactory)
#ifdef _MSC_VER
#pragma warning(pop)
#else
#pragma GCC diagnostic pop
#endif //_MSC_VER