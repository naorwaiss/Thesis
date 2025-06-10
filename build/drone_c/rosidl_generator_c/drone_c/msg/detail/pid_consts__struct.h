// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from drone_c:msg/PidConsts.idl
// generated code does not contain a copyright notice

#ifndef DRONE_C__MSG__DETAIL__PID_CONSTS__STRUCT_H_
#define DRONE_C__MSG__DETAIL__PID_CONSTS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/PidConsts in the package drone_c.
typedef struct drone_c__msg__PidConsts
{
  float rate_pitch[3];
  float rate_roll[3];
  float stablize_pitch[3];
  float stablize_roll[3];
  float rate_yaw[3];
} drone_c__msg__PidConsts;

// Struct for a sequence of drone_c__msg__PidConsts.
typedef struct drone_c__msg__PidConsts__Sequence
{
  drone_c__msg__PidConsts * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} drone_c__msg__PidConsts__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // DRONE_C__MSG__DETAIL__PID_CONSTS__STRUCT_H_
