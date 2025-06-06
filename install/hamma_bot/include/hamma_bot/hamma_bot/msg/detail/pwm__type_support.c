// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from hamma_bot:msg/Pwm.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "hamma_bot/msg/detail/pwm__rosidl_typesupport_introspection_c.h"
#include "hamma_bot/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "hamma_bot/msg/detail/pwm__functions.h"
#include "hamma_bot/msg/detail/pwm__struct.h"


#ifdef __cplusplus
extern "C"
{
#endif

void hamma_bot__msg__Pwm__rosidl_typesupport_introspection_c__Pwm_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  hamma_bot__msg__Pwm__init(message_memory);
}

void hamma_bot__msg__Pwm__rosidl_typesupport_introspection_c__Pwm_fini_function(void * message_memory)
{
  hamma_bot__msg__Pwm__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember hamma_bot__msg__Pwm__rosidl_typesupport_introspection_c__Pwm_message_member_array[2] = {
  {
    "pwm_left_motor",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(hamma_bot__msg__Pwm, pwm_left_motor),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "pwm_right_motor",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(hamma_bot__msg__Pwm, pwm_right_motor),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers hamma_bot__msg__Pwm__rosidl_typesupport_introspection_c__Pwm_message_members = {
  "hamma_bot__msg",  // message namespace
  "Pwm",  // message name
  2,  // number of fields
  sizeof(hamma_bot__msg__Pwm),
  hamma_bot__msg__Pwm__rosidl_typesupport_introspection_c__Pwm_message_member_array,  // message members
  hamma_bot__msg__Pwm__rosidl_typesupport_introspection_c__Pwm_init_function,  // function to initialize message memory (memory has to be allocated)
  hamma_bot__msg__Pwm__rosidl_typesupport_introspection_c__Pwm_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t hamma_bot__msg__Pwm__rosidl_typesupport_introspection_c__Pwm_message_type_support_handle = {
  0,
  &hamma_bot__msg__Pwm__rosidl_typesupport_introspection_c__Pwm_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_hamma_bot
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, hamma_bot, msg, Pwm)() {
  if (!hamma_bot__msg__Pwm__rosidl_typesupport_introspection_c__Pwm_message_type_support_handle.typesupport_identifier) {
    hamma_bot__msg__Pwm__rosidl_typesupport_introspection_c__Pwm_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &hamma_bot__msg__Pwm__rosidl_typesupport_introspection_c__Pwm_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
