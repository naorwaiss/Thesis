// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from ground_bot:msg/Pwm.idl
// generated code does not contain a copyright notice

#ifndef GROUND_BOT__MSG__DETAIL__PWM__TRAITS_HPP_
#define GROUND_BOT__MSG__DETAIL__PWM__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "ground_bot/msg/detail/pwm__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace ground_bot
{

namespace msg
{

inline void to_flow_style_yaml(
  const Pwm & msg,
  std::ostream & out)
{
  out << "{";
  // member: pwm_left_motor
  {
    out << "pwm_left_motor: ";
    rosidl_generator_traits::value_to_yaml(msg.pwm_left_motor, out);
    out << ", ";
  }

  // member: pwm_right_motor
  {
    out << "pwm_right_motor: ";
    rosidl_generator_traits::value_to_yaml(msg.pwm_right_motor, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Pwm & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: pwm_left_motor
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "pwm_left_motor: ";
    rosidl_generator_traits::value_to_yaml(msg.pwm_left_motor, out);
    out << "\n";
  }

  // member: pwm_right_motor
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "pwm_right_motor: ";
    rosidl_generator_traits::value_to_yaml(msg.pwm_right_motor, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Pwm & msg, bool use_flow_style = false)
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

}  // namespace ground_bot

namespace rosidl_generator_traits
{

[[deprecated("use ground_bot::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const ground_bot::msg::Pwm & msg,
  std::ostream & out, size_t indentation = 0)
{
  ground_bot::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use ground_bot::msg::to_yaml() instead")]]
inline std::string to_yaml(const ground_bot::msg::Pwm & msg)
{
  return ground_bot::msg::to_yaml(msg);
}

template<>
inline const char * data_type<ground_bot::msg::Pwm>()
{
  return "ground_bot::msg::Pwm";
}

template<>
inline const char * name<ground_bot::msg::Pwm>()
{
  return "ground_bot/msg/Pwm";
}

template<>
struct has_fixed_size<ground_bot::msg::Pwm>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<ground_bot::msg::Pwm>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<ground_bot::msg::Pwm>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // GROUND_BOT__MSG__DETAIL__PWM__TRAITS_HPP_
