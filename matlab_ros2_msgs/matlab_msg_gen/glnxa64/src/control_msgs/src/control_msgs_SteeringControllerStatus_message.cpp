// Copyright 2020-2022 The MathWorks, Inc.
// Common copy functions for control_msgs/SteeringControllerStatus
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
#include "control_msgs/msg/steering_controller_status.hpp"
#include "visibility_control.h"
#include "class_loader/multi_library_class_loader.hpp"
#include "ROS2PubSubTemplates.hpp"
class CONTROL_MSGS_EXPORT ros2_control_msgs_msg_SteeringControllerStatus_common : public MATLABROS2MsgInterface<control_msgs::msg::SteeringControllerStatus> {
  public:
    virtual ~ros2_control_msgs_msg_SteeringControllerStatus_common(){}
    virtual void copy_from_struct(control_msgs::msg::SteeringControllerStatus* msg, const matlab::data::Struct& arr, MultiLibLoader loader); 
    //----------------------------------------------------------------------------
    virtual MDArray_T get_arr(MDFactory_T& factory, const control_msgs::msg::SteeringControllerStatus* msg, MultiLibLoader loader, size_t size = 1);
};
  void ros2_control_msgs_msg_SteeringControllerStatus_common::copy_from_struct(control_msgs::msg::SteeringControllerStatus* msg, const matlab::data::Struct& arr,
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
        //traction_wheels_position
        const matlab::data::TypedArray<double> traction_wheels_position_arr = arr["traction_wheels_position"];
        size_t nelem = traction_wheels_position_arr.getNumberOfElements();
        	msg->traction_wheels_position.resize(nelem);
        	std::copy(traction_wheels_position_arr.begin(), traction_wheels_position_arr.begin()+nelem, msg->traction_wheels_position.begin());
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'traction_wheels_position' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'traction_wheels_position' is wrong type; expected a double.");
    }
    try {
        //traction_wheels_velocity
        const matlab::data::TypedArray<double> traction_wheels_velocity_arr = arr["traction_wheels_velocity"];
        size_t nelem = traction_wheels_velocity_arr.getNumberOfElements();
        	msg->traction_wheels_velocity.resize(nelem);
        	std::copy(traction_wheels_velocity_arr.begin(), traction_wheels_velocity_arr.begin()+nelem, msg->traction_wheels_velocity.begin());
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'traction_wheels_velocity' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'traction_wheels_velocity' is wrong type; expected a double.");
    }
    try {
        //steer_positions
        const matlab::data::TypedArray<double> steer_positions_arr = arr["steer_positions"];
        size_t nelem = steer_positions_arr.getNumberOfElements();
        	msg->steer_positions.resize(nelem);
        	std::copy(steer_positions_arr.begin(), steer_positions_arr.begin()+nelem, msg->steer_positions.begin());
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'steer_positions' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'steer_positions' is wrong type; expected a double.");
    }
    try {
        //linear_velocity_command
        const matlab::data::TypedArray<double> linear_velocity_command_arr = arr["linear_velocity_command"];
        size_t nelem = linear_velocity_command_arr.getNumberOfElements();
        	msg->linear_velocity_command.resize(nelem);
        	std::copy(linear_velocity_command_arr.begin(), linear_velocity_command_arr.begin()+nelem, msg->linear_velocity_command.begin());
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'linear_velocity_command' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'linear_velocity_command' is wrong type; expected a double.");
    }
    try {
        //steering_angle_command
        const matlab::data::TypedArray<double> steering_angle_command_arr = arr["steering_angle_command"];
        size_t nelem = steering_angle_command_arr.getNumberOfElements();
        	msg->steering_angle_command.resize(nelem);
        	std::copy(steering_angle_command_arr.begin(), steering_angle_command_arr.begin()+nelem, msg->steering_angle_command.begin());
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'steering_angle_command' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'steering_angle_command' is wrong type; expected a double.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T ros2_control_msgs_msg_SteeringControllerStatus_common::get_arr(MDFactory_T& factory, const control_msgs::msg::SteeringControllerStatus* msg,
       MultiLibLoader loader, size_t size) {
    auto outArray = factory.createStructArray({size,1},{"MessageType","header","traction_wheels_position","traction_wheels_velocity","steer_positions","linear_velocity_command","steering_angle_command"});
    for(size_t ctr = 0; ctr < size; ctr++){
    outArray[ctr]["MessageType"] = factory.createCharArray("control_msgs/SteeringControllerStatus");
    // header
    auto currentElement_header = (msg + ctr)->header;
    auto msgClassPtr_header = getCommonObject<std_msgs::msg::Header>("ros2_std_msgs_msg_Header_common",loader);
    outArray[ctr]["header"] = msgClassPtr_header->get_arr(factory, &currentElement_header, loader);
    // traction_wheels_position
    auto currentElement_traction_wheels_position = (msg + ctr)->traction_wheels_position;
    outArray[ctr]["traction_wheels_position"] = factory.createArray<control_msgs::msg::SteeringControllerStatus::_traction_wheels_position_type::const_iterator, double>({currentElement_traction_wheels_position.size(), 1}, currentElement_traction_wheels_position.begin(), currentElement_traction_wheels_position.end());
    // traction_wheels_velocity
    auto currentElement_traction_wheels_velocity = (msg + ctr)->traction_wheels_velocity;
    outArray[ctr]["traction_wheels_velocity"] = factory.createArray<control_msgs::msg::SteeringControllerStatus::_traction_wheels_velocity_type::const_iterator, double>({currentElement_traction_wheels_velocity.size(), 1}, currentElement_traction_wheels_velocity.begin(), currentElement_traction_wheels_velocity.end());
    // steer_positions
    auto currentElement_steer_positions = (msg + ctr)->steer_positions;
    outArray[ctr]["steer_positions"] = factory.createArray<control_msgs::msg::SteeringControllerStatus::_steer_positions_type::const_iterator, double>({currentElement_steer_positions.size(), 1}, currentElement_steer_positions.begin(), currentElement_steer_positions.end());
    // linear_velocity_command
    auto currentElement_linear_velocity_command = (msg + ctr)->linear_velocity_command;
    outArray[ctr]["linear_velocity_command"] = factory.createArray<control_msgs::msg::SteeringControllerStatus::_linear_velocity_command_type::const_iterator, double>({currentElement_linear_velocity_command.size(), 1}, currentElement_linear_velocity_command.begin(), currentElement_linear_velocity_command.end());
    // steering_angle_command
    auto currentElement_steering_angle_command = (msg + ctr)->steering_angle_command;
    outArray[ctr]["steering_angle_command"] = factory.createArray<control_msgs::msg::SteeringControllerStatus::_steering_angle_command_type::const_iterator, double>({currentElement_steering_angle_command.size(), 1}, currentElement_steering_angle_command.begin(), currentElement_steering_angle_command.end());
    }
    return std::move(outArray);
  } 
class CONTROL_MSGS_EXPORT ros2_control_msgs_SteeringControllerStatus_message : public ROS2MsgElementInterfaceFactory {
  public:
    virtual ~ros2_control_msgs_SteeringControllerStatus_message(){}
    virtual std::shared_ptr<MATLABPublisherInterface> generatePublisherInterface(ElementType /*type*/);
    virtual std::shared_ptr<MATLABSubscriberInterface> generateSubscriberInterface(ElementType /*type*/);
    virtual std::shared_ptr<void> generateCppMessage(ElementType /*type*/, const matlab::data::StructArray& /* arr */, MultiLibLoader /* loader */, std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* /*commonObjMap*/);
    virtual matlab::data::StructArray generateMLMessage(ElementType  /*type*/ ,void*  /* msg */, MultiLibLoader /* loader */ , std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* /*commonObjMap*/);
};  
  std::shared_ptr<MATLABPublisherInterface> 
          ros2_control_msgs_SteeringControllerStatus_message::generatePublisherInterface(ElementType /*type*/){
    return std::make_shared<ROS2PublisherImpl<control_msgs::msg::SteeringControllerStatus,ros2_control_msgs_msg_SteeringControllerStatus_common>>();
  }
  std::shared_ptr<MATLABSubscriberInterface> 
         ros2_control_msgs_SteeringControllerStatus_message::generateSubscriberInterface(ElementType /*type*/){
    return std::make_shared<ROS2SubscriberImpl<control_msgs::msg::SteeringControllerStatus,ros2_control_msgs_msg_SteeringControllerStatus_common>>();
  }
  std::shared_ptr<void> ros2_control_msgs_SteeringControllerStatus_message::generateCppMessage(ElementType /*type*/, 
                                           const matlab::data::StructArray& arr,
                                           MultiLibLoader loader,
                                           std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* commonObjMap){
    auto msg = std::make_shared<control_msgs::msg::SteeringControllerStatus>();
    ros2_control_msgs_msg_SteeringControllerStatus_common commonObj;
    commonObj.mCommonObjMap = commonObjMap;
    commonObj.copy_from_struct(msg.get(), arr[0], loader);
    return msg;
  }
  matlab::data::StructArray ros2_control_msgs_SteeringControllerStatus_message::generateMLMessage(ElementType  /*type*/ ,
                                                    void*  msg ,
                                                    MultiLibLoader  loader ,
                                                    std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>*  commonObjMap ){
    ros2_control_msgs_msg_SteeringControllerStatus_common commonObj;	
    commonObj.mCommonObjMap = commonObjMap;	
    MDFactory_T factory;
    return commonObj.get_arr(factory, (control_msgs::msg::SteeringControllerStatus*)msg, loader);			
 }
#include "class_loader/register_macro.hpp"
// Register the component with class_loader.
// This acts as a sort of entry point, allowing the component to be discoverable when its library
// is being loaded into a running process.
CLASS_LOADER_REGISTER_CLASS(ros2_control_msgs_msg_SteeringControllerStatus_common, MATLABROS2MsgInterface<control_msgs::msg::SteeringControllerStatus>)
CLASS_LOADER_REGISTER_CLASS(ros2_control_msgs_SteeringControllerStatus_message, ROS2MsgElementInterfaceFactory)
#ifdef _MSC_VER
#pragma warning(pop)
#else
#pragma GCC diagnostic pop
#endif //_MSC_VER