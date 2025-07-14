// Copyright 2020-2022 The MathWorks, Inc.
// Common copy functions for trajectory_msgs/MultiDOFJointTrajectoryPoint
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
#include "trajectory_msgs/msg/multi_dof_joint_trajectory_point.hpp"
#include "visibility_control.h"
#include "class_loader/multi_library_class_loader.hpp"
#include "ROS2PubSubTemplates.hpp"
class TRAJECTORY_MSGS_EXPORT ros2_trajectory_msgs_msg_MultiDOFJointTrajectoryPoint_common : public MATLABROS2MsgInterface<trajectory_msgs::msg::MultiDOFJointTrajectoryPoint> {
  public:
    virtual ~ros2_trajectory_msgs_msg_MultiDOFJointTrajectoryPoint_common(){}
    virtual void copy_from_struct(trajectory_msgs::msg::MultiDOFJointTrajectoryPoint* msg, const matlab::data::Struct& arr, MultiLibLoader loader); 
    //----------------------------------------------------------------------------
    virtual MDArray_T get_arr(MDFactory_T& factory, const trajectory_msgs::msg::MultiDOFJointTrajectoryPoint* msg, MultiLibLoader loader, size_t size = 1);
};
  void ros2_trajectory_msgs_msg_MultiDOFJointTrajectoryPoint_common::copy_from_struct(trajectory_msgs::msg::MultiDOFJointTrajectoryPoint* msg, const matlab::data::Struct& arr,
               MultiLibLoader loader) {
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
        //velocities
        const matlab::data::StructArray velocities_arr = arr["velocities"];
        for (auto _velocitiesarr : velocities_arr) {
        	geometry_msgs::msg::Twist _val;
        auto msgClassPtr_velocities = getCommonObject<geometry_msgs::msg::Twist>("ros2_geometry_msgs_msg_Twist_common",loader);
        msgClassPtr_velocities->copy_from_struct(&_val,_velocitiesarr,loader);
        	msg->velocities.push_back(_val);
        }
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'velocities' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'velocities' is wrong type; expected a struct.");
    }
    try {
        //accelerations
        const matlab::data::StructArray accelerations_arr = arr["accelerations"];
        for (auto _accelerationsarr : accelerations_arr) {
        	geometry_msgs::msg::Twist _val;
        auto msgClassPtr_accelerations = getCommonObject<geometry_msgs::msg::Twist>("ros2_geometry_msgs_msg_Twist_common",loader);
        msgClassPtr_accelerations->copy_from_struct(&_val,_accelerationsarr,loader);
        	msg->accelerations.push_back(_val);
        }
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'accelerations' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'accelerations' is wrong type; expected a struct.");
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
  MDArray_T ros2_trajectory_msgs_msg_MultiDOFJointTrajectoryPoint_common::get_arr(MDFactory_T& factory, const trajectory_msgs::msg::MultiDOFJointTrajectoryPoint* msg,
       MultiLibLoader loader, size_t size) {
    auto outArray = factory.createStructArray({size,1},{"MessageType","transforms","velocities","accelerations","time_from_start"});
    for(size_t ctr = 0; ctr < size; ctr++){
    outArray[ctr]["MessageType"] = factory.createCharArray("trajectory_msgs/MultiDOFJointTrajectoryPoint");
    // transforms
    auto currentElement_transforms = (msg + ctr)->transforms;
    auto msgClassPtr_transforms = getCommonObject<geometry_msgs::msg::Transform>("ros2_geometry_msgs_msg_Transform_common",loader);
    outArray[ctr]["transforms"] = msgClassPtr_transforms->get_arr(factory,&currentElement_transforms[0],loader,currentElement_transforms.size());
    // velocities
    auto currentElement_velocities = (msg + ctr)->velocities;
    auto msgClassPtr_velocities = getCommonObject<geometry_msgs::msg::Twist>("ros2_geometry_msgs_msg_Twist_common",loader);
    outArray[ctr]["velocities"] = msgClassPtr_velocities->get_arr(factory,&currentElement_velocities[0],loader,currentElement_velocities.size());
    // accelerations
    auto currentElement_accelerations = (msg + ctr)->accelerations;
    auto msgClassPtr_accelerations = getCommonObject<geometry_msgs::msg::Twist>("ros2_geometry_msgs_msg_Twist_common",loader);
    outArray[ctr]["accelerations"] = msgClassPtr_accelerations->get_arr(factory,&currentElement_accelerations[0],loader,currentElement_accelerations.size());
    // time_from_start
    auto currentElement_time_from_start = (msg + ctr)->time_from_start;
    auto msgClassPtr_time_from_start = getCommonObject<builtin_interfaces::msg::Duration>("ros2_builtin_interfaces_msg_Duration_common",loader);
    outArray[ctr]["time_from_start"] = msgClassPtr_time_from_start->get_arr(factory, &currentElement_time_from_start, loader);
    }
    return std::move(outArray);
  } 
class TRAJECTORY_MSGS_EXPORT ros2_trajectory_msgs_MultiDOFJointTrajectoryPoint_message : public ROS2MsgElementInterfaceFactory {
  public:
    virtual ~ros2_trajectory_msgs_MultiDOFJointTrajectoryPoint_message(){}
    virtual std::shared_ptr<MATLABPublisherInterface> generatePublisherInterface(ElementType /*type*/);
    virtual std::shared_ptr<MATLABSubscriberInterface> generateSubscriberInterface(ElementType /*type*/);
    virtual std::shared_ptr<void> generateCppMessage(ElementType /*type*/, const matlab::data::StructArray& /* arr */, MultiLibLoader /* loader */, std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* /*commonObjMap*/);
    virtual matlab::data::StructArray generateMLMessage(ElementType  /*type*/ ,void*  /* msg */, MultiLibLoader /* loader */ , std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* /*commonObjMap*/);
};  
  std::shared_ptr<MATLABPublisherInterface> 
          ros2_trajectory_msgs_MultiDOFJointTrajectoryPoint_message::generatePublisherInterface(ElementType /*type*/){
    return std::make_shared<ROS2PublisherImpl<trajectory_msgs::msg::MultiDOFJointTrajectoryPoint,ros2_trajectory_msgs_msg_MultiDOFJointTrajectoryPoint_common>>();
  }
  std::shared_ptr<MATLABSubscriberInterface> 
         ros2_trajectory_msgs_MultiDOFJointTrajectoryPoint_message::generateSubscriberInterface(ElementType /*type*/){
    return std::make_shared<ROS2SubscriberImpl<trajectory_msgs::msg::MultiDOFJointTrajectoryPoint,ros2_trajectory_msgs_msg_MultiDOFJointTrajectoryPoint_common>>();
  }
  std::shared_ptr<void> ros2_trajectory_msgs_MultiDOFJointTrajectoryPoint_message::generateCppMessage(ElementType /*type*/, 
                                           const matlab::data::StructArray& arr,
                                           MultiLibLoader loader,
                                           std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* commonObjMap){
    auto msg = std::make_shared<trajectory_msgs::msg::MultiDOFJointTrajectoryPoint>();
    ros2_trajectory_msgs_msg_MultiDOFJointTrajectoryPoint_common commonObj;
    commonObj.mCommonObjMap = commonObjMap;
    commonObj.copy_from_struct(msg.get(), arr[0], loader);
    return msg;
  }
  matlab::data::StructArray ros2_trajectory_msgs_MultiDOFJointTrajectoryPoint_message::generateMLMessage(ElementType  /*type*/ ,
                                                    void*  msg ,
                                                    MultiLibLoader  loader ,
                                                    std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>*  commonObjMap ){
    ros2_trajectory_msgs_msg_MultiDOFJointTrajectoryPoint_common commonObj;	
    commonObj.mCommonObjMap = commonObjMap;	
    MDFactory_T factory;
    return commonObj.get_arr(factory, (trajectory_msgs::msg::MultiDOFJointTrajectoryPoint*)msg, loader);			
 }
#include "class_loader/register_macro.hpp"
// Register the component with class_loader.
// This acts as a sort of entry point, allowing the component to be discoverable when its library
// is being loaded into a running process.
CLASS_LOADER_REGISTER_CLASS(ros2_trajectory_msgs_msg_MultiDOFJointTrajectoryPoint_common, MATLABROS2MsgInterface<trajectory_msgs::msg::MultiDOFJointTrajectoryPoint>)
CLASS_LOADER_REGISTER_CLASS(ros2_trajectory_msgs_MultiDOFJointTrajectoryPoint_message, ROS2MsgElementInterfaceFactory)
#ifdef _MSC_VER
#pragma warning(pop)
#else
#pragma GCC diagnostic pop
#endif //_MSC_VER