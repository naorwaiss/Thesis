// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from drone_c:msg/PidConsts.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "drone_c/msg/detail/pid_consts__struct.hpp"
#include "rosidl_typesupport_introspection_cpp/field_types.hpp"
#include "rosidl_typesupport_introspection_cpp/identifier.hpp"
#include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace drone_c
{

namespace msg
{

namespace rosidl_typesupport_introspection_cpp
{

void PidConsts_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) drone_c::msg::PidConsts(_init);
}

void PidConsts_fini_function(void * message_memory)
{
  auto typed_message = static_cast<drone_c::msg::PidConsts *>(message_memory);
  typed_message->~PidConsts();
}

size_t size_function__PidConsts__rate_pitch(const void * untyped_member)
{
  (void)untyped_member;
  return 3;
}

const void * get_const_function__PidConsts__rate_pitch(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::array<float, 3> *>(untyped_member);
  return &member[index];
}

void * get_function__PidConsts__rate_pitch(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::array<float, 3> *>(untyped_member);
  return &member[index];
}

void fetch_function__PidConsts__rate_pitch(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const float *>(
    get_const_function__PidConsts__rate_pitch(untyped_member, index));
  auto & value = *reinterpret_cast<float *>(untyped_value);
  value = item;
}

void assign_function__PidConsts__rate_pitch(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<float *>(
    get_function__PidConsts__rate_pitch(untyped_member, index));
  const auto & value = *reinterpret_cast<const float *>(untyped_value);
  item = value;
}

size_t size_function__PidConsts__rate_roll(const void * untyped_member)
{
  (void)untyped_member;
  return 3;
}

const void * get_const_function__PidConsts__rate_roll(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::array<float, 3> *>(untyped_member);
  return &member[index];
}

void * get_function__PidConsts__rate_roll(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::array<float, 3> *>(untyped_member);
  return &member[index];
}

void fetch_function__PidConsts__rate_roll(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const float *>(
    get_const_function__PidConsts__rate_roll(untyped_member, index));
  auto & value = *reinterpret_cast<float *>(untyped_value);
  value = item;
}

void assign_function__PidConsts__rate_roll(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<float *>(
    get_function__PidConsts__rate_roll(untyped_member, index));
  const auto & value = *reinterpret_cast<const float *>(untyped_value);
  item = value;
}

size_t size_function__PidConsts__stablize_pitch(const void * untyped_member)
{
  (void)untyped_member;
  return 3;
}

const void * get_const_function__PidConsts__stablize_pitch(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::array<float, 3> *>(untyped_member);
  return &member[index];
}

void * get_function__PidConsts__stablize_pitch(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::array<float, 3> *>(untyped_member);
  return &member[index];
}

void fetch_function__PidConsts__stablize_pitch(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const float *>(
    get_const_function__PidConsts__stablize_pitch(untyped_member, index));
  auto & value = *reinterpret_cast<float *>(untyped_value);
  value = item;
}

void assign_function__PidConsts__stablize_pitch(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<float *>(
    get_function__PidConsts__stablize_pitch(untyped_member, index));
  const auto & value = *reinterpret_cast<const float *>(untyped_value);
  item = value;
}

size_t size_function__PidConsts__stablize_roll(const void * untyped_member)
{
  (void)untyped_member;
  return 3;
}

const void * get_const_function__PidConsts__stablize_roll(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::array<float, 3> *>(untyped_member);
  return &member[index];
}

void * get_function__PidConsts__stablize_roll(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::array<float, 3> *>(untyped_member);
  return &member[index];
}

void fetch_function__PidConsts__stablize_roll(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const float *>(
    get_const_function__PidConsts__stablize_roll(untyped_member, index));
  auto & value = *reinterpret_cast<float *>(untyped_value);
  value = item;
}

void assign_function__PidConsts__stablize_roll(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<float *>(
    get_function__PidConsts__stablize_roll(untyped_member, index));
  const auto & value = *reinterpret_cast<const float *>(untyped_value);
  item = value;
}

size_t size_function__PidConsts__rate_yaw(const void * untyped_member)
{
  (void)untyped_member;
  return 3;
}

const void * get_const_function__PidConsts__rate_yaw(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::array<float, 3> *>(untyped_member);
  return &member[index];
}

void * get_function__PidConsts__rate_yaw(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::array<float, 3> *>(untyped_member);
  return &member[index];
}

void fetch_function__PidConsts__rate_yaw(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const float *>(
    get_const_function__PidConsts__rate_yaw(untyped_member, index));
  auto & value = *reinterpret_cast<float *>(untyped_value);
  value = item;
}

void assign_function__PidConsts__rate_yaw(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<float *>(
    get_function__PidConsts__rate_yaw(untyped_member, index));
  const auto & value = *reinterpret_cast<const float *>(untyped_value);
  item = value;
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember PidConsts_message_member_array[5] = {
  {
    "rate_pitch",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    3,  // array size
    false,  // is upper bound
    offsetof(drone_c::msg::PidConsts, rate_pitch),  // bytes offset in struct
    nullptr,  // default value
    size_function__PidConsts__rate_pitch,  // size() function pointer
    get_const_function__PidConsts__rate_pitch,  // get_const(index) function pointer
    get_function__PidConsts__rate_pitch,  // get(index) function pointer
    fetch_function__PidConsts__rate_pitch,  // fetch(index, &value) function pointer
    assign_function__PidConsts__rate_pitch,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "rate_roll",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    3,  // array size
    false,  // is upper bound
    offsetof(drone_c::msg::PidConsts, rate_roll),  // bytes offset in struct
    nullptr,  // default value
    size_function__PidConsts__rate_roll,  // size() function pointer
    get_const_function__PidConsts__rate_roll,  // get_const(index) function pointer
    get_function__PidConsts__rate_roll,  // get(index) function pointer
    fetch_function__PidConsts__rate_roll,  // fetch(index, &value) function pointer
    assign_function__PidConsts__rate_roll,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "stablize_pitch",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    3,  // array size
    false,  // is upper bound
    offsetof(drone_c::msg::PidConsts, stablize_pitch),  // bytes offset in struct
    nullptr,  // default value
    size_function__PidConsts__stablize_pitch,  // size() function pointer
    get_const_function__PidConsts__stablize_pitch,  // get_const(index) function pointer
    get_function__PidConsts__stablize_pitch,  // get(index) function pointer
    fetch_function__PidConsts__stablize_pitch,  // fetch(index, &value) function pointer
    assign_function__PidConsts__stablize_pitch,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "stablize_roll",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    3,  // array size
    false,  // is upper bound
    offsetof(drone_c::msg::PidConsts, stablize_roll),  // bytes offset in struct
    nullptr,  // default value
    size_function__PidConsts__stablize_roll,  // size() function pointer
    get_const_function__PidConsts__stablize_roll,  // get_const(index) function pointer
    get_function__PidConsts__stablize_roll,  // get(index) function pointer
    fetch_function__PidConsts__stablize_roll,  // fetch(index, &value) function pointer
    assign_function__PidConsts__stablize_roll,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "rate_yaw",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    3,  // array size
    false,  // is upper bound
    offsetof(drone_c::msg::PidConsts, rate_yaw),  // bytes offset in struct
    nullptr,  // default value
    size_function__PidConsts__rate_yaw,  // size() function pointer
    get_const_function__PidConsts__rate_yaw,  // get_const(index) function pointer
    get_function__PidConsts__rate_yaw,  // get(index) function pointer
    fetch_function__PidConsts__rate_yaw,  // fetch(index, &value) function pointer
    assign_function__PidConsts__rate_yaw,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers PidConsts_message_members = {
  "drone_c::msg",  // message namespace
  "PidConsts",  // message name
  5,  // number of fields
  sizeof(drone_c::msg::PidConsts),
  PidConsts_message_member_array,  // message members
  PidConsts_init_function,  // function to initialize message memory (memory has to be allocated)
  PidConsts_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t PidConsts_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &PidConsts_message_members,
  get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace msg

}  // namespace drone_c


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<drone_c::msg::PidConsts>()
{
  return &::drone_c::msg::rosidl_typesupport_introspection_cpp::PidConsts_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, drone_c, msg, PidConsts)() {
  return &::drone_c::msg::rosidl_typesupport_introspection_cpp::PidConsts_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
