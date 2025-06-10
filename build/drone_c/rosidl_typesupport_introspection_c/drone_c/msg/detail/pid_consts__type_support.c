// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from drone_c:msg/PidConsts.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "drone_c/msg/detail/pid_consts__rosidl_typesupport_introspection_c.h"
#include "drone_c/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "drone_c/msg/detail/pid_consts__functions.h"
#include "drone_c/msg/detail/pid_consts__struct.h"


#ifdef __cplusplus
extern "C"
{
#endif

void drone_c__msg__PidConsts__rosidl_typesupport_introspection_c__PidConsts_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  drone_c__msg__PidConsts__init(message_memory);
}

void drone_c__msg__PidConsts__rosidl_typesupport_introspection_c__PidConsts_fini_function(void * message_memory)
{
  drone_c__msg__PidConsts__fini(message_memory);
}

size_t drone_c__msg__PidConsts__rosidl_typesupport_introspection_c__size_function__PidConsts__rate_pitch(
  const void * untyped_member)
{
  (void)untyped_member;
  return 3;
}

const void * drone_c__msg__PidConsts__rosidl_typesupport_introspection_c__get_const_function__PidConsts__rate_pitch(
  const void * untyped_member, size_t index)
{
  const float * member =
    (const float *)(untyped_member);
  return &member[index];
}

void * drone_c__msg__PidConsts__rosidl_typesupport_introspection_c__get_function__PidConsts__rate_pitch(
  void * untyped_member, size_t index)
{
  float * member =
    (float *)(untyped_member);
  return &member[index];
}

void drone_c__msg__PidConsts__rosidl_typesupport_introspection_c__fetch_function__PidConsts__rate_pitch(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const float * item =
    ((const float *)
    drone_c__msg__PidConsts__rosidl_typesupport_introspection_c__get_const_function__PidConsts__rate_pitch(untyped_member, index));
  float * value =
    (float *)(untyped_value);
  *value = *item;
}

void drone_c__msg__PidConsts__rosidl_typesupport_introspection_c__assign_function__PidConsts__rate_pitch(
  void * untyped_member, size_t index, const void * untyped_value)
{
  float * item =
    ((float *)
    drone_c__msg__PidConsts__rosidl_typesupport_introspection_c__get_function__PidConsts__rate_pitch(untyped_member, index));
  const float * value =
    (const float *)(untyped_value);
  *item = *value;
}

size_t drone_c__msg__PidConsts__rosidl_typesupport_introspection_c__size_function__PidConsts__rate_roll(
  const void * untyped_member)
{
  (void)untyped_member;
  return 3;
}

const void * drone_c__msg__PidConsts__rosidl_typesupport_introspection_c__get_const_function__PidConsts__rate_roll(
  const void * untyped_member, size_t index)
{
  const float * member =
    (const float *)(untyped_member);
  return &member[index];
}

void * drone_c__msg__PidConsts__rosidl_typesupport_introspection_c__get_function__PidConsts__rate_roll(
  void * untyped_member, size_t index)
{
  float * member =
    (float *)(untyped_member);
  return &member[index];
}

void drone_c__msg__PidConsts__rosidl_typesupport_introspection_c__fetch_function__PidConsts__rate_roll(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const float * item =
    ((const float *)
    drone_c__msg__PidConsts__rosidl_typesupport_introspection_c__get_const_function__PidConsts__rate_roll(untyped_member, index));
  float * value =
    (float *)(untyped_value);
  *value = *item;
}

void drone_c__msg__PidConsts__rosidl_typesupport_introspection_c__assign_function__PidConsts__rate_roll(
  void * untyped_member, size_t index, const void * untyped_value)
{
  float * item =
    ((float *)
    drone_c__msg__PidConsts__rosidl_typesupport_introspection_c__get_function__PidConsts__rate_roll(untyped_member, index));
  const float * value =
    (const float *)(untyped_value);
  *item = *value;
}

size_t drone_c__msg__PidConsts__rosidl_typesupport_introspection_c__size_function__PidConsts__stablize_pitch(
  const void * untyped_member)
{
  (void)untyped_member;
  return 3;
}

const void * drone_c__msg__PidConsts__rosidl_typesupport_introspection_c__get_const_function__PidConsts__stablize_pitch(
  const void * untyped_member, size_t index)
{
  const float * member =
    (const float *)(untyped_member);
  return &member[index];
}

void * drone_c__msg__PidConsts__rosidl_typesupport_introspection_c__get_function__PidConsts__stablize_pitch(
  void * untyped_member, size_t index)
{
  float * member =
    (float *)(untyped_member);
  return &member[index];
}

void drone_c__msg__PidConsts__rosidl_typesupport_introspection_c__fetch_function__PidConsts__stablize_pitch(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const float * item =
    ((const float *)
    drone_c__msg__PidConsts__rosidl_typesupport_introspection_c__get_const_function__PidConsts__stablize_pitch(untyped_member, index));
  float * value =
    (float *)(untyped_value);
  *value = *item;
}

