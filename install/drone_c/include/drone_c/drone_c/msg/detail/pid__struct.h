// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from drone_c:msg/Pid.idl
// generated code does not contain a copyright notice

#ifndef DRONE_C__MSG__DETAIL__PID__STRUCT_H_
#define DRONE_C__MSG__DETAIL__PID__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/Pid in the package drone_c.
/**
  * Definition of the pid_msg
 */
typedef struct drone_c__msg__Pid
{
  float p_pitch;
  float p_roll;
  float p_yaw;
  float i_pitch;
  float i_roll;
  float i_yaw;
  float d_pitch;
  float d_roll;
  float d_yaw;
  float sum_pitch;
  float sum_roll;
  float sum_yaw;
} drone_c__msg__Pid;

// Struct for a sequence of drone_c__msg__Pid.
typedef struct drone_c__msg__Pid__Sequence
{
  drone_c__msg__Pid * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} drone_c__msg__Pid__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // DRONE_C__MSG__DETAIL__PID__STRUCT_H_
