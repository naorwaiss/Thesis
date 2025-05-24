// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__rosidl_typesupport_fastrtps_cpp.hpp.em
// with input from ground_bot:msg/RollerData.idl
// generated code does not contain a copyright notice

#ifndef GROUND_BOT__MSG__DETAIL__ROLLER_DATA__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
#define GROUND_BOT__MSG__DETAIL__ROLLER_DATA__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_interface/macros.h"
#include "ground_bot/msg/rosidl_typesupport_fastrtps_cpp__visibility_control.h"
#include "ground_bot/msg/detail/roller_data__struct.hpp"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

#include "fastcdr/Cdr.h"

namespace ground_bot
{

namespace msg
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_ground_bot
cdr_serialize(
  const ground_bot::msg::RollerData & ros_message,
  eprosima::fastcdr::Cdr & cdr);

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_ground_bot
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  ground_bot::msg::RollerData & ros_message);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_ground_bot
get_serialized_size(
  const ground_bot::msg::RollerData & ros_message,
  size_t current_alignment);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_ground_bot
max_serialized_size_RollerData(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace ground_bot

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_ground_bot
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, ground_bot, msg, RollerData)();

#ifdef __cplusplus
}
#endif

#endif  // GROUND_BOT__MSG__DETAIL__ROLLER_DATA__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
