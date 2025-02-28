// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from drone_c:msg/Motors.idl
// generated code does not contain a copyright notice

#ifndef DRONE_C__MSG__DETAIL__MOTORS__STRUCT_H_
#define DRONE_C__MSG__DETAIL__MOTORS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/Motors in the package drone_c.
typedef struct drone_c__msg__Motors
{
  float front_right;
  float back_right;
  float front_left;
  float back_left;
} drone_c__msg__Motors;

// Struct for a sequence of drone_c__msg__Motors.
typedef struct drone_c__msg__Motors__Sequence
{
  drone_c__msg__Motors * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} drone_c__msg__Motors__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // DRONE_C__MSG__DETAIL__MOTORS__STRUCT_H_
