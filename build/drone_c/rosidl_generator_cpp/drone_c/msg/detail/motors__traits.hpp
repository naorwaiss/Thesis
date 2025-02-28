// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from drone_c:msg/Motors.idl
// generated code does not contain a copyright notice

#ifndef DRONE_C__MSG__DETAIL__MOTORS__TRAITS_HPP_
#define DRONE_C__MSG__DETAIL__MOTORS__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "drone_c/msg/detail/motors__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace drone_c
{

namespace msg
{

inline void to_flow_style_yaml(
  const Motors & msg,
  std::ostream & out)
{
  out << "{";
  // member: front_right
  {
    out << "front_right: ";
    rosidl_generator_traits::value_to_yaml(msg.front_right, out);
    out << ", ";
  }

  // member: back_right
  {
    out << "back_right: ";
    rosidl_generator_traits::value_to_yaml(msg.back_right, out);
    out << ", ";
  }

  // member: front_left
  {
    out << "front_left: ";
    rosidl_generator_traits::value_to_yaml(msg.front_left, out);
    out << ", ";
  }

  // member: back_left
  {
    out << "back_left: ";
    rosidl_generator_traits::value_to_yaml(msg.back_left, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Motors & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: front_right
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "front_right: ";
    rosidl_generator_traits::value_to_yaml(msg.front_right, out);
    out << "\n";
  }

  // member: back_right
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "back_right: ";
    rosidl_generator_traits::value_to_yaml(msg.back_right, out);
    out << "\n";
  }

  // member: front_left
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "front_left: ";
    rosidl_generator_traits::value_to_yaml(msg.front_left, out);
    out << "\n";
  }

  // member: back_left
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "back_left: ";
    rosidl_generator_traits::value_to_yaml(msg.back_left, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Motors & msg, bool use_flow_style = false)
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
  const drone_c::msg::Motors & msg,
  std::ostream & out, size_t indentation = 0)
{
  drone_c::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use drone_c::msg::to_yaml() instead")]]
inline std::string to_yaml(const drone_c::msg::Motors & msg)
{
  return drone_c::msg::to_yaml(msg);
}

template<>
inline const char * data_type<drone_c::msg::Motors>()
{
  return "drone_c::msg::Motors";
}

template<>
inline const char * name<drone_c::msg::Motors>()
{
  return "drone_c/msg/Motors";
}

template<>
struct has_fixed_size<drone_c::msg::Motors>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<drone_c::msg::Motors>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<drone_c::msg::Motors>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // DRONE_C__MSG__DETAIL__MOTORS__TRAITS_HPP_
