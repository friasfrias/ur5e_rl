// Copyright 2020-2022 The MathWorks, Inc.
// Common copy functions for sensor_msgs/BatteryState
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
#include "sensor_msgs/msg/battery_state.hpp"
#include "visibility_control.h"
#include "class_loader/multi_library_class_loader.hpp"
#include "ROS2PubSubTemplates.hpp"
class SENSOR_MSGS_EXPORT ros2_sensor_msgs_msg_BatteryState_common : public MATLABROS2MsgInterface<sensor_msgs::msg::BatteryState> {
  public:
    virtual ~ros2_sensor_msgs_msg_BatteryState_common(){}
    virtual void copy_from_struct(sensor_msgs::msg::BatteryState* msg, const matlab::data::Struct& arr, MultiLibLoader loader); 
    //----------------------------------------------------------------------------
    virtual MDArray_T get_arr(MDFactory_T& factory, const sensor_msgs::msg::BatteryState* msg, MultiLibLoader loader, size_t size = 1);
};
  void ros2_sensor_msgs_msg_BatteryState_common::copy_from_struct(sensor_msgs::msg::BatteryState* msg, const matlab::data::Struct& arr,
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
        //voltage
        const matlab::data::TypedArray<float> voltage_arr = arr["voltage"];
        msg->voltage = voltage_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'voltage' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'voltage' is wrong type; expected a single.");
    }
    try {
        //temperature
        const matlab::data::TypedArray<float> temperature_arr = arr["temperature"];
        msg->temperature = temperature_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'temperature' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'temperature' is wrong type; expected a single.");
    }
    try {
        //current
        const matlab::data::TypedArray<float> current_arr = arr["current"];
        msg->current = current_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'current' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'current' is wrong type; expected a single.");
    }
    try {
        //charge
        const matlab::data::TypedArray<float> charge_arr = arr["charge"];
        msg->charge = charge_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'charge' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'charge' is wrong type; expected a single.");
    }
    try {
        //capacity
        const matlab::data::TypedArray<float> capacity_arr = arr["capacity"];
        msg->capacity = capacity_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'capacity' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'capacity' is wrong type; expected a single.");
    }
    try {
        //design_capacity
        const matlab::data::TypedArray<float> design_capacity_arr = arr["design_capacity"];
        msg->design_capacity = design_capacity_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'design_capacity' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'design_capacity' is wrong type; expected a single.");
    }
    try {
        //percentage
        const matlab::data::TypedArray<float> percentage_arr = arr["percentage"];
        msg->percentage = percentage_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'percentage' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'percentage' is wrong type; expected a single.");
    }
    try {
        //power_supply_status
        const matlab::data::TypedArray<uint8_t> power_supply_status_arr = arr["power_supply_status"];
        msg->power_supply_status = power_supply_status_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'power_supply_status' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'power_supply_status' is wrong type; expected a uint8.");
    }
    try {
        //power_supply_health
        const matlab::data::TypedArray<uint8_t> power_supply_health_arr = arr["power_supply_health"];
        msg->power_supply_health = power_supply_health_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'power_supply_health' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'power_supply_health' is wrong type; expected a uint8.");
    }
    try {
        //power_supply_technology
        const matlab::data::TypedArray<uint8_t> power_supply_technology_arr = arr["power_supply_technology"];
        msg->power_supply_technology = power_supply_technology_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'power_supply_technology' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'power_supply_technology' is wrong type; expected a uint8.");
    }
    try {
        //present
        const matlab::data::TypedArray<bool> present_arr = arr["present"];
        msg->present = present_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'present' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'present' is wrong type; expected a logical.");
    }
    try {
        //cell_voltage
        const matlab::data::TypedArray<float> cell_voltage_arr = arr["cell_voltage"];
        size_t nelem = cell_voltage_arr.getNumberOfElements();
        	msg->cell_voltage.resize(nelem);
        	std::copy(cell_voltage_arr.begin(), cell_voltage_arr.begin()+nelem, msg->cell_voltage.begin());
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'cell_voltage' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'cell_voltage' is wrong type; expected a single.");
    }
    try {
        //cell_temperature
        const matlab::data::TypedArray<float> cell_temperature_arr = arr["cell_temperature"];
        size_t nelem = cell_temperature_arr.getNumberOfElements();
        	msg->cell_temperature.resize(nelem);
        	std::copy(cell_temperature_arr.begin(), cell_temperature_arr.begin()+nelem, msg->cell_temperature.begin());
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'cell_temperature' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'cell_temperature' is wrong type; expected a single.");
    }
    try {
        //location
        const matlab::data::CharArray location_arr = arr["location"];
        msg->location = location_arr.toAscii();
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'location' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'location' is wrong type; expected a string.");
    }
    try {
        //serial_number
        const matlab::data::CharArray serial_number_arr = arr["serial_number"];
        msg->serial_number = serial_number_arr.toAscii();
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'serial_number' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'serial_number' is wrong type; expected a string.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T ros2_sensor_msgs_msg_BatteryState_common::get_arr(MDFactory_T& factory, const sensor_msgs::msg::BatteryState* msg,
       MultiLibLoader loader, size_t size) {
    auto outArray = factory.createStructArray({size,1},{"MessageType","POWER_SUPPLY_STATUS_UNKNOWN","POWER_SUPPLY_STATUS_CHARGING","POWER_SUPPLY_STATUS_DISCHARGING","POWER_SUPPLY_STATUS_NOT_CHARGING","POWER_SUPPLY_STATUS_FULL","POWER_SUPPLY_HEALTH_UNKNOWN","POWER_SUPPLY_HEALTH_GOOD","POWER_SUPPLY_HEALTH_OVERHEAT","POWER_SUPPLY_HEALTH_DEAD","POWER_SUPPLY_HEALTH_OVERVOLTAGE","POWER_SUPPLY_HEALTH_UNSPEC_FAILURE","POWER_SUPPLY_HEALTH_COLD","POWER_SUPPLY_HEALTH_WATCHDOG_TIMER_EXPIRE","POWER_SUPPLY_HEALTH_SAFETY_TIMER_EXPIRE","POWER_SUPPLY_TECHNOLOGY_UNKNOWN","POWER_SUPPLY_TECHNOLOGY_NIMH","POWER_SUPPLY_TECHNOLOGY_LION","POWER_SUPPLY_TECHNOLOGY_LIPO","POWER_SUPPLY_TECHNOLOGY_LIFE","POWER_SUPPLY_TECHNOLOGY_NICD","POWER_SUPPLY_TECHNOLOGY_LIMN","header","voltage","temperature","current","charge","capacity","design_capacity","percentage","power_supply_status","power_supply_health","power_supply_technology","present","cell_voltage","cell_temperature","location","serial_number"});
    for(size_t ctr = 0; ctr < size; ctr++){
    outArray[ctr]["MessageType"] = factory.createCharArray("sensor_msgs/BatteryState");
    // POWER_SUPPLY_STATUS_UNKNOWN
    auto currentElement_POWER_SUPPLY_STATUS_UNKNOWN = (msg + ctr)->POWER_SUPPLY_STATUS_UNKNOWN;
    outArray[ctr]["POWER_SUPPLY_STATUS_UNKNOWN"] = factory.createScalar(currentElement_POWER_SUPPLY_STATUS_UNKNOWN);
    // POWER_SUPPLY_STATUS_CHARGING
    auto currentElement_POWER_SUPPLY_STATUS_CHARGING = (msg + ctr)->POWER_SUPPLY_STATUS_CHARGING;
    outArray[ctr]["POWER_SUPPLY_STATUS_CHARGING"] = factory.createScalar(currentElement_POWER_SUPPLY_STATUS_CHARGING);
    // POWER_SUPPLY_STATUS_DISCHARGING
    auto currentElement_POWER_SUPPLY_STATUS_DISCHARGING = (msg + ctr)->POWER_SUPPLY_STATUS_DISCHARGING;
    outArray[ctr]["POWER_SUPPLY_STATUS_DISCHARGING"] = factory.createScalar(currentElement_POWER_SUPPLY_STATUS_DISCHARGING);
    // POWER_SUPPLY_STATUS_NOT_CHARGING
    auto currentElement_POWER_SUPPLY_STATUS_NOT_CHARGING = (msg + ctr)->POWER_SUPPLY_STATUS_NOT_CHARGING;
    outArray[ctr]["POWER_SUPPLY_STATUS_NOT_CHARGING"] = factory.createScalar(currentElement_POWER_SUPPLY_STATUS_NOT_CHARGING);
    // POWER_SUPPLY_STATUS_FULL
    auto currentElement_POWER_SUPPLY_STATUS_FULL = (msg + ctr)->POWER_SUPPLY_STATUS_FULL;
    outArray[ctr]["POWER_SUPPLY_STATUS_FULL"] = factory.createScalar(currentElement_POWER_SUPPLY_STATUS_FULL);
    // POWER_SUPPLY_HEALTH_UNKNOWN
    auto currentElement_POWER_SUPPLY_HEALTH_UNKNOWN = (msg + ctr)->POWER_SUPPLY_HEALTH_UNKNOWN;
    outArray[ctr]["POWER_SUPPLY_HEALTH_UNKNOWN"] = factory.createScalar(currentElement_POWER_SUPPLY_HEALTH_UNKNOWN);
    // POWER_SUPPLY_HEALTH_GOOD
    auto currentElement_POWER_SUPPLY_HEALTH_GOOD = (msg + ctr)->POWER_SUPPLY_HEALTH_GOOD;
    outArray[ctr]["POWER_SUPPLY_HEALTH_GOOD"] = factory.createScalar(currentElement_POWER_SUPPLY_HEALTH_GOOD);
    // POWER_SUPPLY_HEALTH_OVERHEAT
    auto currentElement_POWER_SUPPLY_HEALTH_OVERHEAT = (msg + ctr)->POWER_SUPPLY_HEALTH_OVERHEAT;
    outArray[ctr]["POWER_SUPPLY_HEALTH_OVERHEAT"] = factory.createScalar(currentElement_POWER_SUPPLY_HEALTH_OVERHEAT);
    // POWER_SUPPLY_HEALTH_DEAD
    auto currentElement_POWER_SUPPLY_HEALTH_DEAD = (msg + ctr)->POWER_SUPPLY_HEALTH_DEAD;
    outArray[ctr]["POWER_SUPPLY_HEALTH_DEAD"] = factory.createScalar(currentElement_POWER_SUPPLY_HEALTH_DEAD);
    // POWER_SUPPLY_HEALTH_OVERVOLTAGE
    auto currentElement_POWER_SUPPLY_HEALTH_OVERVOLTAGE = (msg + ctr)->POWER_SUPPLY_HEALTH_OVERVOLTAGE;
    outArray[ctr]["POWER_SUPPLY_HEALTH_OVERVOLTAGE"] = factory.createScalar(currentElement_POWER_SUPPLY_HEALTH_OVERVOLTAGE);
    // POWER_SUPPLY_HEALTH_UNSPEC_FAILURE
    auto currentElement_POWER_SUPPLY_HEALTH_UNSPEC_FAILURE = (msg + ctr)->POWER_SUPPLY_HEALTH_UNSPEC_FAILURE;
    outArray[ctr]["POWER_SUPPLY_HEALTH_UNSPEC_FAILURE"] = factory.createScalar(currentElement_POWER_SUPPLY_HEALTH_UNSPEC_FAILURE);
    // POWER_SUPPLY_HEALTH_COLD
    auto currentElement_POWER_SUPPLY_HEALTH_COLD = (msg + ctr)->POWER_SUPPLY_HEALTH_COLD;
    outArray[ctr]["POWER_SUPPLY_HEALTH_COLD"] = factory.createScalar(currentElement_POWER_SUPPLY_HEALTH_COLD);
    // POWER_SUPPLY_HEALTH_WATCHDOG_TIMER_EXPIRE
    auto currentElement_POWER_SUPPLY_HEALTH_WATCHDOG_TIMER_EXPIRE = (msg + ctr)->POWER_SUPPLY_HEALTH_WATCHDOG_TIMER_EXPIRE;
    outArray[ctr]["POWER_SUPPLY_HEALTH_WATCHDOG_TIMER_EXPIRE"] = factory.createScalar(currentElement_POWER_SUPPLY_HEALTH_WATCHDOG_TIMER_EXPIRE);
    // POWER_SUPPLY_HEALTH_SAFETY_TIMER_EXPIRE
    auto currentElement_POWER_SUPPLY_HEALTH_SAFETY_TIMER_EXPIRE = (msg + ctr)->POWER_SUPPLY_HEALTH_SAFETY_TIMER_EXPIRE;
    outArray[ctr]["POWER_SUPPLY_HEALTH_SAFETY_TIMER_EXPIRE"] = factory.createScalar(currentElement_POWER_SUPPLY_HEALTH_SAFETY_TIMER_EXPIRE);
    // POWER_SUPPLY_TECHNOLOGY_UNKNOWN
    auto currentElement_POWER_SUPPLY_TECHNOLOGY_UNKNOWN = (msg + ctr)->POWER_SUPPLY_TECHNOLOGY_UNKNOWN;
    outArray[ctr]["POWER_SUPPLY_TECHNOLOGY_UNKNOWN"] = factory.createScalar(currentElement_POWER_SUPPLY_TECHNOLOGY_UNKNOWN);
    // POWER_SUPPLY_TECHNOLOGY_NIMH
    auto currentElement_POWER_SUPPLY_TECHNOLOGY_NIMH = (msg + ctr)->POWER_SUPPLY_TECHNOLOGY_NIMH;
    outArray[ctr]["POWER_SUPPLY_TECHNOLOGY_NIMH"] = factory.createScalar(currentElement_POWER_SUPPLY_TECHNOLOGY_NIMH);
    // POWER_SUPPLY_TECHNOLOGY_LION
    auto currentElement_POWER_SUPPLY_TECHNOLOGY_LION = (msg + ctr)->POWER_SUPPLY_TECHNOLOGY_LION;
    outArray[ctr]["POWER_SUPPLY_TECHNOLOGY_LION"] = factory.createScalar(currentElement_POWER_SUPPLY_TECHNOLOGY_LION);
    // POWER_SUPPLY_TECHNOLOGY_LIPO
    auto currentElement_POWER_SUPPLY_TECHNOLOGY_LIPO = (msg + ctr)->POWER_SUPPLY_TECHNOLOGY_LIPO;
    outArray[ctr]["POWER_SUPPLY_TECHNOLOGY_LIPO"] = factory.createScalar(currentElement_POWER_SUPPLY_TECHNOLOGY_LIPO);
    // POWER_SUPPLY_TECHNOLOGY_LIFE
    auto currentElement_POWER_SUPPLY_TECHNOLOGY_LIFE = (msg + ctr)->POWER_SUPPLY_TECHNOLOGY_LIFE;
    outArray[ctr]["POWER_SUPPLY_TECHNOLOGY_LIFE"] = factory.createScalar(currentElement_POWER_SUPPLY_TECHNOLOGY_LIFE);
    // POWER_SUPPLY_TECHNOLOGY_NICD
    auto currentElement_POWER_SUPPLY_TECHNOLOGY_NICD = (msg + ctr)->POWER_SUPPLY_TECHNOLOGY_NICD;
    outArray[ctr]["POWER_SUPPLY_TECHNOLOGY_NICD"] = factory.createScalar(currentElement_POWER_SUPPLY_TECHNOLOGY_NICD);
    // POWER_SUPPLY_TECHNOLOGY_LIMN
    auto currentElement_POWER_SUPPLY_TECHNOLOGY_LIMN = (msg + ctr)->POWER_SUPPLY_TECHNOLOGY_LIMN;
    outArray[ctr]["POWER_SUPPLY_TECHNOLOGY_LIMN"] = factory.createScalar(currentElement_POWER_SUPPLY_TECHNOLOGY_LIMN);
    // header
    auto currentElement_header = (msg + ctr)->header;
    auto msgClassPtr_header = getCommonObject<std_msgs::msg::Header>("ros2_std_msgs_msg_Header_common",loader);
    outArray[ctr]["header"] = msgClassPtr_header->get_arr(factory, &currentElement_header, loader);
    // voltage
    auto currentElement_voltage = (msg + ctr)->voltage;
    outArray[ctr]["voltage"] = factory.createScalar(currentElement_voltage);
    // temperature
    auto currentElement_temperature = (msg + ctr)->temperature;
    outArray[ctr]["temperature"] = factory.createScalar(currentElement_temperature);
    // current
    auto currentElement_current = (msg + ctr)->current;
    outArray[ctr]["current"] = factory.createScalar(currentElement_current);
    // charge
    auto currentElement_charge = (msg + ctr)->charge;
    outArray[ctr]["charge"] = factory.createScalar(currentElement_charge);
    // capacity
    auto currentElement_capacity = (msg + ctr)->capacity;
    outArray[ctr]["capacity"] = factory.createScalar(currentElement_capacity);
    // design_capacity
    auto currentElement_design_capacity = (msg + ctr)->design_capacity;
    outArray[ctr]["design_capacity"] = factory.createScalar(currentElement_design_capacity);
    // percentage
    auto currentElement_percentage = (msg + ctr)->percentage;
    outArray[ctr]["percentage"] = factory.createScalar(currentElement_percentage);
    // power_supply_status
    auto currentElement_power_supply_status = (msg + ctr)->power_supply_status;
    outArray[ctr]["power_supply_status"] = factory.createScalar(currentElement_power_supply_status);
    // power_supply_health
    auto currentElement_power_supply_health = (msg + ctr)->power_supply_health;
    outArray[ctr]["power_supply_health"] = factory.createScalar(currentElement_power_supply_health);
    // power_supply_technology
    auto currentElement_power_supply_technology = (msg + ctr)->power_supply_technology;
    outArray[ctr]["power_supply_technology"] = factory.createScalar(currentElement_power_supply_technology);
    // present
    auto currentElement_present = (msg + ctr)->present;
    outArray[ctr]["present"] = factory.createScalar(currentElement_present);
    // cell_voltage
    auto currentElement_cell_voltage = (msg + ctr)->cell_voltage;
    outArray[ctr]["cell_voltage"] = factory.createArray<sensor_msgs::msg::BatteryState::_cell_voltage_type::const_iterator, float>({currentElement_cell_voltage.size(), 1}, currentElement_cell_voltage.begin(), currentElement_cell_voltage.end());
    // cell_temperature
    auto currentElement_cell_temperature = (msg + ctr)->cell_temperature;
    outArray[ctr]["cell_temperature"] = factory.createArray<sensor_msgs::msg::BatteryState::_cell_temperature_type::const_iterator, float>({currentElement_cell_temperature.size(), 1}, currentElement_cell_temperature.begin(), currentElement_cell_temperature.end());
    // location
    auto currentElement_location = (msg + ctr)->location;
    outArray[ctr]["location"] = factory.createCharArray(currentElement_location);
    // serial_number
    auto currentElement_serial_number = (msg + ctr)->serial_number;
    outArray[ctr]["serial_number"] = factory.createCharArray(currentElement_serial_number);
    }
    return std::move(outArray);
  } 
class SENSOR_MSGS_EXPORT ros2_sensor_msgs_BatteryState_message : public ROS2MsgElementInterfaceFactory {
  public:
    virtual ~ros2_sensor_msgs_BatteryState_message(){}
    virtual std::shared_ptr<MATLABPublisherInterface> generatePublisherInterface(ElementType /*type*/);
    virtual std::shared_ptr<MATLABSubscriberInterface> generateSubscriberInterface(ElementType /*type*/);
    virtual std::shared_ptr<void> generateCppMessage(ElementType /*type*/, const matlab::data::StructArray& /* arr */, MultiLibLoader /* loader */, std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* /*commonObjMap*/);
    virtual matlab::data::StructArray generateMLMessage(ElementType  /*type*/ ,void*  /* msg */, MultiLibLoader /* loader */ , std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* /*commonObjMap*/);
};  
  std::shared_ptr<MATLABPublisherInterface> 
          ros2_sensor_msgs_BatteryState_message::generatePublisherInterface(ElementType /*type*/){
    return std::make_shared<ROS2PublisherImpl<sensor_msgs::msg::BatteryState,ros2_sensor_msgs_msg_BatteryState_common>>();
  }
  std::shared_ptr<MATLABSubscriberInterface> 
         ros2_sensor_msgs_BatteryState_message::generateSubscriberInterface(ElementType /*type*/){
    return std::make_shared<ROS2SubscriberImpl<sensor_msgs::msg::BatteryState,ros2_sensor_msgs_msg_BatteryState_common>>();
  }
  std::shared_ptr<void> ros2_sensor_msgs_BatteryState_message::generateCppMessage(ElementType /*type*/, 
                                           const matlab::data::StructArray& arr,
                                           MultiLibLoader loader,
                                           std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* commonObjMap){
    auto msg = std::make_shared<sensor_msgs::msg::BatteryState>();
    ros2_sensor_msgs_msg_BatteryState_common commonObj;
    commonObj.mCommonObjMap = commonObjMap;
    commonObj.copy_from_struct(msg.get(), arr[0], loader);
    return msg;
  }
  matlab::data::StructArray ros2_sensor_msgs_BatteryState_message::generateMLMessage(ElementType  /*type*/ ,
                                                    void*  msg ,
                                                    MultiLibLoader  loader ,
                                                    std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>*  commonObjMap ){
    ros2_sensor_msgs_msg_BatteryState_common commonObj;	
    commonObj.mCommonObjMap = commonObjMap;	
    MDFactory_T factory;
    return commonObj.get_arr(factory, (sensor_msgs::msg::BatteryState*)msg, loader);			
 }
#include "class_loader/register_macro.hpp"
// Register the component with class_loader.
// This acts as a sort of entry point, allowing the component to be discoverable when its library
// is being loaded into a running process.
CLASS_LOADER_REGISTER_CLASS(ros2_sensor_msgs_msg_BatteryState_common, MATLABROS2MsgInterface<sensor_msgs::msg::BatteryState>)
CLASS_LOADER_REGISTER_CLASS(ros2_sensor_msgs_BatteryState_message, ROS2MsgElementInterfaceFactory)
#ifdef _MSC_VER
#pragma warning(pop)
#else
#pragma GCC diagnostic pop
#endif //_MSC_VER