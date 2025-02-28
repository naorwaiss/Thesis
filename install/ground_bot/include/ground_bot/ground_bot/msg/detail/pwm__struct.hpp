// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from ground_bot:msg/Pwm.idl
// generated code does not contain a copyright notice

#ifndef GROUND_BOT__MSG__DETAIL__PWM__STRUCT_HPP_
#define GROUND_BOT__MSG__DETAIL__PWM__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__ground_bot__msg__Pwm __attribute__((deprecated))
#else
# define DEPRECATED__ground_bot__msg__Pwm __declspec(deprecated)
#endif

namespace ground_bot
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct Pwm_
{
  using Type = Pwm_<ContainerAllocator>;

  explicit Pwm_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->pwm_left_motor = 0l;
      this->pwm_right_motor = 0l;
    }
  }

  explicit Pwm_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->pwm_left_motor = 0l;
      this->pwm_right_motor = 0l;
    }
  }

  // field types and members
  using _pwm_left_motor_type =
    int32_t;
  _pwm_left_motor_type pwm_left_motor;
  using _pwm_right_motor_type =
    int32_t;
  _pwm_right_motor_type pwm_right_motor;

  // setters for named parameter idiom
  Type & set__pwm_left_motor(
    const int32_t & _arg)
  {
    this->pwm_left_motor = _arg;
    return *this;
  }
  Type & set__pwm_right_motor(
    const int32_t & _arg)
  {
    this->pwm_right_motor = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    ground_bot::msg::Pwm_<ContainerAllocator> *;
  using ConstRawPtr =
    const ground_bot::msg::Pwm_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<ground_bot::msg::Pwm_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<ground_bot::msg::Pwm_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      ground_bot::msg::Pwm_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<ground_bot::msg::Pwm_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      ground_bot::msg::Pwm_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<ground_bot::msg::Pwm_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<ground_bot::msg::Pwm_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<ground_bot::msg::Pwm_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__ground_bot__msg__Pwm
    std::shared_ptr<ground_bot::msg::Pwm_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__ground_bot__msg__Pwm
    std::shared_ptr<ground_bot::msg::Pwm_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Pwm_ & other) const
  {
    if (this->pwm_left_motor != other.pwm_left_motor) {
      return false;
    }
    if (this->pwm_right_motor != other.pwm_right_motor) {
      return false;
    }
    return true;
  }
  bool operator!=(const Pwm_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Pwm_

// alias to use template instance with default allocator
using Pwm =
  ground_bot::msg::Pwm_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace ground_bot

#endif  // GROUND_BOT__MSG__DETAIL__PWM__STRUCT_HPP_
