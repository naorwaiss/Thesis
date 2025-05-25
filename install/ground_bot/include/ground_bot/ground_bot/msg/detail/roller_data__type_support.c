// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from ground_bot:msg/RollerData.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "ground_bot/msg/detail/roller_data__rosidl_typesupport_introspection_c.h"
#include "ground_bot/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "ground_bot/msg/detail/roller_data__functions.h"
#include "ground_bot/msg/detail/roller_data__struct.h"


#ifdef __cplusplus
extern "C"
{
#endif

void ground_bot__msg__RollerData__rosidl_typesupport_introspection_c__RollerData_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  ground_bot__msg__RollerData__init(message_memory);
}

void ground_bot__msg__RollerData__rosidl_typesupport_introspection_c__RollerData_fini_function(void * message_memory)
{
  ground_bot__msg__RollerData__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember ground_bot__msg__RollerData__rosidl_typesupport_introspection_c__RollerData_message_member_array[4] = {
  {
    "tension",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(ground_bot__msg__RollerData, tension),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "dis_tension",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(ground_bot__msg__RollerData, dis_tension),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "error",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(ground_bot__msg__RollerData, error),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "error_sum",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(ground_bot__msg__RollerData, error_sum),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers ground_bot__msg__RollerData__rosidl_typesupport_introspection_c__RollerData_message_members = {
  "ground_bot__msg",  // message namespace
  "RollerData",  // message name
  4,  // number of fields
  sizeof(ground_bot__msg__RollerData),
  ground_bot__msg__RollerData__rosidl_typesupport_introspection_c__RollerData_message_member_array,  // message members
  ground_bot__msg__RollerData__rosidl_typesupport_introspection_c__RollerData_init_function,  // function to initialize message memory (memory has to be allocated)
  ground_bot__msg__RollerData__rosidl_typesupport_introspection_c__RollerData_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t ground_bot__msg__RollerData__rosidl_typesupport_introspection_c__RollerData_message_type_support_handle = {
  0,
  &ground_bot__msg__RollerData__rosidl_typesupport_introspection_c__RollerData_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_ground_bot
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, ground_bot, msg, RollerData)() {
  if (!ground_bot__msg__RollerData__rosidl_typesupport_introspection_c__RollerData_message_type_support_handle.typesupport_identifier) {
    ground_bot__msg__RollerData__rosidl_typesupport_introspection_c__RollerData_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &ground_bot__msg__RollerData__rosidl_typesupport_introspection_c__RollerData_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
