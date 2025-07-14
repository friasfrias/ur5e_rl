// Copyright 2020-2022 The MathWorks, Inc.
// Common copy functions for control_msgs/MultiDOFCommand
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
#include "control_msgs/msg/multi_dof_command.hpp"
#include "visibility_control.h"
#include "class_loader/multi_library_class_loader.hpp"
#include "ROS2PubSubTemplates.hpp"
class CONTROL_MSGS_EXPORT ros2_control_msgs_msg_MultiDOFCommand_common : public MATLABROS2MsgInterface<control_msgs::msg::MultiDOFCommand> {
  public:
    virtual ~ros2_control_msgs_msg_MultiDOFCommand_common(){}
    virtual void copy_from_struct(control_msgs::msg::MultiDOFCommand* msg, const matlab::data::Struct& arr, MultiLibLoader loader); 
    //----------------------------------------------------------------------------
    virtual MDArray_T get_arr(MDFactory_T& factory, const control_msgs::msg::MultiDOFCommand* msg, MultiLibLoader loader, size_t size = 1);
};
  void ros2_control_msgs_msg_MultiDOFCommand_common::copy_from_struct(control_msgs::msg::MultiDOFCommand* msg, const matlab::data::Struct& arr,
               MultiLibLoader loader) {
    try {
        //dof_names
        const matlab::data::CellArray dof_names_cellarr = arr["dof_names"];
        size_t nelem = dof_names_cellarr.getNumberOfElements();
        for (size_t idx=0; idx < nelem; ++idx){
        	const matlab::data::CharArray dof_names_arr = dof_names_cellarr[idx];
        	msg->dof_names.push_back(dof_names_arr.toAscii());
        }
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'dof_names' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'dof_names' is wrong type; expected a string.");
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
    try {
        //values_dot
        const matlab::data::TypedArray<double> values_dot_arr = arr["values_dot"];
        size_t nelem = values_dot_arr.getNumberOfElements();
        	msg->values_dot.resize(nelem);
        	std::copy(values_dot_arr.begin(), values_dot_arr.begin()+nelem, msg->values_dot.begin());
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'values_dot' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'values_dot' is wrong type; expected a double.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T ros2_control_msgs_msg_MultiDOFCommand_common::get_arr(MDFactory_T& factory, const control_msgs::msg::MultiDOFCommand* msg,
       MultiLibLoader loader, size_t size) {
    auto outArray = factory.createStructArray({size,1},{"MessageType","dof_names","values","values_dot"});
    for(size_t ctr = 0; ctr < size; ctr++){
    outArray[ctr]["MessageType"] = factory.createCharArray("control_msgs/MultiDOFCommand");
    // dof_names
    auto currentElement_dof_names = (msg + ctr)->dof_names;
    auto dof_namesoutCell = factory.createCellArray({currentElement_dof_names.size(),1});
    for(size_t idxin = 0; idxin < currentElement_dof_names.size(); ++ idxin){
    	dof_namesoutCell[idxin] = factory.createCharArray(currentElement_dof_names[idxin]);
    }
    outArray[ctr]["dof_names"] = dof_namesoutCell;
    // values
    auto currentElement_values = (msg + ctr)->values;
    outArray[ctr]["values"] = factory.createArray<control_msgs::msg::MultiDOFCommand::_values_type::const_iterator, double>({currentElement_values.size(), 1}, currentElement_values.begin(), currentElement_values.end());
    // values_dot
    auto currentElement_values_dot = (msg + ctr)->values_dot;
    outArray[ctr]["values_dot"] = factory.createArray<control_msgs::msg::MultiDOFCommand::_values_dot_type::const_iterator, double>({currentElement_values_dot.size(), 1}, currentElement_values_dot.begin(), currentElement_values_dot.end());
    }
    return std::move(outArray);
  } 
class CONTROL_MSGS_EXPORT ros2_control_msgs_MultiDOFCommand_message : public ROS2MsgElementInterfaceFactory {
  public:
    virtual ~ros2_control_msgs_MultiDOFCommand_message(){}
    virtual std::shared_ptr<MATLABPublisherInterface> generatePublisherInterface(ElementType /*type*/);
    virtual std::shared_ptr<MATLABSubscriberInterface> generateSubscriberInterface(ElementType /*type*/);
    virtual std::shared_ptr<void> generateCppMessage(ElementType /*type*/, const matlab::data::StructArray& /* arr */, MultiLibLoader /* loader */, std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* /*commonObjMap*/);
    virtual matlab::data::StructArray generateMLMessage(ElementType  /*type*/ ,void*  /* msg */, MultiLibLoader /* loader */ , std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* /*commonObjMap*/);
};  
  std::shared_ptr<MATLABPublisherInterface> 
          ros2_control_msgs_MultiDOFCommand_message::generatePublisherInterface(ElementType /*type*/){
    return std::make_shared<ROS2PublisherImpl<control_msgs::msg::MultiDOFCommand,ros2_control_msgs_msg_MultiDOFCommand_common>>();
  }
  std::shared_ptr<MATLABSubscriberInterface> 
         ros2_control_msgs_MultiDOFCommand_message::generateSubscriberInterface(ElementType /*type*/){
    return std::make_shared<ROS2SubscriberImpl<control_msgs::msg::MultiDOFCommand,ros2_control_msgs_msg_MultiDOFCommand_common>>();
  }
  std::shared_ptr<void> ros2_control_msgs_MultiDOFCommand_message::generateCppMessage(ElementType /*type*/, 
                                           const matlab::data::StructArray& arr,
                                           MultiLibLoader loader,
                                           std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* commonObjMap){
    auto msg = std::make_shared<control_msgs::msg::MultiDOFCommand>();
    ros2_control_msgs_msg_MultiDOFCommand_common commonObj;
    commonObj.mCommonObjMap = commonObjMap;
    commonObj.copy_from_struct(msg.get(), arr[0], loader);
    return msg;
  }
  matlab::data::StructArray ros2_control_msgs_MultiDOFCommand_message::generateMLMessage(ElementType  /*type*/ ,
                                                    void*  msg ,
                                                    MultiLibLoader  loader ,
                                                    std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>*  commonObjMap ){
    ros2_control_msgs_msg_MultiDOFCommand_common commonObj;	
    commonObj.mCommonObjMap = commonObjMap;	
    MDFactory_T factory;
    return commonObj.get_arr(factory, (control_msgs::msg::MultiDOFCommand*)msg, loader);			
 }
#include "class_loader/register_macro.hpp"
// Register the component with class_loader.
// This acts as a sort of entry point, allowing the component to be discoverable when its library
// is being loaded into a running process.
CLASS_LOADER_REGISTER_CLASS(ros2_control_msgs_msg_MultiDOFCommand_common, MATLABROS2MsgInterface<control_msgs::msg::MultiDOFCommand>)
CLASS_LOADER_REGISTER_CLASS(ros2_control_msgs_MultiDOFCommand_message, ROS2MsgElementInterfaceFactory)
#ifdef _MSC_VER
#pragma warning(pop)
#else
#pragma GCC diagnostic pop
#endif //_MSC_VER