void drone_c__msg__PidConsts__rosidl_typesupport_introspection_c__assign_function__PidConsts__stablize_pitch(
  void * untyped_member, size_t index, const void * untyped_value)
{
  float * item =
    ((float *)
    drone_c__msg__PidConsts__rosidl_typesupport_introspection_c__get_function__PidConsts__stablize_pitch(untyped_member, index));
  const float * value =
    (const float *)(untyped_value);
  *item = *value;
}

size_t drone_c__msg__PidConsts__rosidl_typesupport_introspection_c__size_function__PidConsts__stablize_roll(
  const void * untyped_member)
{
  (void)untyped_member;
  return 3;
}

const void * drone_c__msg__PidConsts__rosidl_typesupport_introspection_c__get_const_function__PidConsts__stablize_roll(
  const void * untyped_member, size_t index)
{
  const float * member =
    (const float *)(untyped_member);
  return &member[index];
}

void * drone_c__msg__PidConsts__rosidl_typesupport_introspection_c__get_function__PidConsts__stablize_roll(
  void * untyped_member, size_t index)
{
  float * member =
    (float *)(untyped_member);
  return &member[index];
}

void drone_c__msg__PidConsts__rosidl_typesupport_introspection_c__fetch_function__PidConsts__stablize_roll(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const float * item =
    ((const float *)
    drone_c__msg__PidConsts__rosidl_typesupport_introspection_c__get_const_function__PidConsts__stablize_roll(untyped_member, index));
  float * value =
    (float *)(untyped_value);
  *value = *item;
}

void drone_c__msg__PidConsts__rosidl_typesupport_introspection_c__assign_function__PidConsts__stablize_roll(
  void * untyped_member, size_t index, const void * untyped_value)
{
  float * item =
    ((float *)
    drone_c__msg__PidConsts__rosidl_typesupport_introspection_c__get_function__PidConsts__stablize_roll(untyped_member, index));
  const float * value =
    (const float *)(untyped_value);
  *item = *value;
}

size_t drone_c__msg__PidConsts__rosidl_typesupport_introspection_c__size_function__PidConsts__rate_yaw(
  const void * untyped_member)
{
  (void)untyped_member;
  return 3;
}

const void * drone_c__msg__PidConsts__rosidl_typesupport_introspection_c__get_const_function__PidConsts__rate_yaw(
  const void * untyped_member, size_t index)
{
  const float * member =
    (const float *)(untyped_member);
  return &member[index];
}

void * drone_c__msg__PidConsts__rosidl_typesupport_introspection_c__get_function__PidConsts__rate_yaw(
  void * untyped_member, size_t index)
{
  float * member =
    (float *)(untyped_member);
  return &member[index];
}

void drone_c__msg__PidConsts__rosidl_typesupport_introspection_c__fetch_function__PidConsts__rate_yaw(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const float * item =
    ((const float *)
    drone_c__msg__PidConsts__rosidl_typesupport_introspection_c__get_const_function__PidConsts__rate_yaw(untyped_member, index));
  float * value =
    (float *)(untyped_value);
  *value = *item;
}

void drone_c__msg__PidConsts__rosidl_typesupport_introspection_c__assign_function__PidConsts__rate_yaw(
  void * untyped_member, size_t index, const void * untyped_value)
{
  float * item =
    ((float *)
    drone_c__msg__PidConsts__rosidl_typesupport_introspection_c__get_function__PidConsts__rate_yaw(untyped_member, index));
  const float * value =
    (const float *)(untyped_value);
  *item = *value;
}

