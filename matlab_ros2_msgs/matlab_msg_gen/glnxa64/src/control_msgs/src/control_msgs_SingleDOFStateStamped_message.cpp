// Copyright 2020-2022 The MathWorks, Inc.
// Common copy functions for control_msgs/SingleDOFStateStamped
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
#include "control_msgs/msg/single_dof_state_stamped.hpp"
#include "visibility_control.h"
#include "class_loader/multi_library_class_loader.hpp"
#include "ROS2PubSubTemplates.hpp"
class CONTROL_MSGS_EXPORT ros2_control_msgs_msg_SingleDOFStateStamped_common : public MATLABROS2MsgInterface<control_msgs::msg::SingleDOFStateStamped> {
  public:
    virtual ~ros2_control_msgs_msg_SingleDOFStateStamped_common(){}
    virtual void copy_from_struct(control_msgs::msg::SingleDOFStateStamped* msg, const matlab::data::Struct& arr, MultiLibLoader loader); 
    //----------------------------------------------------------------------------
    virtual MDArray_T get_arr(MDFactory_T& factory, const control_msgs::msg::SingleDOFStateStamped* msg, MultiLibLoader loader, size_t size = 1);
};
  void ros2_control_msgs_msg_SingleDOFStateStamped_common::copy_from_struct(control_msgs::msg::SingleDOFStateStamped* msg, const matlab::data::Struct& arr,
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
        //dof_state
        const matlab::data::StructArray dof_state_arr = arr["dof_state"];
        auto msgClassPtr_dof_state = getCommonObject<control_msgs::msg::SingleDOFState>("ros2_control_msgs_msg_SingleDOFState_common",loader);
        msgClassPtr_dof_state->copy_from_struct(&msg->dof_state,dof_state_arr[0],loader);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'dof_state' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'dof_state' is wrong type; expected a struct.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T ros2_control_msgs_msg_SingleDOFStateStamped_common::get_arr(MDFactory_T& factory, const control_msgs::msg::SingleDOFStateStamped* msg,
       MultiLibLoader loader, size_t size) {
    auto outArray = factory.createStructArray({size,1},{"MessageType","header","dof_state"});
    for(size_t ctr = 0; ctr < size; ctr++){
    outArray[ctr]["MessageType"] = factory.createCharArray("control_msgs/SingleDOFStateStamped");
    // header
    auto currentElement_header = (msg + ctr)->header;
    auto msgClassPtr_header = getCommonObject<std_msgs::msg::Header>("ros2_std_msgs_msg_Header_common",loader);
    outArray[ctr]["header"] = msgClassPtr_header->get_arr(factory, &currentElement_header, loader);
    // dof_state
    auto currentElement_dof_state = (msg + ctr)->dof_state;
    auto msgClassPtr_dof_state = getCommonObject<control_msgs::msg::SingleDOFState>("ros2_control_msgs_msg_SingleDOFState_common",loader);
    outArray[ctr]["dof_state"] = msgClassPtr_dof_state->get_arr(factory, &currentElement_dof_state, loader);
    }
    return std::move(outArray);
  } 
class CONTROL_MSGS_EXPORT ros2_control_msgs_SingleDOFStateStamped_message : public ROS2MsgElementInterfaceFactory {
  public:
    virtual ~ros2_control_msgs_SingleDOFStateStamped_message(){}
    virtual std::shared_ptr<MATLABPublisherInterface> generatePublisherInterface(ElementType /*type*/);
    virtual std::shared_ptr<MATLABSubscriberInterface> generateSubscriberInterface(ElementType /*type*/);
    virtual std::shared_ptr<void> generateCppMessage(ElementType /*type*/, const matlab::data::StructArray& /* arr */, MultiLibLoader /* loader */, std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* /*commonObjMap*/);
    virtual matlab::data::StructArray generateMLMessage(ElementType  /*type*/ ,void*  /* msg */, MultiLibLoader /* loader */ , std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* /*commonObjMap*/);
};  
  std::shared_ptr<MATLABPublisherInterface> 
          ros2_control_msgs_SingleDOFStateStamped_message::generatePublisherInterface(ElementType /*type*/){
    return std::make_shared<ROS2PublisherImpl<control_msgs::msg::SingleDOFStateStamped,ros2_control_msgs_msg_SingleDOFStateStamped_common>>();
  }
  std::shared_ptr<MATLABSubscriberInterface> 
         ros2_control_msgs_SingleDOFStateStamped_message::generateSubscriberInterface(ElementType /*type*/){
    return std::make_shared<ROS2SubscriberImpl<control_msgs::msg::SingleDOFStateStamped,ros2_control_msgs_msg_SingleDOFStateStamped_common>>();
  }
  std::shared_ptr<void> ros2_control_msgs_SingleDOFStateStamped_message::generateCppMessage(ElementType /*type*/, 
                                           const matlab::data::StructArray& arr,
                                           MultiLibLoader loader,
                                           std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* commonObjMap){
    auto msg = std::make_shared<control_msgs::msg::SingleDOFStateStamped>();
    ros2_control_msgs_msg_SingleDOFStateStamped_common commonObj;
    commonObj.mCommonObjMap = commonObjMap;
    commonObj.copy_from_struct(msg.get(), arr[0], loader);
    return msg;
  }
  matlab::data::StructArray ros2_control_msgs_SingleDOFStateStamped_message::generateMLMessage(ElementType  /*type*/ ,
                                                    void*  msg ,
                                                    MultiLibLoader  loader ,
                                                    std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>*  commonObjMap ){
    ros2_control_msgs_msg_SingleDOFStateStamped_common commonObj;	
    commonObj.mCommonObjMap = commonObjMap;	
    MDFactory_T factory;
    return commonObj.get_arr(factory, (control_msgs::msg::SingleDOFStateStamped*)msg, loader);			
 }
#include "class_loader/register_macro.hpp"
// Register the component with class_loader.
// This acts as a sort of entry point, allowing the component to be discoverable when its library
// is being loaded into a running process.
CLASS_LOADER_REGISTER_CLASS(ros2_control_msgs_msg_SingleDOFStateStamped_common, MATLABROS2MsgInterface<control_msgs::msg::SingleDOFStateStamped>)
CLASS_LOADER_REGISTER_CLASS(ros2_control_msgs_SingleDOFStateStamped_message, ROS2MsgElementInterfaceFactory)
#ifdef _MSC_VER
#pragma warning(pop)
#else
#pragma GCC diagnostic pop
#endif //_MSC_VER