// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from drone_c:msg/ImuFilter.idl
// generated code does not contain a copyright notice

#ifndef DRONE_C__MSG__DETAIL__IMU_FILTER__STRUCT_H_
#define DRONE_C__MSG__DETAIL__IMU_FILTER__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/ImuFilter in the package drone_c.
typedef struct drone_c__msg__ImuFilter
{
  float acc_lpf_x;
  float acc_lpf_y;
  float acc_lpf_z;
  float gyro_hpf_x;
  float gyro_hpf_y;
  float gyro_hpf_z;
  float gyro_lpf_x;
  float gyro_lpf_y;
  float gyro_lpf_z;
  float mag_lpf_x;
  float mag_lpf_y;
  float mag_lpf_z;
} drone_c__msg__ImuFilter;

// Struct for a sequence of drone_c__msg__ImuFilter.
typedef struct drone_c__msg__ImuFilter__Sequence
{
  drone_c__msg__ImuFilter * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} drone_c__msg__ImuFilter__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // DRONE_C__MSG__DETAIL__IMU_FILTER__STRUCT_H_
