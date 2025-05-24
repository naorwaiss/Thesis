// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from ground_bot:msg/RollerData.idl
// generated code does not contain a copyright notice

#ifndef GROUND_BOT__MSG__DETAIL__ROLLER_DATA__STRUCT_H_
#define GROUND_BOT__MSG__DETAIL__ROLLER_DATA__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/RollerData in the package ground_bot.
typedef struct ground_bot__msg__RollerData
{
  float tension;
  float dis_tension;
  float error;
} ground_bot__msg__RollerData;

// Struct for a sequence of ground_bot__msg__RollerData.
typedef struct ground_bot__msg__RollerData__Sequence
{
  ground_bot__msg__RollerData * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} ground_bot__msg__RollerData__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // GROUND_BOT__MSG__DETAIL__ROLLER_DATA__STRUCT_H_
