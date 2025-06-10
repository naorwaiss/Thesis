// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from drone_c:msg/PidConsts.idl
// generated code does not contain a copyright notice

#ifndef DRONE_C__MSG__DETAIL__PID_CONSTS__TRAITS_HPP_
#define DRONE_C__MSG__DETAIL__PID_CONSTS__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "drone_c/msg/detail/pid_consts__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace drone_c
{

namespace msg
{

inline void to_flow_style_yaml(
  const PidConsts & msg,
  std::ostream & out)
{
  out << "{";
  // member: rate_pitch
  {
    if (msg.rate_pitch.size() == 0) {
      out << "rate_pitch: []";
    } else {
      out << "rate_pitch: [";
      size_t pending_items = msg.rate_pitch.size();
      for (auto item : msg.rate_pitch) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: rate_roll
  {
    if (msg.rate_roll.size() == 0) {
      out << "rate_roll: []";
    } else {
      out << "rate_roll: [";
      size_t pending_items = msg.rate_roll.size();
      for (auto item : msg.rate_roll) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: stablize_pitch
  {
    if (msg.stablize_pitch.size() == 0) {
      out << "stablize_pitch: []";
    } else {
      out << "stablize_pitch: [";
      size_t pending_items = msg.stablize_pitch.size();
      for (auto item : msg.stablize_pitch) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: stablize_roll
  {
    if (msg.stablize_roll.size() == 0) {
      out << "stablize_roll: []";
    } else {
      out << "stablize_roll: [";
      size_t pending_items = msg.stablize_roll.size();
      for (auto item : msg.stablize_roll) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: rate_yaw
  {
    if (msg.rate_yaw.size() == 0) {
      out << "rate_yaw: []";
    } else {
      out << "rate_yaw: [";
      size_t pending_items = msg.rate_yaw.size();
      for (auto item : msg.rate_yaw) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const PidConsts & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: rate_pitch
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.rate_pitch.size() == 0) {
      out << "rate_pitch: []\n";
    } else {
      out << "rate_pitch:\n";
      for (auto item : msg.rate_pitch) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: rate_roll
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.rate_roll.size() == 0) {
      out << "rate_roll: []\n";
    } else {
      out << "rate_roll:\n";
      for (auto item : msg.rate_roll) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: stablize_pitch
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.stablize_pitch.size() == 0) {
      out << "stablize_pitch: []\n";
    } else {
      out << "stablize_pitch:\n";
      for (auto item : msg.stablize_pitch) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: stablize_roll
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.stablize_roll.size() == 0) {
      out << "stablize_roll: []\n";
    } else {
      out << "stablize_roll:\n";
      for (auto item : msg.stablize_roll) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: rate_yaw
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.rate_yaw.size() == 0) {
      out << "rate_yaw: []\n";
    } else {
      out << "rate_yaw:\n";
      for (auto item : msg.rate_yaw) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const PidConsts & msg, bool use_flow_style = false)
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
  const drone_c::msg::PidConsts & msg,
  std::ostream & out, size_t indentation = 0)
{
  drone_c::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use drone_c::msg::to_yaml() instead")]]
inline std::string to_yaml(const drone_c::msg::PidConsts & msg)
{
  return drone_c::msg::to_yaml(msg);
}

template<>
inline const char * data_type<drone_c::msg::PidConsts>()
{
  return "drone_c::msg::PidConsts";
}

template<>
inline const char * name<drone_c::msg::PidConsts>()
{
  return "drone_c/msg/PidConsts";
}

template<>
struct has_fixed_size<drone_c::msg::PidConsts>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<drone_c::msg::PidConsts>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<drone_c::msg::PidConsts>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // DRONE_C__MSG__DETAIL__PID_CONSTS__TRAITS_HPP_
