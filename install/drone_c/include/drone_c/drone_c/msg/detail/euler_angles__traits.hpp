// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from drone_c:msg/EulerAngles.idl
// generated code does not contain a copyright notice

#ifndef DRONE_C__MSG__DETAIL__EULER_ANGLES__TRAITS_HPP_
#define DRONE_C__MSG__DETAIL__EULER_ANGLES__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "drone_c/msg/detail/euler_angles__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace drone_c
{

namespace msg
{

inline void to_flow_style_yaml(
  const EulerAngles & msg,
  std::ostream & out)
{
  out << "{";
  // member: pitch
  {
    out << "pitch: ";
    rosidl_generator_traits::value_to_yaml(msg.pitch, out);
    out << ", ";
  }

  // member: roll
  {
    out << "roll: ";
    rosidl_generator_traits::value_to_yaml(msg.roll, out);
    out << ", ";
  }

  // member: yaw
  {
    out << "yaw: ";
    rosidl_generator_traits::value_to_yaml(msg.yaw, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const EulerAngles & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: pitch
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "pitch: ";
    rosidl_generator_traits::value_to_yaml(msg.pitch, out);
    out << "\n";
  }

  // member: roll
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "roll: ";
    rosidl_generator_traits::value_to_yaml(msg.roll, out);
    out << "\n";
  }

  // member: yaw
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "yaw: ";
    rosidl_generator_traits::value_to_yaml(msg.yaw, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const EulerAngles & msg, bool use_flow_style = false)
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
  const drone_c::msg::EulerAngles & msg,
  std::ostream & out, size_t indentation = 0)
{
  drone_c::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use drone_c::msg::to_yaml() instead")]]
inline std::string to_yaml(const drone_c::msg::EulerAngles & msg)
{
  return drone_c::msg::to_yaml(msg);
}

template<>
inline const char * data_type<drone_c::msg::EulerAngles>()
{
  return "drone_c::msg::EulerAngles";
}

template<>
inline const char * name<drone_c::msg::EulerAngles>()
{
  return "drone_c/msg/EulerAngles";
}

template<>
struct has_fixed_size<drone_c::msg::EulerAngles>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<drone_c::msg::EulerAngles>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<drone_c::msg::EulerAngles>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // DRONE_C__MSG__DETAIL__EULER_ANGLES__TRAITS_HPP_
