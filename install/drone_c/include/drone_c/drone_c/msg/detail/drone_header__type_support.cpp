// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from drone_c:msg/DroneHeader.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "drone_c/msg/detail/drone_header__struct.hpp"
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

void DroneHeader_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) drone_c::msg::DroneHeader(_init);
}

void DroneHeader_fini_function(void * message_memory)
{
  auto typed_message = static_cast<drone_c::msg::DroneHeader *>(message_memory);
  typed_message->~DroneHeader();
}

size_t size_function__DroneHeader__mac_adress(const void * untyped_member)
{
  (void)untyped_member;
  return 6;
}

const void * get_const_function__DroneHeader__mac_adress(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::array<int32_t, 6> *>(untyped_member);
  return &member[index];
}

void * get_function__DroneHeader__mac_adress(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::array<int32_t, 6> *>(untyped_member);
  return &member[index];
}

void fetch_function__DroneHeader__mac_adress(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const int32_t *>(
    get_const_function__DroneHeader__mac_adress(untyped_member, index));
  auto & value = *reinterpret_cast<int32_t *>(untyped_value);
  value = item;
}

void assign_function__DroneHeader__mac_adress(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<int32_t *>(
    get_function__DroneHeader__mac_adress(untyped_member, index));
  const auto & value = *reinterpret_cast<const int32_t *>(untyped_value);
  item = value;
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember DroneHeader_message_member_array[3] = {
  {
    "mac_adress",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    6,  // array size
    false,  // is upper bound
    offsetof(drone_c::msg::DroneHeader, mac_adress),  // bytes offset in struct
    nullptr,  // default value
    size_function__DroneHeader__mac_adress,  // size() function pointer
    get_const_function__DroneHeader__mac_adress,  // get_const(index) function pointer
    get_function__DroneHeader__mac_adress,  // get(index) function pointer
    fetch_function__DroneHeader__mac_adress,  // fetch(index, &value) function pointer
    assign_function__DroneHeader__mac_adress,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "drone_mode",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(drone_c::msg::DroneHeader, drone_mode),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "drone_filter",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(drone_c::msg::DroneHeader, drone_filter),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers DroneHeader_message_members = {
  "drone_c::msg",  // message namespace
  "DroneHeader",  // message name
  3,  // number of fields
  sizeof(drone_c::msg::DroneHeader),
  DroneHeader_message_member_array,  // message members
  DroneHeader_init_function,  // function to initialize message memory (memory has to be allocated)
  DroneHeader_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t DroneHeader_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &DroneHeader_message_members,
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
get_message_type_support_handle<drone_c::msg::DroneHeader>()
{
  return &::drone_c::msg::rosidl_typesupport_introspection_cpp::DroneHeader_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, drone_c, msg, DroneHeader)() {
  return &::drone_c::msg::rosidl_typesupport_introspection_cpp::DroneHeader_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
