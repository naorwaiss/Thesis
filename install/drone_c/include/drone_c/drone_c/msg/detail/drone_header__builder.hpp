// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from drone_c:msg/DroneHeader.idl
// generated code does not contain a copyright notice

#ifndef DRONE_C__MSG__DETAIL__DRONE_HEADER__BUILDER_HPP_
#define DRONE_C__MSG__DETAIL__DRONE_HEADER__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "drone_c/msg/detail/drone_header__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace drone_c
{

namespace msg
{

namespace builder
{

class Init_DroneHeader_drone_filter
{
public:
  explicit Init_DroneHeader_drone_filter(::drone_c::msg::DroneHeader & msg)
  : msg_(msg)
  {}
  ::drone_c::msg::DroneHeader drone_filter(::drone_c::msg::DroneHeader::_drone_filter_type arg)
  {
    msg_.drone_filter = std::move(arg);
    return std::move(msg_);
  }

private:
  ::drone_c::msg::DroneHeader msg_;
};

class Init_DroneHeader_drone_mode
{
public:
  explicit Init_DroneHeader_drone_mode(::drone_c::msg::DroneHeader & msg)
  : msg_(msg)
  {}
  Init_DroneHeader_drone_filter drone_mode(::drone_c::msg::DroneHeader::_drone_mode_type arg)
  {
    msg_.drone_mode = std::move(arg);
    return Init_DroneHeader_drone_filter(msg_);
  }

private:
  ::drone_c::msg::DroneHeader msg_;
};

class Init_DroneHeader_mac_adress
{
public:
  Init_DroneHeader_mac_adress()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_DroneHeader_drone_mode mac_adress(::drone_c::msg::DroneHeader::_mac_adress_type arg)
  {
    msg_.mac_adress = std::move(arg);
    return Init_DroneHeader_drone_mode(msg_);
  }

private:
  ::drone_c::msg::DroneHeader msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::drone_c::msg::DroneHeader>()
{
  return drone_c::msg::builder::Init_DroneHeader_mac_adress();
}

}  // namespace drone_c

#endif  // DRONE_C__MSG__DETAIL__DRONE_HEADER__BUILDER_HPP_
