// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from drone_c:msg/ImuFilter.idl
// generated code does not contain a copyright notice

#ifndef DRONE_C__MSG__DETAIL__IMU_FILTER__TRAITS_HPP_
#define DRONE_C__MSG__DETAIL__IMU_FILTER__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "drone_c/msg/detail/imu_filter__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace drone_c
{

namespace msg
{

inline void to_flow_style_yaml(
  const ImuFilter & msg,
  std::ostream & out)
{
  out << "{";
  // member: acc_lpf_x
  {
    out << "acc_lpf_x: ";
    rosidl_generator_traits::value_to_yaml(msg.acc_lpf_x, out);
    out << ", ";
  }

  // member: acc_lpf_y
  {
    out << "acc_lpf_y: ";
    rosidl_generator_traits::value_to_yaml(msg.acc_lpf_y, out);
    out << ", ";
  }

  // member: acc_lpf_z
  {
    out << "acc_lpf_z: ";
    rosidl_generator_traits::value_to_yaml(msg.acc_lpf_z, out);
    out << ", ";
  }

  // member: gyro_hpf_x
  {
    out << "gyro_hpf_x: ";
    rosidl_generator_traits::value_to_yaml(msg.gyro_hpf_x, out);
    out << ", ";
  }

  // member: gyro_hpf_y
  {
    out << "gyro_hpf_y: ";
    rosidl_generator_traits::value_to_yaml(msg.gyro_hpf_y, out);
    out << ", ";
  }

  // member: gyro_hpf_z
  {
    out << "gyro_hpf_z: ";
    rosidl_generator_traits::value_to_yaml(msg.gyro_hpf_z, out);
    out << ", ";
  }

  // member: gyro_lpf_x
  {
    out << "gyro_lpf_x: ";
    rosidl_generator_traits::value_to_yaml(msg.gyro_lpf_x, out);
    out << ", ";
  }

  // member: gyro_lpf_y
  {
    out << "gyro_lpf_y: ";
    rosidl_generator_traits::value_to_yaml(msg.gyro_lpf_y, out);
    out << ", ";
  }

  // member: gyro_lpf_z
  {
    out << "gyro_lpf_z: ";
    rosidl_generator_traits::value_to_yaml(msg.gyro_lpf_z, out);
    out << ", ";
  }

  // member: mag_lpf_x
  {
    out << "mag_lpf_x: ";
    rosidl_generator_traits::value_to_yaml(msg.mag_lpf_x, out);
    out << ", ";
  }

  // member: mag_lpf_y
  {
    out << "mag_lpf_y: ";
    rosidl_generator_traits::value_to_yaml(msg.mag_lpf_y, out);
    out << ", ";
  }

  // member: mag_lpf_z
  {
    out << "mag_lpf_z: ";
    rosidl_generator_traits::value_to_yaml(msg.mag_lpf_z, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const ImuFilter & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: acc_lpf_x
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "acc_lpf_x: ";
    rosidl_generator_traits::value_to_yaml(msg.acc_lpf_x, out);
    out << "\n";
  }

  // member: acc_lpf_y
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "acc_lpf_y: ";
    rosidl_generator_traits::value_to_yaml(msg.acc_lpf_y, out);
    out << "\n";
  }

  // member: acc_lpf_z
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "acc_lpf_z: ";
    rosidl_generator_traits::value_to_yaml(msg.acc_lpf_z, out);
    out << "\n";
  }

  // member: gyro_hpf_x
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "gyro_hpf_x: ";
    rosidl_generator_traits::value_to_yaml(msg.gyro_hpf_x, out);
    out << "\n";
  }

  // member: gyro_hpf_y
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "gyro_hpf_y: ";
    rosidl_generator_traits::value_to_yaml(msg.gyro_hpf_y, out);
    out << "\n";
  }

  // member: gyro_hpf_z
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "gyro_hpf_z: ";
    rosidl_generator_traits::value_to_yaml(msg.gyro_hpf_z, out);
    out << "\n";
  }

  // member: gyro_lpf_x
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "gyro_lpf_x: ";
    rosidl_generator_traits::value_to_yaml(msg.gyro_lpf_x, out);
    out << "\n";
  }

  // member: gyro_lpf_y
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "gyro_lpf_y: ";
    rosidl_generator_traits::value_to_yaml(msg.gyro_lpf_y, out);
    out << "\n";
  }

  // member: gyro_lpf_z
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "gyro_lpf_z: ";
    rosidl_generator_traits::value_to_yaml(msg.gyro_lpf_z, out);
    out << "\n";
  }

  // member: mag_lpf_x
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "mag_lpf_x: ";
    rosidl_generator_traits::value_to_yaml(msg.mag_lpf_x, out);
    out << "\n";
  }

  // member: mag_lpf_y
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "mag_lpf_y: ";
    rosidl_generator_traits::value_to_yaml(msg.mag_lpf_y, out);
    out << "\n";
  }

  // member: mag_lpf_z
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "mag_lpf_z: ";
    rosidl_generator_traits::value_to_yaml(msg.mag_lpf_z, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const ImuFilter & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace drone_c

namespace rosidl_generator_traits
{

[[deprecated("use drone_c::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const drone_c::msg::ImuFilter & msg,
  std::ostream & out, size_t indentation = 0)
{
  drone_c::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use drone_c::msg::to_yaml() instead")]]
inline std::string to_yaml(const drone_c::msg::ImuFilter & msg)
{
  return drone_c::msg::to_yaml(msg);
}

template<>
inline const char * data_type<drone_c::msg::ImuFilter>()
{
  return "drone_c::msg::ImuFilter";
}

template<>
inline const char * name<drone_c::msg::ImuFilter>()
{
  return "drone_c/msg/ImuFilter";
}

template<>
struct has_fixed_size<drone_c::msg::ImuFilter>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<drone_c::msg::ImuFilter>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<drone_c::msg::ImuFilter>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // DRONE_C__MSG__DETAIL__IMU_FILTER__TRAITS_HPP_
