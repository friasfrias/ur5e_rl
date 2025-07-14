// Copyright 2020-2022 The MathWorks, Inc.
// Common copy functions for trajectory_msgs/JointTrajectoryPoint
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
#include "trajectory_msgs/msg/joint_trajectory_point.hpp"
#include "visibility_control.h"
#include "class_loader/multi_library_class_loader.hpp"
#include "ROS2PubSubTemplates.hpp"
class TRAJECTORY_MSGS_EXPORT ros2_trajectory_msgs_msg_JointTrajectoryPoint_common : public MATLABROS2MsgInterface<trajectory_msgs::msg::JointTrajectoryPoint> {
  public:
    virtual ~ros2_trajectory_msgs_msg_JointTrajectoryPoint_common(){}
    virtual void copy_from_struct(trajectory_msgs::msg::JointTrajectoryPoint* msg, const matlab::data::Struct& arr, MultiLibLoader loader); 
    //----------------------------------------------------------------------------
    virtual MDArray_T get_arr(MDFactory_T& factory, const trajectory_msgs::msg::JointTrajectoryPoint* msg, MultiLibLoader loader, size_t size = 1);
};
  void ros2_trajectory_msgs_msg_JointTrajectoryPoint_common::copy_from_struct(trajectory_msgs::msg::JointTrajectoryPoint* msg, const matlab::data::Struct& arr,
               MultiLibLoader loader) {
    try {
        //positions
        const matlab::data::TypedArray<double> positions_arr = arr["positions"];
        size_t nelem = positions_arr.getNumberOfElements();
        	msg->positions.resize(nelem);
        	std::copy(positions_arr.begin(), positions_arr.begin()+nelem, msg->positions.begin());
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'positions' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'positions' is wrong type; expected a double.");
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
        //accelerations
        const matlab::data::TypedArray<double> accelerations_arr = arr["accelerations"];
        size_t nelem = accelerations_arr.getNumberOfElements();
        	msg->accelerations.resize(nelem);
        	std::copy(accelerations_arr.begin(), accelerations_arr.begin()+nelem, msg->accelerations.begin());
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'accelerations' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'accelerations' is wrong type; expected a double.");
    }
    try {
        //effort
        const matlab::data::TypedArray<double> effort_arr = arr["effort"];
        size_t nelem = effort_arr.getNumberOfElements();
        	msg->effort.resize(nelem);
        	std::copy(effort_arr.begin(), effort_arr.begin()+nelem, msg->effort.begin());
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'effort' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'effort' is wrong type; expected a double.");
    }
    try {
        //time_from_start
        const matlab::data::StructArray time_from_start_arr = arr["time_from_start"];
        auto msgClassPtr_time_from_start = getCommonObject<builtin_interfaces::msg::Duration>("ros2_builtin_interfaces_msg_Duration_common",loader);
        msgClassPtr_time_from_start->copy_from_struct(&msg->time_from_start,time_from_start_arr[0],loader);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'time_from_start' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'time_from_start' is wrong type; expected a struct.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T ros2_trajectory_msgs_msg_JointTrajectoryPoint_common::get_arr(MDFactory_T& factory, const trajectory_msgs::msg::JointTrajectoryPoint* msg,
       MultiLibLoader loader, size_t size) {
    auto outArray = factory.createStructArray({size,1},{"MessageType","positions","velocities","accelerations","effort","time_from_start"});
    for(size_t ctr = 0; ctr < size; ctr++){
    outArray[ctr]["MessageType"] = factory.createCharArray("trajectory_msgs/JointTrajectoryPoint");
    // positions
    auto currentElement_positions = (msg + ctr)->positions;
    outArray[ctr]["positions"] = factory.createArray<trajectory_msgs::msg::JointTrajectoryPoint::_positions_type::const_iterator, double>({currentElement_positions.size(), 1}, currentElement_positions.begin(), currentElement_positions.end());
    // velocities
    auto currentElement_velocities = (msg + ctr)->velocities;
    outArray[ctr]["velocities"] = factory.createArray<trajectory_msgs::msg::JointTrajectoryPoint::_velocities_type::const_iterator, double>({currentElement_velocities.size(), 1}, currentElement_velocities.begin(), currentElement_velocities.end());
    // accelerations
    auto currentElement_accelerations = (msg + ctr)->accelerations;
    outArray[ctr]["accelerations"] = factory.createArray<trajectory_msgs::msg::JointTrajectoryPoint::_accelerations_type::const_iterator, double>({currentElement_accelerations.size(), 1}, currentElement_accelerations.begin(), currentElement_accelerations.end());
    // effort
    auto currentElement_effort = (msg + ctr)->effort;
    outArray[ctr]["effort"] = factory.createArray<trajectory_msgs::msg::JointTrajectoryPoint::_effort_type::const_iterator, double>({currentElement_effort.size(), 1}, currentElement_effort.begin(), currentElement_effort.end());
    // time_from_start
    auto currentElement_time_from_start = (msg + ctr)->time_from_start;
    auto msgClassPtr_time_from_start = getCommonObject<builtin_interfaces::msg::Duration>("ros2_builtin_interfaces_msg_Duration_common",loader);
    outArray[ctr]["time_from_start"] = msgClassPtr_time_from_start->get_arr(factory, &currentElement_time_from_start, loader);
    }
    return std::move(outArray);
  } 
class TRAJECTORY_MSGS_EXPORT ros2_trajectory_msgs_JointTrajectoryPoint_message : public ROS2MsgElementInterfaceFactory {
  public:
    virtual ~ros2_trajectory_msgs_JointTrajectoryPoint_message(){}
    virtual std::shared_ptr<MATLABPublisherInterface> generatePublisherInterface(ElementType /*type*/);
    virtual std::shared_ptr<MATLABSubscriberInterface> generateSubscriberInterface(ElementType /*type*/);
    virtual std::shared_ptr<void> generateCppMessage(ElementType /*type*/, const matlab::data::StructArray& /* arr */, MultiLibLoader /* loader */, std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* /*commonObjMap*/);
    virtual matlab::data::StructArray generateMLMessage(ElementType  /*type*/ ,void*  /* msg */, MultiLibLoader /* loader */ , std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* /*commonObjMap*/);
};  
  std::shared_ptr<MATLABPublisherInterface> 
          ros2_trajectory_msgs_JointTrajectoryPoint_message::generatePublisherInterface(ElementType /*type*/){
    return std::make_shared<ROS2PublisherImpl<trajectory_msgs::msg::JointTrajectoryPoint,ros2_trajectory_msgs_msg_JointTrajectoryPoint_common>>();
  }
  std::shared_ptr<MATLABSubscriberInterface> 
         ros2_trajectory_msgs_JointTrajectoryPoint_message::generateSubscriberInterface(ElementType /*type*/){
    return std::make_shared<ROS2SubscriberImpl<trajectory_msgs::msg::JointTrajectoryPoint,ros2_trajectory_msgs_msg_JointTrajectoryPoint_common>>();
  }
  std::shared_ptr<void> ros2_trajectory_msgs_JointTrajectoryPoint_message::generateCppMessage(ElementType /*type*/, 
                                           const matlab::data::StructArray& arr,
                                           MultiLibLoader loader,
                                           std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* commonObjMap){
    auto msg = std::make_shared<trajectory_msgs::msg::JointTrajectoryPoint>();
    ros2_trajectory_msgs_msg_JointTrajectoryPoint_common commonObj;
    commonObj.mCommonObjMap = commonObjMap;
    commonObj.copy_from_struct(msg.get(), arr[0], loader);
    return msg;
  }
  matlab::data::StructArray ros2_trajectory_msgs_JointTrajectoryPoint_message::generateMLMessage(ElementType  /*type*/ ,
                                                    void*  msg ,
                                                    MultiLibLoader  loader ,
                                                    std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>*  commonObjMap ){
    ros2_trajectory_msgs_msg_JointTrajectoryPoint_common commonObj;	
    commonObj.mCommonObjMap = commonObjMap;	
    MDFactory_T factory;
    return commonObj.get_arr(factory, (trajectory_msgs::msg::JointTrajectoryPoint*)msg, loader);			
 }
#include "class_loader/register_macro.hpp"
// Register the component with class_loader.
// This acts as a sort of entry point, allowing the component to be discoverable when its library
// is being loaded into a running process.
CLASS_LOADER_REGISTER_CLASS(ros2_trajectory_msgs_msg_JointTrajectoryPoint_common, MATLABROS2MsgInterface<trajectory_msgs::msg::JointTrajectoryPoint>)
CLASS_LOADER_REGISTER_CLASS(ros2_trajectory_msgs_JointTrajectoryPoint_message, ROS2MsgElementInterfaceFactory)
#ifdef _MSC_VER
#pragma warning(pop)
#else
#pragma GCC diagnostic pop
#endif //_MSC_VER