// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from drone_c:msg/Pid.idl
// generated code does not contain a copyright notice

#ifndef DRONE_C__MSG__DETAIL__PID__STRUCT_HPP_
#define DRONE_C__MSG__DETAIL__PID__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__drone_c__msg__Pid __attribute__((deprecated))
#else
# define DEPRECATED__drone_c__msg__Pid __declspec(deprecated)
#endif

namespace drone_c
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct Pid_
{
  using Type = Pid_<ContainerAllocator>;

  explicit Pid_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->error_pitch = 0.0f;
      this->error_roll = 0.0f;
      this->error_yaw = 0.0f;
      this->p_pitch = 0.0f;
      this->p_roll = 0.0f;
      this->p_yaw = 0.0f;
      this->i_pitch = 0.0f;
      this->i_roll = 0.0f;
      this->i_yaw = 0.0f;
      this->d_pitch = 0.0f;
      this->d_roll = 0.0f;
      this->d_yaw = 0.0f;
      this->sum_pitch = 0.0f;
      this->sum_roll = 0.0f;
      this->sum_yaw = 0.0f;
    }
  }

  explicit Pid_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->error_pitch = 0.0f;
      this->error_roll = 0.0f;
      this->error_yaw = 0.0f;
      this->p_pitch = 0.0f;
      this->p_roll = 0.0f;
      this->p_yaw = 0.0f;
      this->i_pitch = 0.0f;
      this->i_roll = 0.0f;
      this->i_yaw = 0.0f;
      this->d_pitch = 0.0f;
      this->d_roll = 0.0f;
      this->d_yaw = 0.0f;
      this->sum_pitch = 0.0f;
      this->sum_roll = 0.0f;
      this->sum_yaw = 0.0f;
    }
  }

  // field types and members
  using _error_pitch_type =
    float;
  _error_pitch_type error_pitch;
  using _error_roll_type =
    float;
  _error_roll_type error_roll;
  using _error_yaw_type =
    float;
  _error_yaw_type error_yaw;
  using _p_pitch_type =
    float;
  _p_pitch_type p_pitch;
  using _p_roll_type =
    float;
  _p_roll_type p_roll;
  using _p_yaw_type =
    float;
  _p_yaw_type p_yaw;
  using _i_pitch_type =
    float;
  _i_pitch_type i_pitch;
  using _i_roll_type =
    float;
  _i_roll_type i_roll;
  using _i_yaw_type =
    float;
  _i_yaw_type i_yaw;
  using _d_pitch_type =
    float;
  _d_pitch_type d_pitch;
  using _d_roll_type =
    float;
  _d_roll_type d_roll;
  using _d_yaw_type =
    float;
  _d_yaw_type d_yaw;
  using _sum_pitch_type =
    float;
  _sum_pitch_type sum_pitch;
  using _sum_roll_type =
    float;
  _sum_roll_type sum_roll;
  using _sum_yaw_type =
    float;
  _sum_yaw_type sum_yaw;

  // setters for named parameter idiom
  Type & set__error_pitch(
    const float & _arg)
  {
    this->error_pitch = _arg;
    return *this;
  }
  Type & set__error_roll(
    const float & _arg)
  {
    this->error_roll = _arg;
    return *this;
  }
  Type & set__error_yaw(
    const float & _arg)
  {
    this->error_yaw = _arg;
    return *this;
  }
  Type & set__p_pitch(
    const float & _arg)
  {
    this->p_pitch = _arg;
    return *this;
  }
  Type & set__p_roll(
    const float & _arg)
  {
    this->p_roll = _arg;
    return *this;
  }
  Type & set__p_yaw(
    const float & _arg)
  {
    this->p_yaw = _arg;
    return *this;
  }
  Type & set__i_pitch(
    const float & _arg)
  {
    this->i_pitch = _arg;
    return *this;
  }
  Type & set__i_roll(
    const float & _arg)
  {
    this->i_roll = _arg;
    return *this;
  }
  Type & set__i_yaw(
    const float & _arg)
  {
    this->i_yaw = _arg;
    return *this;
  }
  Type & set__d_pitch(
    const float & _arg)
  {
    this->d_pitch = _arg;
    return *this;
  }
  Type & set__d_roll(
    const float & _arg)
  {
    this->d_roll = _arg;
    return *this;
  }
  Type & set__d_yaw(
    const float & _arg)
  {
    this->d_yaw = _arg;
    return *this;
  }
  Type & set__sum_pitch(
    const float & _arg)
  {
    this->sum_pitch = _arg;
    return *this;
  }
  Type & set__sum_roll(
    const float & _arg)
  {
    this->sum_roll = _arg;
    return *this;
  }
  Type & set__sum_yaw(
    const float & _arg)
  {
    this->sum_yaw = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    drone_c::msg::Pid_<ContainerAllocator> *;
  using ConstRawPtr =
    const drone_c::msg::Pid_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<drone_c::msg::Pid_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<drone_c::msg::Pid_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      drone_c::msg::Pid_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<drone_c::msg::Pid_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      drone_c::msg::Pid_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<drone_c::msg::Pid_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<drone_c::msg::Pid_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<drone_c::msg::Pid_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__drone_c__msg__Pid
    std::shared_ptr<drone_c::msg::Pid_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__drone_c__msg__Pid
    std::shared_ptr<drone_c::msg::Pid_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Pid_ & other) const
  {
    if (this->error_pitch != other.error_pitch) {
      return false;
    }
    if (this->error_roll != other.error_roll) {
      return false;
    }
    if (this->error_yaw != other.error_yaw) {
      return false;
    }
    if (this->p_pitch != other.p_pitch) {
      return false;
    }
    if (this->p_roll != other.p_roll) {
      return false;
    }
    if (this->p_yaw != other.p_yaw) {
      return false;
    }
    if (this->i_pitch != other.i_pitch) {
      return false;
    }
    if (this->i_roll != other.i_roll) {
      return false;
    }
    if (this->i_yaw != other.i_yaw) {
      return false;
    }
    if (this->d_pitch != other.d_pitch) {
      return false;
    }
    if (this->d_roll != other.d_roll) {
      return false;
    }
    if (this->d_yaw != other.d_yaw) {
      return false;
    }
    if (this->sum_pitch != other.sum_pitch) {
      return false;
    }
    if (this->sum_roll != other.sum_roll) {
      return false;
    }
    if (this->sum_yaw != other.sum_yaw) {
      return false;
    }
    return true;
  }
  bool operator!=(const Pid_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Pid_

// alias to use template instance with default allocator
using Pid =
  drone_c::msg::Pid_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace drone_c

#endif  // DRONE_C__MSG__DETAIL__PID__STRUCT_HPP_
