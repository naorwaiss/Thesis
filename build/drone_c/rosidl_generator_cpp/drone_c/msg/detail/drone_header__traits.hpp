// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from drone_c:msg/DroneHeader.idl
// generated code does not contain a copyright notice

#ifndef DRONE_C__MSG__DETAIL__DRONE_HEADER__TRAITS_HPP_
#define DRONE_C__MSG__DETAIL__DRONE_HEADER__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "drone_c/msg/detail/drone_header__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace drone_c
{

namespace msg
{

inline void to_flow_style_yaml(
  const DroneHeader & msg,
  std::ostream & out)
{
  out << "{";
  // member: mac_adress
  {
    if (msg.mac_adress.size() == 0) {
      out << "mac_adress: []";
    } else {
      out << "mac_adress: [";
      size_t pending_items = msg.mac_adress.size();
      for (auto item : msg.mac_adress) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: drone_mode
  {
    out << "drone_mode: ";
    rosidl_generator_traits::value_to_yaml(msg.drone_mode, out);
    out << ", ";
  }

  // member: drone_filter
  {
    out << "drone_filter: ";
    rosidl_generator_traits::value_to_yaml(msg.drone_filter, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const DroneHeader & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: mac_adress
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.mac_adress.size() == 0) {
      out << "mac_adress: []\n";
    } else {
      out << "mac_adress:\n";
      for (auto item : msg.mac_adress) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: drone_mode
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "drone_mode: ";
    rosidl_generator_traits::value_to_yaml(msg.drone_mode, out);
    out << "\n";
  }

  // member: drone_filter
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "drone_filter: ";
    rosidl_generator_traits::value_to_yaml(msg.drone_filter, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const DroneHeader & msg, bool use_flow_style = false)
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
  const drone_c::msg::DroneHeader & msg,
  std::ostream & out, size_t indentation = 0)
{
  drone_c::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use drone_c::msg::to_yaml() instead")]]
inline std::string to_yaml(const drone_c::msg::DroneHeader & msg)
{
  return drone_c::msg::to_yaml(msg);
}

template<>
inline const char * data_type<drone_c::msg::DroneHeader>()
{
  return "drone_c::msg::DroneHeader";
}

template<>
inline const char * name<drone_c::msg::DroneHeader>()
{
  return "drone_c/msg/DroneHeader";
}

template<>
struct has_fixed_size<drone_c::msg::DroneHeader>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<drone_c::msg::DroneHeader>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<drone_c::msg::DroneHeader>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // DRONE_C__MSG__DETAIL__DRONE_HEADER__TRAITS_HPP_
