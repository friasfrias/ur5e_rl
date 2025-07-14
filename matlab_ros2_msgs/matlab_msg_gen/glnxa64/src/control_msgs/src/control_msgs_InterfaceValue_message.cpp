// Copyright 2020-2022 The MathWorks, Inc.
// Common copy functions for control_msgs/InterfaceValue
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
#include "control_msgs/msg/interface_value.hpp"
#include "visibility_control.h"
#include "class_loader/multi_library_class_loader.hpp"
#include "ROS2PubSubTemplates.hpp"
class CONTROL_MSGS_EXPORT ros2_control_msgs_msg_InterfaceValue_common : public MATLABROS2MsgInterface<control_msgs::msg::InterfaceValue> {
  public:
    virtual ~ros2_control_msgs_msg_InterfaceValue_common(){}
    virtual void copy_from_struct(control_msgs::msg::InterfaceValue* msg, const matlab::data::Struct& arr, MultiLibLoader loader); 
    //----------------------------------------------------------------------------
    virtual MDArray_T get_arr(MDFactory_T& factory, const control_msgs::msg::InterfaceValue* msg, MultiLibLoader loader, size_t size = 1);
};
  void ros2_control_msgs_msg_InterfaceValue_common::copy_from_struct(control_msgs::msg::InterfaceValue* msg, const matlab::data::Struct& arr,
               MultiLibLoader loader) {
    try {
        //interface_names
        const matlab::data::CellArray interface_names_cellarr = arr["interface_names"];
        size_t nelem = interface_names_cellarr.getNumberOfElements();
        for (size_t idx=0; idx < nelem; ++idx){
        	const matlab::data::CharArray interface_names_arr = interface_names_cellarr[idx];
        	msg->interface_names.push_back(interface_names_arr.toAscii());
        }
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'interface_names' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'interface_names' is wrong type; expected a string.");
    }
    try {
        //values
        const matlab::data::TypedArray<double> values_arr = arr["values"];
        size_t nelem = values_arr.getNumberOfElements();
        	msg->values.resize(nelem);
        	std::copy(values_arr.begin(), values_arr.begin()+nelem, msg->values.begin());
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'values' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'values' is wrong type; expected a double.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T ros2_control_msgs_msg_InterfaceValue_common::get_arr(MDFactory_T& factory, const control_msgs::msg::InterfaceValue* msg,
       MultiLibLoader loader, size_t size) {
    auto outArray = factory.createStructArray({size,1},{"MessageType","interface_names","values"});
    for(size_t ctr = 0; ctr < size; ctr++){
    outArray[ctr]["MessageType"] = factory.createCharArray("control_msgs/InterfaceValue");
    // interface_names
    auto currentElement_interface_names = (msg + ctr)->interface_names;
    auto interface_namesoutCell = factory.createCellArray({currentElement_interface_names.size(),1});
    for(size_t idxin = 0; idxin < currentElement_interface_names.size(); ++ idxin){
    	interface_namesoutCell[idxin] = factory.createCharArray(currentElement_interface_names[idxin]);
    }
    outArray[ctr]["interface_names"] = interface_namesoutCell;
    // values
    auto currentElement_values = (msg + ctr)->values;
    outArray[ctr]["values"] = factory.createArray<control_msgs::msg::InterfaceValue::_values_type::const_iterator, double>({currentElement_values.size(), 1}, currentElement_values.begin(), currentElement_values.end());
    }
    return std::move(outArray);
  } 
class CONTROL_MSGS_EXPORT ros2_control_msgs_InterfaceValue_message : public ROS2MsgElementInterfaceFactory {
  public:
    virtual ~ros2_control_msgs_InterfaceValue_message(){}
    virtual std::shared_ptr<MATLABPublisherInterface> generatePublisherInterface(ElementType /*type*/);
    virtual std::shared_ptr<MATLABSubscriberInterface> generateSubscriberInterface(ElementType /*type*/);
    virtual std::shared_ptr<void> generateCppMessage(ElementType /*type*/, const matlab::data::StructArray& /* arr */, MultiLibLoader /* loader */, std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* /*commonObjMap*/);
    virtual matlab::data::StructArray generateMLMessage(ElementType  /*type*/ ,void*  /* msg */, MultiLibLoader /* loader */ , std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* /*commonObjMap*/);
};  
  std::shared_ptr<MATLABPublisherInterface> 
          ros2_control_msgs_InterfaceValue_message::generatePublisherInterface(ElementType /*type*/){
    return std::make_shared<ROS2PublisherImpl<control_msgs::msg::InterfaceValue,ros2_control_msgs_msg_InterfaceValue_common>>();
  }
  std::shared_ptr<MATLABSubscriberInterface> 
         ros2_control_msgs_InterfaceValue_message::generateSubscriberInterface(ElementType /*type*/){
    return std::make_shared<ROS2SubscriberImpl<control_msgs::msg::InterfaceValue,ros2_control_msgs_msg_InterfaceValue_common>>();
  }
  std::shared_ptr<void> ros2_control_msgs_InterfaceValue_message::generateCppMessage(ElementType /*type*/, 
                                           const matlab::data::StructArray& arr,
                                           MultiLibLoader loader,
                                           std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* commonObjMap){
    auto msg = std::make_shared<control_msgs::msg::InterfaceValue>();
    ros2_control_msgs_msg_InterfaceValue_common commonObj;
    commonObj.mCommonObjMap = commonObjMap;
    commonObj.copy_from_struct(msg.get(), arr[0], loader);
    return msg;
  }
  matlab::data::StructArray ros2_control_msgs_InterfaceValue_message::generateMLMessage(ElementType  /*type*/ ,
                                                    void*  msg ,
                                                    MultiLibLoader  loader ,
                                                    std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>*  commonObjMap ){
    ros2_control_msgs_msg_InterfaceValue_common commonObj;	
    commonObj.mCommonObjMap = commonObjMap;	
    MDFactory_T factory;
    return commonObj.get_arr(factory, (control_msgs::msg::InterfaceValue*)msg, loader);			
 }
#include "class_loader/register_macro.hpp"
// Register the component with class_loader.
// This acts as a sort of entry point, allowing the component to be discoverable when its library
// is being loaded into a running process.
CLASS_LOADER_REGISTER_CLASS(ros2_control_msgs_msg_InterfaceValue_common, MATLABROS2MsgInterface<control_msgs::msg::InterfaceValue>)
CLASS_LOADER_REGISTER_CLASS(ros2_control_msgs_InterfaceValue_message, ROS2MsgElementInterfaceFactory)
#ifdef _MSC_VER
#pragma warning(pop)
#else
#pragma GCC diagnostic pop
#endif //_MSC_VER