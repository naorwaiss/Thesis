// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from drone_c:msg/EulerAngles.idl
// generated code does not contain a copyright notice

#ifndef DRONE_C__MSG__DETAIL__EULER_ANGLES__STRUCT_H_
#define DRONE_C__MSG__DETAIL__EULER_ANGLES__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/EulerAngles in the package drone_c.
typedef struct drone_c__msg__EulerAngles
{
  float pitch;
  float roll;
  float yaw;
} drone_c__msg__EulerAngles;

// Struct for a sequence of drone_c__msg__EulerAngles.
typedef struct drone_c__msg__EulerAngles__Sequence
{
  drone_c__msg__EulerAngles * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} drone_c__msg__EulerAngles__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // DRONE_C__MSG__DETAIL__EULER_ANGLES__STRUCT_H_
