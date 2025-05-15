// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__rosidl_typesupport_fastrtps_cpp.hpp.em
// with input from hamma_bot:msg/MotorData.idl
// generated code does not contain a copyright notice

#ifndef HAMMA_BOT__MSG__DETAIL__MOTOR_DATA__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
#define HAMMA_BOT__MSG__DETAIL__MOTOR_DATA__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_interface/macros.h"
#include "hamma_bot/msg/rosidl_typesupport_fastrtps_cpp__visibility_control.h"
#include "hamma_bot/msg/detail/motor_data__struct.hpp"

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

namespace hamma_bot
{

namespace msg
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_hamma_bot
cdr_serialize(
  const hamma_bot::msg::MotorData & ros_message,
  eprosima::fastcdr::Cdr & cdr);

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_hamma_bot
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  hamma_bot::msg::MotorData & ros_message);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_hamma_bot
get_serialized_size(
  const hamma_bot::msg::MotorData & ros_message,
  size_t current_alignment);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_hamma_bot
max_serialized_size_MotorData(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace hamma_bot

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_hamma_bot
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, hamma_bot, msg, MotorData)();

#ifdef __cplusplus
}
#endif

#endif  // HAMMA_BOT__MSG__DETAIL__MOTOR_DATA__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
