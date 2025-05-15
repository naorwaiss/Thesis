// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from hamma_bot:msg/Pwm.idl
// generated code does not contain a copyright notice

#ifndef HAMMA_BOT__MSG__DETAIL__PWM__STRUCT_H_
#define HAMMA_BOT__MSG__DETAIL__PWM__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/Pwm in the package hamma_bot.
typedef struct hamma_bot__msg__Pwm
{
  int32_t pwm_left_motor;
  int32_t pwm_right_motor;
} hamma_bot__msg__Pwm;

// Struct for a sequence of hamma_bot__msg__Pwm.
typedef struct hamma_bot__msg__Pwm__Sequence
{
  hamma_bot__msg__Pwm * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} hamma_bot__msg__Pwm__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // HAMMA_BOT__MSG__DETAIL__PWM__STRUCT_H_
