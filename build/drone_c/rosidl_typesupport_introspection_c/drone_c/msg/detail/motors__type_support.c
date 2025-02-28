// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from drone_c:msg/Motors.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "drone_c/msg/detail/motors__rosidl_typesupport_introspection_c.h"
#include "drone_c/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "drone_c/msg/detail/motors__functions.h"
#include "drone_c/msg/detail/motors__struct.h"


#ifdef __cplusplus
extern "C"
{
#endif

void drone_c__msg__Motors__rosidl_typesupport_introspection_c__Motors_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  drone_c__msg__Motors__init(message_memory);
}

void drone_c__msg__Motors__rosidl_typesupport_introspection_c__Motors_fini_function(void * message_memory)
{
  drone_c__msg__Motors__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember drone_c__msg__Motors__rosidl_typesupport_introspection_c__Motors_message_member_array[4] = {
  {
    "front_right",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(drone_c__msg__Motors, front_right),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "back_right",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(drone_c__msg__Motors, back_right),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "front_left",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(drone_c__msg__Motors, front_left),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "back_left",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(drone_c__msg__Motors, back_left),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers drone_c__msg__Motors__rosidl_typesupport_introspection_c__Motors_message_members = {
  "drone_c__msg",  // message namespace
  "Motors",  // message name
  4,  // number of fields
  sizeof(drone_c__msg__Motors),
  drone_c__msg__Motors__rosidl_typesupport_introspection_c__Motors_message_member_array,  // message members
  drone_c__msg__Motors__rosidl_typesupport_introspection_c__Motors_init_function,  // function to initialize message memory (memory has to be allocated)
  drone_c__msg__Motors__rosidl_typesupport_introspection_c__Motors_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t drone_c__msg__Motors__rosidl_typesupport_introspection_c__Motors_message_type_support_handle = {
  0,
  &drone_c__msg__Motors__rosidl_typesupport_introspection_c__Motors_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_drone_c
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, drone_c, msg, Motors)() {
  if (!drone_c__msg__Motors__rosidl_typesupport_introspection_c__Motors_message_type_support_handle.typesupport_identifier) {
    drone_c__msg__Motors__rosidl_typesupport_introspection_c__Motors_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &drone_c__msg__Motors__rosidl_typesupport_introspection_c__Motors_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
