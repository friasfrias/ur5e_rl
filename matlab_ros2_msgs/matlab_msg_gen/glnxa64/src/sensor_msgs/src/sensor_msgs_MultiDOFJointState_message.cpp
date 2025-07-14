// Copyright 2020-2022 The MathWorks, Inc.
// Common copy functions for sensor_msgs/MultiDOFJointState
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
#include "sensor_msgs/msg/multi_dof_joint_state.hpp"
#include "visibility_control.h"
#include "class_loader/multi_library_class_loader.hpp"
#include "ROS2PubSubTemplates.hpp"
class SENSOR_MSGS_EXPORT ros2_sensor_msgs_msg_MultiDOFJointState_common : public MATLABROS2MsgInterface<sensor_msgs::msg::MultiDOFJointState> {
  public:
    virtual ~ros2_sensor_msgs_msg_MultiDOFJointState_common(){}
    virtual void copy_from_struct(sensor_msgs::msg::MultiDOFJointState* msg, const matlab::data::Struct& arr, MultiLibLoader loader); 
    //----------------------------------------------------------------------------
    virtual MDArray_T get_arr(MDFactory_T& factory, const sensor_msgs::msg::MultiDOFJointState* msg, MultiLibLoader loader, size_t size = 1);
};
  void ros2_sensor_msgs_msg_MultiDOFJointState_common::copy_from_struct(sensor_msgs::msg::MultiDOFJointState* msg, const matlab::data::Struct& arr,
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
        //transforms
        const matlab::data::StructArray transforms_arr = arr["transforms"];
        for (auto _transformsarr : transforms_arr) {
        	geometry_msgs::msg::Transform _val;
        auto msgClassPtr_transforms = getCommonObject<geometry_msgs::msg::Transform>("ros2_geometry_msgs_msg_Transform_common",loader);
        msgClassPtr_transforms->copy_from_struct(&_val,_transformsarr,loader);
        	msg->transforms.push_back(_val);
        }
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'transforms' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'transforms' is wrong type; expected a struct.");
    }
    try {
        //twist
        const matlab::data::StructArray twist_arr = arr["twist"];
        for (auto _twistarr : twist_arr) {
        	geometry_msgs::msg::Twist _val;
        auto msgClassPtr_twist = getCommonObject<geometry_msgs::msg::Twist>("ros2_geometry_msgs_msg_Twist_common",loader);
        msgClassPtr_twist->copy_from_struct(&_val,_twistarr,loader);
        	msg->twist.push_back(_val);
        }
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'twist' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'twist' is wrong type; expected a struct.");
    }
    try {
        //wrench
        const matlab::data::StructArray wrench_arr = arr["wrench"];
        for (auto _wrencharr : wrench_arr) {
        	geometry_msgs::msg::Wrench _val;
        auto msgClassPtr_wrench = getCommonObject<geometry_msgs::msg::Wrench>("ros2_geometry_msgs_msg_Wrench_common",loader);
        msgClassPtr_wrench->copy_from_struct(&_val,_wrencharr,loader);
        	msg->wrench.push_back(_val);
        }
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'wrench' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'wrench' is wrong type; expected a struct.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T ros2_sensor_msgs_msg_MultiDOFJointState_common::get_arr(MDFactory_T& factory, const sensor_msgs::msg::MultiDOFJointState* msg,
       MultiLibLoader loader, size_t size) {
    auto outArray = factory.createStructArray({size,1},{"MessageType","header","joint_names","transforms","twist","wrench"});
    for(size_t ctr = 0; ctr < size; ctr++){
    outArray[ctr]["MessageType"] = factory.createCharArray("sensor_msgs/MultiDOFJointState");
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
    // transforms
    auto currentElement_transforms = (msg + ctr)->transforms;
    auto msgClassPtr_transforms = getCommonObject<geometry_msgs::msg::Transform>("ros2_geometry_msgs_msg_Transform_common",loader);
    outArray[ctr]["transforms"] = msgClassPtr_transforms->get_arr(factory,&currentElement_transforms[0],loader,currentElement_transforms.size());
    // twist
    auto currentElement_twist = (msg + ctr)->twist;
    auto msgClassPtr_twist = getCommonObject<geometry_msgs::msg::Twist>("ros2_geometry_msgs_msg_Twist_common",loader);
    outArray[ctr]["twist"] = msgClassPtr_twist->get_arr(factory,&currentElement_twist[0],loader,currentElement_twist.size());
    // wrench
    auto currentElement_wrench = (msg + ctr)->wrench;
    auto msgClassPtr_wrench = getCommonObject<geometry_msgs::msg::Wrench>("ros2_geometry_msgs_msg_Wrench_common",loader);
    outArray[ctr]["wrench"] = msgClassPtr_wrench->get_arr(factory,&currentElement_wrench[0],loader,currentElement_wrench.size());
    }
    return std::move(outArray);
  } 
class SENSOR_MSGS_EXPORT ros2_sensor_msgs_MultiDOFJointState_message : public ROS2MsgElementInterfaceFactory {
  public:
    virtual ~ros2_sensor_msgs_MultiDOFJointState_message(){}
    virtual std::shared_ptr<MATLABPublisherInterface> generatePublisherInterface(ElementType /*type*/);
    virtual std::shared_ptr<MATLABSubscriberInterface> generateSubscriberInterface(ElementType /*type*/);
    virtual std::shared_ptr<void> generateCppMessage(ElementType /*type*/, const matlab::data::StructArray& /* arr */, MultiLibLoader /* loader */, std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* /*commonObjMap*/);
    virtual matlab::data::StructArray generateMLMessage(ElementType  /*type*/ ,void*  /* msg */, MultiLibLoader /* loader */ , std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* /*commonObjMap*/);
};  
  std::shared_ptr<MATLABPublisherInterface> 
          ros2_sensor_msgs_MultiDOFJointState_message::generatePublisherInterface(ElementType /*type*/){
    return std::make_shared<ROS2PublisherImpl<sensor_msgs::msg::MultiDOFJointState,ros2_sensor_msgs_msg_MultiDOFJointState_common>>();
  }
  std::shared_ptr<MATLABSubscriberInterface> 
         ros2_sensor_msgs_MultiDOFJointState_message::generateSubscriberInterface(ElementType /*type*/){
    return std::make_shared<ROS2SubscriberImpl<sensor_msgs::msg::MultiDOFJointState,ros2_sensor_msgs_msg_MultiDOFJointState_common>>();
  }
  std::shared_ptr<void> ros2_sensor_msgs_MultiDOFJointState_message::generateCppMessage(ElementType /*type*/, 
                                           const matlab::data::StructArray& arr,
                                           MultiLibLoader loader,
                                           std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* commonObjMap){
    auto msg = std::make_shared<sensor_msgs::msg::MultiDOFJointState>();
    ros2_sensor_msgs_msg_MultiDOFJointState_common commonObj;
    commonObj.mCommonObjMap = commonObjMap;
    commonObj.copy_from_struct(msg.get(), arr[0], loader);
    return msg;
  }
  matlab::data::StructArray ros2_sensor_msgs_MultiDOFJointState_message::generateMLMessage(ElementType  /*type*/ ,
                                                    void*  msg ,
                                                    MultiLibLoader  loader ,
                                                    std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>*  commonObjMap ){
    ros2_sensor_msgs_msg_MultiDOFJointState_common commonObj;	
    commonObj.mCommonObjMap = commonObjMap;	
    MDFactory_T factory;
    return commonObj.get_arr(factory, (sensor_msgs::msg::MultiDOFJointState*)msg, loader);			
 }
#include "class_loader/register_macro.hpp"
// Register the component with class_loader.
// This acts as a sort of entry point, allowing the component to be discoverable when its library
// is being loaded into a running process.
CLASS_LOADER_REGISTER_CLASS(ros2_sensor_msgs_msg_MultiDOFJointState_common, MATLABROS2MsgInterface<sensor_msgs::msg::MultiDOFJointState>)
CLASS_LOADER_REGISTER_CLASS(ros2_sensor_msgs_MultiDOFJointState_message, ROS2MsgElementInterfaceFactory)
#ifdef _MSC_VER
#pragma warning(pop)
#else
#pragma GCC diagnostic pop
#endif //_MSC_VER