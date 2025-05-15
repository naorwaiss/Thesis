// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from hamma_bot:msg/MotorData.idl
// generated code does not contain a copyright notice

#ifndef HAMMA_BOT__MSG__DETAIL__MOTOR_DATA__STRUCT_H_
#define HAMMA_BOT__MSG__DETAIL__MOTOR_DATA__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/MotorData in the package hamma_bot.
typedef struct hamma_bot__msg__MotorData
{
  float left_motor;
  float right_motor;
} hamma_bot__msg__MotorData;

// Struct for a sequence of hamma_bot__msg__MotorData.
typedef struct hamma_bot__msg__MotorData__Sequence
{
  hamma_bot__msg__MotorData * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} hamma_bot__msg__MotorData__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // HAMMA_BOT__MSG__DETAIL__MOTOR_DATA__STRUCT_H_