static rosidl_typesupport_introspection_c__MessageMember drone_c__msg__PidConsts__rosidl_typesupport_introspection_c__PidConsts_message_member_array[5] = {
  {
    "rate_pitch",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    3,  // array size
    false,  // is upper bound
    offsetof(drone_c__msg__PidConsts, rate_pitch),  // bytes offset in struct
    NULL,  // default value
    drone_c__msg__PidConsts__rosidl_typesupport_introspection_c__size_function__PidConsts__rate_pitch,  // size() function pointer
    drone_c__msg__PidConsts__rosidl_typesupport_introspection_c__get_const_function__PidConsts__rate_pitch,  // get_const(index) function pointer
    drone_c__msg__PidConsts__rosidl_typesupport_introspection_c__get_function__PidConsts__rate_pitch,  // get(index) function pointer
    drone_c__msg__PidConsts__rosidl_typesupport_introspection_c__fetch_function__PidConsts__rate_pitch,  // fetch(index, &value) function pointer
    drone_c__msg__PidConsts__rosidl_typesupport_introspection_c__assign_function__PidConsts__rate_pitch,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "rate_roll",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    3,  // array size
    false,  // is upper bound
    offsetof(drone_c__msg__PidConsts, rate_roll),  // bytes offset in struct
    NULL,  // default value
    drone_c__msg__PidConsts__rosidl_typesupport_introspection_c__size_function__PidConsts__rate_roll,  // size() function pointer
    drone_c__msg__PidConsts__rosidl_typesupport_introspection_c__get_const_function__PidConsts__rate_roll,  // get_const(index) function pointer
    drone_c__msg__PidConsts__rosidl_typesupport_introspection_c__get_function__PidConsts__rate_roll,  // get(index) function pointer
    drone_c__msg__PidConsts__rosidl_typesupport_introspection_c__fetch_function__PidConsts__rate_roll,  // fetch(index, &value) function pointer
    drone_c__msg__PidConsts__rosidl_typesupport_introspection_c__assign_function__PidConsts__rate_roll,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "stablize_pitch",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    3,  // array size
    false,  // is upper bound
    offsetof(drone_c__msg__PidConsts, stablize_pitch),  // bytes offset in struct
    NULL,  // default value
    drone_c__msg__PidConsts__rosidl_typesupport_introspection_c__size_function__PidConsts__stablize_pitch,  // size() function pointer
    drone_c__msg__PidConsts__rosidl_typesupport_introspection_c__get_const_function__PidConsts__stablize_pitch,  // get_const(index) function pointer
    drone_c__msg__PidConsts__rosidl_typesupport_introspection_c__get_function__PidConsts__stablize_pitch,  // get(index) function pointer
    drone_c__msg__PidConsts__rosidl_typesupport_introspection_c__fetch_function__PidConsts__stablize_pitch,  // fetch(index, &value) function pointer
    drone_c__msg__PidConsts__rosidl_typesupport_introspection_c__assign_function__PidConsts__stablize_pitch,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "stablize_roll",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    3,  // array size
    false,  // is upper bound
    offsetof(drone_c__msg__PidConsts, stablize_roll),  // bytes offset in struct
    NULL,  // default value
    drone_c__msg__PidConsts__rosidl_typesupport_introspection_c__size_function__PidConsts__stablize_roll,  // size() function pointer
    drone_c__msg__PidConsts__rosidl_typesupport_introspection_c__get_const_function__PidConsts__stablize_roll,  // get_const(index) function pointer
    drone_c__msg__PidConsts__rosidl_typesupport_introspection_c__get_function__PidConsts__stablize_roll,  // get(index) function pointer
    drone_c__msg__PidConsts__rosidl_typesupport_introspection_c__fetch_function__PidConsts__stablize_roll,  // fetch(index, &value) function pointer
    drone_c__msg__PidConsts__rosidl_typesupport_introspection_c__assign_function__PidConsts__stablize_roll,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "rate_yaw",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    3,  // array size
    false,  // is upper bound
    offsetof(drone_c__msg__PidConsts, rate_yaw),  // bytes offset in struct
    NULL,  // default value
    drone_c__msg__PidConsts__rosidl_typesupport_introspection_c__size_function__PidConsts__rate_yaw,  // size() function pointer
    drone_c__msg__PidConsts__rosidl_typesupport_introspection_c__get_const_function__PidConsts__rate_yaw,  // get_const(index) function pointer
    drone_c__msg__PidConsts__rosidl_typesupport_introspection_c__get_function__PidConsts__rate_yaw,  // get(index) function pointer
    drone_c__msg__PidConsts__rosidl_typesupport_introspection_c__fetch_function__PidConsts__rate_yaw,  // fetch(index, &value) function pointer
    drone_c__msg__PidConsts__rosidl_typesupport_introspection_c__assign_function__PidConsts__rate_yaw,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers drone_c__msg__PidConsts__rosidl_typesupport_introspection_c__PidConsts_message_members = {
  "drone_c__msg",  // message namespace
  "PidConsts",  // message name
  5,  // number of fields
  sizeof(drone_c__msg__PidConsts),
  drone_c__msg__PidConsts__rosidl_typesupport_introspection_c__PidConsts_message_member_array,  // message members
  drone_c__msg__PidConsts__rosidl_typesupport_introspection_c__PidConsts_init_function,  // function to initialize message memory (memory has to be allocated)
  drone_c__msg__PidConsts__rosidl_typesupport_introspection_c__PidConsts_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t drone_c__msg__PidConsts__rosidl_typesupport_introspection_c__PidConsts_message_type_support_handle = {
  0,
  &drone_c__msg__PidConsts__rosidl_typesupport_introspection_c__PidConsts_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_drone_c
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, drone_c, msg, PidConsts)() {
  if (!drone_c__msg__PidConsts__rosidl_typesupport_introspection_c__PidConsts_message_type_support_handle.typesupport_identifier) {
    drone_c__msg__PidConsts__rosidl_typesupport_introspection_c__PidConsts_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &drone_c__msg__PidConsts__rosidl_typesupport_introspection_c__PidConsts_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
