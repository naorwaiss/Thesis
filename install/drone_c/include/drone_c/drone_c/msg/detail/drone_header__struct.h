// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from drone_c:msg/DroneHeader.idl
// generated code does not contain a copyright notice

#ifndef DRONE_C__MSG__DETAIL__DRONE_HEADER__STRUCT_H_
#define DRONE_C__MSG__DETAIL__DRONE_HEADER__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/DroneHeader in the package drone_c.
typedef struct drone_c__msg__DroneHeader
{
  int32_t mac_adress[6];
  int32_t drone_mode;
  int32_t drone_filter;
} drone_c__msg__DroneHeader;

// Struct for a sequence of drone_c__msg__DroneHeader.
typedef struct drone_c__msg__DroneHeader__Sequence
{
  drone_c__msg__DroneHeader * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} drone_c__msg__DroneHeader__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // DRONE_C__MSG__DETAIL__DRONE_HEADER__STRUCT_H_
