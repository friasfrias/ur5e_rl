// Copyright 2020-2022 The MathWorks, Inc.
// Common copy functions for control_msgs/MultiDOFStateStamped
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
#include "control_msgs/msg/multi_dof_state_stamped.hpp"
#include "visibility_control.h"
#include "class_loader/multi_library_class_loader.hpp"
#include "ROS2PubSubTemplates.hpp"
class CONTROL_MSGS_EXPORT ros2_control_msgs_msg_MultiDOFStateStamped_common : public MATLABROS2MsgInterface<control_msgs::msg::MultiDOFStateStamped> {
  public:
    virtual ~ros2_control_msgs_msg_MultiDOFStateStamped_common(){}
    virtual void copy_from_struct(control_msgs::msg::MultiDOFStateStamped* msg, const matlab::data::Struct& arr, MultiLibLoader loader); 
    //----------------------------------------------------------------------------
    virtual MDArray_T get_arr(MDFactory_T& factory, const control_msgs::msg::MultiDOFStateStamped* msg, MultiLibLoader loader, size_t size = 1);
};
  void ros2_control_msgs_msg_MultiDOFStateStamped_common::copy_from_struct(control_msgs::msg::MultiDOFStateStamped* msg, const matlab::data::Struct& arr,
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
        //dof_states
        const matlab::data::StructArray dof_states_arr = arr["dof_states"];
        for (auto _dof_statesarr : dof_states_arr) {
        	control_msgs::msg::SingleDOFState _val;
        auto msgClassPtr_dof_states = getCommonObject<control_msgs::msg::SingleDOFState>("ros2_control_msgs_msg_SingleDOFState_common",loader);
        msgClassPtr_dof_states->copy_from_struct(&_val,_dof_statesarr,loader);
        	msg->dof_states.push_back(_val);
        }
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'dof_states' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'dof_states' is wrong type; expected a struct.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T ros2_control_msgs_msg_MultiDOFStateStamped_common::get_arr(MDFactory_T& factory, const control_msgs::msg::MultiDOFStateStamped* msg,
       MultiLibLoader loader, size_t size) {
    auto outArray = factory.createStructArray({size,1},{"MessageType","header","dof_states"});
    for(size_t ctr = 0; ctr < size; ctr++){
    outArray[ctr]["MessageType"] = factory.createCharArray("control_msgs/MultiDOFStateStamped");
    // header
    auto currentElement_header = (msg + ctr)->header;
    auto msgClassPtr_header = getCommonObject<std_msgs::msg::Header>("ros2_std_msgs_msg_Header_common",loader);
    outArray[ctr]["header"] = msgClassPtr_header->get_arr(factory, &currentElement_header, loader);
    // dof_states
    auto currentElement_dof_states = (msg + ctr)->dof_states;
    auto msgClassPtr_dof_states = getCommonObject<control_msgs::msg::SingleDOFState>("ros2_control_msgs_msg_SingleDOFState_common",loader);
    outArray[ctr]["dof_states"] = msgClassPtr_dof_states->get_arr(factory,&currentElement_dof_states[0],loader,currentElement_dof_states.size());
    }
    return std::move(outArray);
  } 
class CONTROL_MSGS_EXPORT ros2_control_msgs_MultiDOFStateStamped_message : public ROS2MsgElementInterfaceFactory {
  public:
    virtual ~ros2_control_msgs_MultiDOFStateStamped_message(){}
    virtual std::shared_ptr<MATLABPublisherInterface> generatePublisherInterface(ElementType /*type*/);
    virtual std::shared_ptr<MATLABSubscriberInterface> generateSubscriberInterface(ElementType /*type*/);
    virtual std::shared_ptr<void> generateCppMessage(ElementType /*type*/, const matlab::data::StructArray& /* arr */, MultiLibLoader /* loader */, std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* /*commonObjMap*/);
    virtual matlab::data::StructArray generateMLMessage(ElementType  /*type*/ ,void*  /* msg */, MultiLibLoader /* loader */ , std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* /*commonObjMap*/);
};  
  std::shared_ptr<MATLABPublisherInterface> 
          ros2_control_msgs_MultiDOFStateStamped_message::generatePublisherInterface(ElementType /*type*/){
    return std::make_shared<ROS2PublisherImpl<control_msgs::msg::MultiDOFStateStamped,ros2_control_msgs_msg_MultiDOFStateStamped_common>>();
  }
  std::shared_ptr<MATLABSubscriberInterface> 
         ros2_control_msgs_MultiDOFStateStamped_message::generateSubscriberInterface(ElementType /*type*/){
    return std::make_shared<ROS2SubscriberImpl<control_msgs::msg::MultiDOFStateStamped,ros2_control_msgs_msg_MultiDOFStateStamped_common>>();
  }
  std::shared_ptr<void> ros2_control_msgs_MultiDOFStateStamped_message::generateCppMessage(ElementType /*type*/, 
                                           const matlab::data::StructArray& arr,
                                           MultiLibLoader loader,
                                           std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* commonObjMap){
    auto msg = std::make_shared<control_msgs::msg::MultiDOFStateStamped>();
    ros2_control_msgs_msg_MultiDOFStateStamped_common commonObj;
    commonObj.mCommonObjMap = commonObjMap;
    commonObj.copy_from_struct(msg.get(), arr[0], loader);
    return msg;
  }
  matlab::data::StructArray ros2_control_msgs_MultiDOFStateStamped_message::generateMLMessage(ElementType  /*type*/ ,
                                                    void*  msg ,
                                                    MultiLibLoader  loader ,
                                                    std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>*  commonObjMap ){
    ros2_control_msgs_msg_MultiDOFStateStamped_common commonObj;	
    commonObj.mCommonObjMap = commonObjMap;	
    MDFactory_T factory;
    return commonObj.get_arr(factory, (control_msgs::msg::MultiDOFStateStamped*)msg, loader);			
 }
#include "class_loader/register_macro.hpp"
// Register the component with class_loader.
// This acts as a sort of entry point, allowing the component to be discoverable when its library
// is being loaded into a running process.
CLASS_LOADER_REGISTER_CLASS(ros2_control_msgs_msg_MultiDOFStateStamped_common, MATLABROS2MsgInterface<control_msgs::msg::MultiDOFStateStamped>)
CLASS_LOADER_REGISTER_CLASS(ros2_control_msgs_MultiDOFStateStamped_message, ROS2MsgElementInterfaceFactory)
#ifdef _MSC_VER
#pragma warning(pop)
#else
#pragma GCC diagnostic pop
#endif //_MSC_VER