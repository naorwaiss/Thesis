// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from drone_c:msg/ImuFilter.idl
// generated code does not contain a copyright notice

#ifndef DRONE_C__MSG__DETAIL__IMU_FILTER__BUILDER_HPP_
#define DRONE_C__MSG__DETAIL__IMU_FILTER__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "drone_c/msg/detail/imu_filter__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace drone_c
{

namespace msg
{

namespace builder
{

class Init_ImuFilter_mag_lpf_z
{
public:
  explicit Init_ImuFilter_mag_lpf_z(::drone_c::msg::ImuFilter & msg)
  : msg_(msg)
  {}
  ::drone_c::msg::ImuFilter mag_lpf_z(::drone_c::msg::ImuFilter::_mag_lpf_z_type arg)
  {
    msg_.mag_lpf_z = std::move(arg);
    return std::move(msg_);
  }

private:
  ::drone_c::msg::ImuFilter msg_;
};

class Init_ImuFilter_mag_lpf_y
{
public:
  explicit Init_ImuFilter_mag_lpf_y(::drone_c::msg::ImuFilter & msg)
  : msg_(msg)
  {}
  Init_ImuFilter_mag_lpf_z mag_lpf_y(::drone_c::msg::ImuFilter::_mag_lpf_y_type arg)
  {
    msg_.mag_lpf_y = std::move(arg);
    return Init_ImuFilter_mag_lpf_z(msg_);
  }

private:
  ::drone_c::msg::ImuFilter msg_;
};

class Init_ImuFilter_mag_lpf_x
{
public:
  explicit Init_ImuFilter_mag_lpf_x(::drone_c::msg::ImuFilter & msg)
  : msg_(msg)
  {}
  Init_ImuFilter_mag_lpf_y mag_lpf_x(::drone_c::msg::ImuFilter::_mag_lpf_x_type arg)
  {
    msg_.mag_lpf_x = std::move(arg);
    return Init_ImuFilter_mag_lpf_y(msg_);
  }

private:
  ::drone_c::msg::ImuFilter msg_;
};

class Init_ImuFilter_gyro_lpf_z
{
public:
  explicit Init_ImuFilter_gyro_lpf_z(::drone_c::msg::ImuFilter & msg)
  : msg_(msg)
  {}
  Init_ImuFilter_mag_lpf_x gyro_lpf_z(::drone_c::msg::ImuFilter::_gyro_lpf_z_type arg)
  {
    msg_.gyro_lpf_z = std::move(arg);
    return Init_ImuFilter_mag_lpf_x(msg_);
  }

private:
  ::drone_c::msg::ImuFilter msg_;
};

class Init_ImuFilter_gyro_lpf_y
{
public:
  explicit Init_ImuFilter_gyro_lpf_y(::drone_c::msg::ImuFilter & msg)
  : msg_(msg)
  {}
  Init_ImuFilter_gyro_lpf_z gyro_lpf_y(::drone_c::msg::ImuFilter::_gyro_lpf_y_type arg)
  {
    msg_.gyro_lpf_y = std::move(arg);
    return Init_ImuFilter_gyro_lpf_z(msg_);
  }

private:
  ::drone_c::msg::ImuFilter msg_;
};

class Init_ImuFilter_gyro_lpf_x
{
public:
  explicit Init_ImuFilter_gyro_lpf_x(::drone_c::msg::ImuFilter & msg)
  : msg_(msg)
  {}
  Init_ImuFilter_gyro_lpf_y gyro_lpf_x(::drone_c::msg::ImuFilter::_gyro_lpf_x_type arg)
  {
    msg_.gyro_lpf_x = std::move(arg);
    return Init_ImuFilter_gyro_lpf_y(msg_);
  }

private:
  ::drone_c::msg::ImuFilter msg_;
};

class Init_ImuFilter_gyro_hpf_z
{
public:
  explicit Init_ImuFilter_gyro_hpf_z(::drone_c::msg::ImuFilter & msg)
  : msg_(msg)
  {}
  Init_ImuFilter_gyro_lpf_x gyro_hpf_z(::drone_c::msg::ImuFilter::_gyro_hpf_z_type arg)
  {
    msg_.gyro_hpf_z = std::move(arg);
    return Init_ImuFilter_gyro_lpf_x(msg_);
  }

private:
  ::drone_c::msg::ImuFilter msg_;
};

class Init_ImuFilter_gyro_hpf_y
{
public:
  explicit Init_ImuFilter_gyro_hpf_y(::drone_c::msg::ImuFilter & msg)
  : msg_(msg)
  {}
  Init_ImuFilter_gyro_hpf_z gyro_hpf_y(::drone_c::msg::ImuFilter::_gyro_hpf_y_type arg)
  {
    msg_.gyro_hpf_y = std::move(arg);
    return Init_ImuFilter_gyro_hpf_z(msg_);
  }

private:
  ::drone_c::msg::ImuFilter msg_;
};

class Init_ImuFilter_gyro_hpf_x
{
public:
  explicit Init_ImuFilter_gyro_hpf_x(::drone_c::msg::ImuFilter & msg)
  : msg_(msg)
  {}
  Init_ImuFilter_gyro_hpf_y gyro_hpf_x(::drone_c::msg::ImuFilter::_gyro_hpf_x_type arg)
  {
    msg_.gyro_hpf_x = std::move(arg);
    return Init_ImuFilter_gyro_hpf_y(msg_);
  }

private:
  ::drone_c::msg::ImuFilter msg_;
};

class Init_ImuFilter_acc_lpf_z
{
public:
  explicit Init_ImuFilter_acc_lpf_z(::drone_c::msg::ImuFilter & msg)
  : msg_(msg)
  {}
  Init_ImuFilter_gyro_hpf_x acc_lpf_z(::drone_c::msg::ImuFilter::_acc_lpf_z_type arg)
  {
    msg_.acc_lpf_z = std::move(arg);
    return Init_ImuFilter_gyro_hpf_x(msg_);
  }

private:
  ::drone_c::msg::ImuFilter msg_;
};

class Init_ImuFilter_acc_lpf_y
{
public:
  explicit Init_ImuFilter_acc_lpf_y(::drone_c::msg::ImuFilter & msg)
  : msg_(msg)
  {}
  Init_ImuFilter_acc_lpf_z acc_lpf_y(::drone_c::msg::ImuFilter::_acc_lpf_y_type arg)
  {
    msg_.acc_lpf_y = std::move(arg);
    return Init_ImuFilter_acc_lpf_z(msg_);
  }

private:
  ::drone_c::msg::ImuFilter msg_;
};

class Init_ImuFilter_acc_lpf_x
{
public:
  Init_ImuFilter_acc_lpf_x()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ImuFilter_acc_lpf_y acc_lpf_x(::drone_c::msg::ImuFilter::_acc_lpf_x_type arg)
  {
    msg_.acc_lpf_x = std::move(arg);
    return Init_ImuFilter_acc_lpf_y(msg_);
  }

private:
  ::drone_c::msg::ImuFilter msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::drone_c::msg::ImuFilter>()
{
  return drone_c::msg::builder::Init_ImuFilter_acc_lpf_x();
}

}  // namespace drone_c

#endif  // DRONE_C__MSG__DETAIL__IMU_FILTER__BUILDER_HPP_
