// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__type_support.cpp.em
// with input from action_msgs:msg/GoalStatus.idl
// generated code does not contain a copyright notice
#include "action_msgs/msg/detail/goal_status__rosidl_typesupport_fastrtps_cpp.hpp"
#include "action_msgs/msg/detail/goal_status__struct.hpp"

#include <limits>
#include <stdexcept>
#include <string>
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_fastrtps_cpp/identifier.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_fastrtps_cpp/wstring_conversion.hpp"
#include "fastcdr/Cdr.h"


// forward declaration of message dependencies and their conversion functions
namespace action_msgs
{
namespace msg
{
namespace typesupport_fastrtps_cpp
{
bool cdr_serialize(
  const action_msgs::msg::GoalInfo &,
  eprosima::fastcdr::Cdr &);
bool cdr_deserialize(
  eprosima::fastcdr::Cdr &,
  action_msgs::msg::GoalInfo &);
size_t get_serialized_size(
  const action_msgs::msg::GoalInfo &,
  size_t current_alignment);
size_t
max_serialized_size_GoalInfo(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);
}  // namespace typesupport_fastrtps_cpp
}  // namespace msg
}  // namespace action_msgs


namespace action_msgs
{

namespace msg
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_action_msgs
cdr_serialize(
  const action_msgs::msg::GoalStatus & ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Member: goal_info
  action_msgs::msg::typesupport_fastrtps_cpp::cdr_serialize(
    ros_message.goal_info,
    cdr);
  // Member: status
  cdr << ros_message.status;
  return true;
}

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_action_msgs
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  action_msgs::msg::GoalStatus & ros_message)
{
  // Member: goal_info
  action_msgs::msg::typesupport_fastrtps_cpp::cdr_deserialize(
    cdr, ros_message.goal_info);

  // Member: status
  cdr >> ros_message.status;

  return true;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_action_msgs
get_serialized_size(
  const action_msgs::msg::GoalStatus & ros_message,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Member: goal_info

  current_alignment +=
    action_msgs::msg::typesupport_fastrtps_cpp::get_serialized_size(
    ros_message.goal_info, current_alignment);
  // Member: status
  {
    size_t item_size = sizeof(ros_message.status);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_action_msgs
max_serialized_size_GoalStatus(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  full_bounded = true;
  is_plain = true;


  // Member: goal_info
  {
    size_t array_size = 1;


    for (size_t index = 0; index < array_size; ++index) {
      bool inner_full_bounded;
      bool inner_is_plain;
      current_alignment +=
        action_msgs::msg::typesupport_fastrtps_cpp::max_serialized_size_GoalInfo(
        inner_full_bounded, inner_is_plain, current_alignment);
      full_bounded &= inner_full_bounded;
      is_plain &= inner_is_plain;
    }
  }

  // Member: status
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint8_t);
  }

  return current_alignment - initial_alignment;
}

static bool _GoalStatus__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  auto typed_message =
    static_cast<const action_msgs::msg::GoalStatus *>(
    untyped_ros_message);
  return cdr_serialize(*typed_message, cdr);
}

static bool _GoalStatus__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  auto typed_message =
    static_cast<action_msgs::msg::GoalStatus *>(
    untyped_ros_message);
  return cdr_deserialize(cdr, *typed_message);
}

static uint32_t _GoalStatus__get_serialized_size(
  const void * untyped_ros_message)
{
  auto typed_message =
    static_cast<const action_msgs::msg::GoalStatus *>(
    untyped_ros_message);
  return static_cast<uint32_t>(get_serialized_size(*typed_message, 0));
}

static size_t _GoalStatus__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_GoalStatus(full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}

static message_type_support_callbacks_t _GoalStatus__callbacks = {
  "action_msgs::msg",
  "GoalStatus",
  _GoalStatus__cdr_serialize,
  _GoalStatus__cdr_deserialize,
  _GoalStatus__get_serialized_size,
  _GoalStatus__max_serialized_size
};

static rosidl_message_type_support_t _GoalStatus__handle = {
  rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
  &_GoalStatus__callbacks,
  get_message_typesupport_handle_function,
};

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace action_msgs

namespace rosidl_typesupport_fastrtps_cpp
{

template<>
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_EXPORT_action_msgs
const rosidl_message_type_support_t *
get_message_type_support_handle<action_msgs::msg::GoalStatus>()
{
  return &action_msgs::msg::typesupport_fastrtps_cpp::_GoalStatus__handle;
}

}  // namespace rosidl_typesupport_fastrtps_cpp

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, action_msgs, msg, GoalStatus)() {
  return &action_msgs::msg::typesupport_fastrtps_cpp::_GoalStatus__handle;
}

#ifdef __cplusplus
}
#endif
