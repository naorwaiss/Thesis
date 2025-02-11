// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from ground_bot:msg/MotorData.idl
// generated code does not contain a copyright notice

#ifndef GROUND_BOT__MSG__DETAIL__MOTOR_DATA__STRUCT_H_
#define GROUND_BOT__MSG__DETAIL__MOTOR_DATA__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/MotorData in the package ground_bot.
typedef struct ground_bot__msg__MotorData
{
  float left_motor;
  float right_motor;
} ground_bot__msg__MotorData;

// Struct for a sequence of ground_bot__msg__MotorData.
typedef struct ground_bot__msg__MotorData__Sequence
{
  ground_bot__msg__MotorData * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} ground_bot__msg__MotorData__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // GROUND_BOT__MSG__DETAIL__MOTOR_DATA__STRUCT_H_
