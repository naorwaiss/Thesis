// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from hamma_bot:msg/MotorData.idl
// generated code does not contain a copyright notice

#ifndef HAMMA_BOT__MSG__DETAIL__MOTOR_DATA__TRAITS_HPP_
#define HAMMA_BOT__MSG__DETAIL__MOTOR_DATA__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "hamma_bot/msg/detail/motor_data__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace hamma_bot
{

namespace msg
{

inline void to_flow_style_yaml(
  const MotorData & msg,
  std::ostream & out)
{
  out << "{";
  // member: left_motor
  {
    out << "left_motor: ";
    rosidl_generator_traits::value_to_yaml(msg.left_motor, out);
    out << ", ";
  }

  // member: right_motor
  {
    out << "right_motor: ";
    rosidl_generator_traits::value_to_yaml(msg.right_motor, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const MotorData & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: left_motor
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "left_motor: ";
    rosidl_generator_traits::value_to_yaml(msg.left_motor, out);
    out << "\n";
  }

  // member: right_motor
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "right_motor: ";
    rosidl_generator_traits::value_to_yaml(msg.right_motor, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const MotorData & msg, bool use_flow_style = false)
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

}  // namespace hamma_bot

namespace rosidl_generator_traits
{

[[deprecated("use hamma_bot::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const hamma_bot::msg::MotorData & msg,
  std::ostream & out, size_t indentation = 0)
{
  hamma_bot::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use hamma_bot::msg::to_yaml() instead")]]
inline std::string to_yaml(const hamma_bot::msg::MotorData & msg)
{
  return hamma_bot::msg::to_yaml(msg);
}

template<>
inline const char * data_type<hamma_bot::msg::MotorData>()
{
  return "hamma_bot::msg::MotorData";
}

template<>
inline const char * name<hamma_bot::msg::MotorData>()
{
  return "hamma_bot/msg/MotorData";
}

template<>
struct has_fixed_size<hamma_bot::msg::MotorData>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<hamma_bot::msg::MotorData>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<hamma_bot::msg::MotorData>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // HAMMA_BOT__MSG__DETAIL__MOTOR_DATA__TRAITS_HPP_
