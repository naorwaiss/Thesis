// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from drone_c:msg/Pid.idl
// generated code does not contain a copyright notice

#ifndef DRONE_C__MSG__DETAIL__PID__TRAITS_HPP_
#define DRONE_C__MSG__DETAIL__PID__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "drone_c/msg/detail/pid__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace drone_c
{

namespace msg
{

inline void to_flow_style_yaml(
  const Pid & msg,
  std::ostream & out)
{
  out << "{";
  // member: error_pitch
  {
    out << "error_pitch: ";
    rosidl_generator_traits::value_to_yaml(msg.error_pitch, out);
    out << ", ";
  }

  // member: error_roll
  {
    out << "error_roll: ";
    rosidl_generator_traits::value_to_yaml(msg.error_roll, out);
    out << ", ";
  }

  // member: error_yaw
  {
    out << "error_yaw: ";
    rosidl_generator_traits::value_to_yaml(msg.error_yaw, out);
    out << ", ";
  }

  // member: p_pitch
  {
    out << "p_pitch: ";
    rosidl_generator_traits::value_to_yaml(msg.p_pitch, out);
    out << ", ";
  }

  // member: p_roll
  {
    out << "p_roll: ";
    rosidl_generator_traits::value_to_yaml(msg.p_roll, out);
    out << ", ";
  }

  // member: p_yaw
  {
    out << "p_yaw: ";
    rosidl_generator_traits::value_to_yaml(msg.p_yaw, out);
    out << ", ";
  }

  // member: i_pitch
  {
    out << "i_pitch: ";
    rosidl_generator_traits::value_to_yaml(msg.i_pitch, out);
    out << ", ";
  }

  // member: i_roll
  {
    out << "i_roll: ";
    rosidl_generator_traits::value_to_yaml(msg.i_roll, out);
    out << ", ";
  }

  // member: i_yaw
  {
    out << "i_yaw: ";
    rosidl_generator_traits::value_to_yaml(msg.i_yaw, out);
    out << ", ";
  }

  // member: d_pitch
  {
    out << "d_pitch: ";
    rosidl_generator_traits::value_to_yaml(msg.d_pitch, out);
    out << ", ";
  }

  // member: d_roll
  {
    out << "d_roll: ";
    rosidl_generator_traits::value_to_yaml(msg.d_roll, out);
    out << ", ";
  }

  // member: d_yaw
  {
    out << "d_yaw: ";
    rosidl_generator_traits::value_to_yaml(msg.d_yaw, out);
    out << ", ";
  }

  // member: sum_pitch
  {
    out << "sum_pitch: ";
    rosidl_generator_traits::value_to_yaml(msg.sum_pitch, out);
    out << ", ";
  }

  // member: sum_roll
  {
    out << "sum_roll: ";
    rosidl_generator_traits::value_to_yaml(msg.sum_roll, out);
    out << ", ";
  }

  // member: sum_yaw
  {
    out << "sum_yaw: ";
    rosidl_generator_traits::value_to_yaml(msg.sum_yaw, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Pid & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: error_pitch
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "error_pitch: ";
    rosidl_generator_traits::value_to_yaml(msg.error_pitch, out);
    out << "\n";
  }

  // member: error_roll
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "error_roll: ";
    rosidl_generator_traits::value_to_yaml(msg.error_roll, out);
    out << "\n";
  }

  // member: error_yaw
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "error_yaw: ";
    rosidl_generator_traits::value_to_yaml(msg.error_yaw, out);
    out << "\n";
  }

  // member: p_pitch
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "p_pitch: ";
    rosidl_generator_traits::value_to_yaml(msg.p_pitch, out);
    out << "\n";
  }

  // member: p_roll
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "p_roll: ";
    rosidl_generator_traits::value_to_yaml(msg.p_roll, out);
    out << "\n";
  }

  // member: p_yaw
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "p_yaw: ";
    rosidl_generator_traits::value_to_yaml(msg.p_yaw, out);
    out << "\n";
  }

  // member: i_pitch
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "i_pitch: ";
    rosidl_generator_traits::value_to_yaml(msg.i_pitch, out);
    out << "\n";
  }

  // member: i_roll
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "i_roll: ";
    rosidl_generator_traits::value_to_yaml(msg.i_roll, out);
    out << "\n";
  }

  // member: i_yaw
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "i_yaw: ";
    rosidl_generator_traits::value_to_yaml(msg.i_yaw, out);
    out << "\n";
  }

  // member: d_pitch
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "d_pitch: ";
    rosidl_generator_traits::value_to_yaml(msg.d_pitch, out);
    out << "\n";
  }

  // member: d_roll
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "d_roll: ";
    rosidl_generator_traits::value_to_yaml(msg.d_roll, out);
    out << "\n";
  }

  // member: d_yaw
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "d_yaw: ";
    rosidl_generator_traits::value_to_yaml(msg.d_yaw, out);
    out << "\n";
  }

  // member: sum_pitch
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "sum_pitch: ";
    rosidl_generator_traits::value_to_yaml(msg.sum_pitch, out);
    out << "\n";
  }

  // member: sum_roll
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "sum_roll: ";
    rosidl_generator_traits::value_to_yaml(msg.sum_roll, out);
    out << "\n";
  }

  // member: sum_yaw
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "sum_yaw: ";
    rosidl_generator_traits::value_to_yaml(msg.sum_yaw, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Pid & msg, bool use_flow_style = false)
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
  const drone_c::msg::Pid & msg,
  std::ostream & out, size_t indentation = 0)
{
  drone_c::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use drone_c::msg::to_yaml() instead")]]
inline std::string to_yaml(const drone_c::msg::Pid & msg)
{
  return drone_c::msg::to_yaml(msg);
}

template<>
inline const char * data_type<drone_c::msg::Pid>()
{
  return "drone_c::msg::Pid";
}

template<>
inline const char * name<drone_c::msg::Pid>()
{
  return "drone_c/msg/Pid";
}

template<>
struct has_fixed_size<drone_c::msg::Pid>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<drone_c::msg::Pid>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<drone_c::msg::Pid>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // DRONE_C__MSG__DETAIL__PID__TRAITS_HPP_
