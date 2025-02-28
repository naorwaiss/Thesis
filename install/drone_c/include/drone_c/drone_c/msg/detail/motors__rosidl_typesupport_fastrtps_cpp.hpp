// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__rosidl_typesupport_fastrtps_cpp.hpp.em
// with input from drone_c:msg/Motors.idl
// generated code does not contain a copyright notice

#ifndef DRONE_C__MSG__DETAIL__MOTORS__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
#define DRONE_C__MSG__DETAIL__MOTORS__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_interface/macros.h"
#include "drone_c/msg/rosidl_typesupport_fastrtps_cpp__visibility_control.h"
#include "drone_c/msg/detail/motors__struct.hpp"

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

namespace drone_c
{

namespace msg
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_drone_c
cdr_serialize(
  const drone_c::msg::Motors & ros_message,
  eprosima::fastcdr::Cdr & cdr);

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_drone_c
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  drone_c::msg::Motors & ros_message);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_drone_c
get_serialized_size(
  const drone_c::msg::Motors & ros_message,
  size_t current_alignment);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_drone_c
max_serialized_size_Motors(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace drone_c

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_drone_c
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, drone_c, msg, Motors)();

#ifdef __cplusplus
}
#endif

#endif  // DRONE_C__MSG__DETAIL__MOTORS__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
