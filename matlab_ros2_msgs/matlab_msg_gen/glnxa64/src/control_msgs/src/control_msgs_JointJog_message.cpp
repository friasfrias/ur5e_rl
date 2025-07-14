// Copyright 2020-2022 The MathWorks, Inc.
// Common copy functions for control_msgs/JointJog
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
#include "control_msgs/msg/joint_jog.hpp"
#include "visibility_control.h"
#include "class_loader/multi_library_class_loader.hpp"
#include "ROS2PubSubTemplates.hpp"
class CONTROL_MSGS_EXPORT ros2_control_msgs_msg_JointJog_common : public MATLABROS2MsgInterface<control_msgs::msg::JointJog> {
  public:
    virtual ~ros2_control_msgs_msg_JointJog_common(){}
    virtual void copy_from_struct(control_msgs::msg::JointJog* msg, const matlab::data::Struct& arr, MultiLibLoader loader); 
    //----------------------------------------------------------------------------
    virtual MDArray_T get_arr(MDFactory_T& factory, const control_msgs::msg::JointJog* msg, MultiLibLoader loader, size_t size = 1);
};
  void ros2_control_msgs_msg_JointJog_common::copy_from_struct(control_msgs::msg::JointJog* msg, const matlab::data::Struct& arr,
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
        //displacements
        const matlab::data::TypedArray<double> displacements_arr = arr["displacements"];
        size_t nelem = displacements_arr.getNumberOfElements();
        	msg->displacements.resize(nelem);
        	std::copy(displacements_arr.begin(), displacements_arr.begin()+nelem, msg->displacements.begin());
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'displacements' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'displacements' is wrong type; expected a double.");
    }
    try {
        //velocities
        const matlab::data::TypedArray<double> velocities_arr = arr["velocities"];
        size_t nelem = velocities_arr.getNumberOfElements();
        	msg->velocities.resize(nelem);
        	std::copy(velocities_arr.begin(), velocities_arr.begin()+nelem, msg->velocities.begin());
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'velocities' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'velocities' is wrong type; expected a double.");
    }
    try {
        //duration
        const matlab::data::TypedArray<double> duration_arr = arr["duration"];
        msg->duration = duration_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'duration' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'duration' is wrong type; expected a double.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T ros2_control_msgs_msg_JointJog_common::get_arr(MDFactory_T& factory, const control_msgs::msg::JointJog* msg,
       MultiLibLoader loader, size_t size) {
    auto outArray = factory.createStructArray({size,1},{"MessageType","header","joint_names","displacements","velocities","duration"});
    for(size_t ctr = 0; ctr < size; ctr++){
    outArray[ctr]["MessageType"] = factory.createCharArray("control_msgs/JointJog");
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
    // displacements
    auto currentElement_displacements = (msg + ctr)->displacements;
    outArray[ctr]["displacements"] = factory.createArray<control_msgs::msg::JointJog::_displacements_type::const_iterator, double>({currentElement_displacements.size(), 1}, currentElement_displacements.begin(), currentElement_displacements.end());
    // velocities
    auto currentElement_velocities = (msg + ctr)->velocities;
    outArray[ctr]["velocities"] = factory.createArray<control_msgs::msg::JointJog::_velocities_type::const_iterator, double>({currentElement_velocities.size(), 1}, currentElement_velocities.begin(), currentElement_velocities.end());
    // duration
    auto currentElement_duration = (msg + ctr)->duration;
    outArray[ctr]["duration"] = factory.createScalar(currentElement_duration);
    }
    return std::move(outArray);
  } 
class CONTROL_MSGS_EXPORT ros2_control_msgs_JointJog_message : public ROS2MsgElementInterfaceFactory {
  public:
    virtual ~ros2_control_msgs_JointJog_message(){}
    virtual std::shared_ptr<MATLABPublisherInterface> generatePublisherInterface(ElementType /*type*/);
    virtual std::shared_ptr<MATLABSubscriberInterface> generateSubscriberInterface(ElementType /*type*/);
    virtual std::shared_ptr<void> generateCppMessage(ElementType /*type*/, const matlab::data::StructArray& /* arr */, MultiLibLoader /* loader */, std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* /*commonObjMap*/);
    virtual matlab::data::StructArray generateMLMessage(ElementType  /*type*/ ,void*  /* msg */, MultiLibLoader /* loader */ , std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* /*commonObjMap*/);
};  
  std::shared_ptr<MATLABPublisherInterface> 
          ros2_control_msgs_JointJog_message::generatePublisherInterface(ElementType /*type*/){
    return std::make_shared<ROS2PublisherImpl<control_msgs::msg::JointJog,ros2_control_msgs_msg_JointJog_common>>();
  }
  std::shared_ptr<MATLABSubscriberInterface> 
         ros2_control_msgs_JointJog_message::generateSubscriberInterface(ElementType /*type*/){
    return std::make_shared<ROS2SubscriberImpl<control_msgs::msg::JointJog,ros2_control_msgs_msg_JointJog_common>>();
  }
  std::shared_ptr<void> ros2_control_msgs_JointJog_message::generateCppMessage(ElementType /*type*/, 
                                           const matlab::data::StructArray& arr,
                                           MultiLibLoader loader,
                                           std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* commonObjMap){
    auto msg = std::make_shared<control_msgs::msg::JointJog>();
    ros2_control_msgs_msg_JointJog_common commonObj;
    commonObj.mCommonObjMap = commonObjMap;
    commonObj.copy_from_struct(msg.get(), arr[0], loader);
    return msg;
  }
  matlab::data::StructArray ros2_control_msgs_JointJog_message::generateMLMessage(ElementType  /*type*/ ,
                                                    void*  msg ,
                                                    MultiLibLoader  loader ,
                                                    std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>*  commonObjMap ){
    ros2_control_msgs_msg_JointJog_common commonObj;	
    commonObj.mCommonObjMap = commonObjMap;	
    MDFactory_T factory;
    return commonObj.get_arr(factory, (control_msgs::msg::JointJog*)msg, loader);			
 }
#include "class_loader/register_macro.hpp"
// Register the component with class_loader.
// This acts as a sort of entry point, allowing the component to be discoverable when its library
// is being loaded into a running process.
CLASS_LOADER_REGISTER_CLASS(ros2_control_msgs_msg_JointJog_common, MATLABROS2MsgInterface<control_msgs::msg::JointJog>)
CLASS_LOADER_REGISTER_CLASS(ros2_control_msgs_JointJog_message, ROS2MsgElementInterfaceFactory)
#ifdef _MSC_VER
#pragma warning(pop)
#else
#pragma GCC diagnostic pop
#endif //_MSC_VER