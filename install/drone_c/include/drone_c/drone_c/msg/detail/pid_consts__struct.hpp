// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from drone_c:msg/PidConsts.idl
// generated code does not contain a copyright notice

#ifndef DRONE_C__MSG__DETAIL__PID_CONSTS__STRUCT_HPP_
#define DRONE_C__MSG__DETAIL__PID_CONSTS__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__drone_c__msg__PidConsts __attribute__((deprecated))
#else
# define DEPRECATED__drone_c__msg__PidConsts __declspec(deprecated)
#endif

namespace drone_c
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct PidConsts_
{
  using Type = PidConsts_<ContainerAllocator>;

  explicit PidConsts_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      std::fill<typename std::array<float, 3>::iterator, float>(this->rate_pitch.begin(), this->rate_pitch.end(), 0.0f);
      std::fill<typename std::array<float, 3>::iterator, float>(this->rate_roll.begin(), this->rate_roll.end(), 0.0f);
      std::fill<typename std::array<float, 3>::iterator, float>(this->stablize_pitch.begin(), this->stablize_pitch.end(), 0.0f);
      std::fill<typename std::array<float, 3>::iterator, float>(this->stablize_roll.begin(), this->stablize_roll.end(), 0.0f);
      std::fill<typename std::array<float, 3>::iterator, float>(this->rate_yaw.begin(), this->rate_yaw.end(), 0.0f);
    }
  }

  explicit PidConsts_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : rate_pitch(_alloc),
    rate_roll(_alloc),
    stablize_pitch(_alloc),
    stablize_roll(_alloc),
    rate_yaw(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      std::fill<typename std::array<float, 3>::iterator, float>(this->rate_pitch.begin(), this->rate_pitch.end(), 0.0f);
      std::fill<typename std::array<float, 3>::iterator, float>(this->rate_roll.begin(), this->rate_roll.end(), 0.0f);
      std::fill<typename std::array<float, 3>::iterator, float>(this->stablize_pitch.begin(), this->stablize_pitch.end(), 0.0f);
      std::fill<typename std::array<float, 3>::iterator, float>(this->stablize_roll.begin(), this->stablize_roll.end(), 0.0f);
      std::fill<typename std::array<float, 3>::iterator, float>(this->rate_yaw.begin(), this->rate_yaw.end(), 0.0f);
    }
  }

  // field types and members
  using _rate_pitch_type =
    std::array<float, 3>;
  _rate_pitch_type rate_pitch;
  using _rate_roll_type =
    std::array<float, 3>;
  _rate_roll_type rate_roll;
  using _stablize_pitch_type =
    std::array<float, 3>;
  _stablize_pitch_type stablize_pitch;
  using _stablize_roll_type =
    std::array<float, 3>;
  _stablize_roll_type stablize_roll;
  using _rate_yaw_type =
    std::array<float, 3>;
  _rate_yaw_type rate_yaw;

  // setters for named parameter idiom
  Type & set__rate_pitch(
    const std::array<float, 3> & _arg)
  {
    this->rate_pitch = _arg;
    return *this;
  }
  Type & set__rate_roll(
    const std::array<float, 3> & _arg)
  {
    this->rate_roll = _arg;
    return *this;
  }
  Type & set__stablize_pitch(
    const std::array<float, 3> & _arg)
  {
    this->stablize_pitch = _arg;
    return *this;
  }
  Type & set__stablize_roll(
    const std::array<float, 3> & _arg)
  {
    this->stablize_roll = _arg;
    return *this;
  }
  Type & set__rate_yaw(
    const std::array<float, 3> & _arg)
  {
    this->rate_yaw = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    drone_c::msg::PidConsts_<ContainerAllocator> *;
  using ConstRawPtr =
    const drone_c::msg::PidConsts_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<drone_c::msg::PidConsts_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<drone_c::msg::PidConsts_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      drone_c::msg::PidConsts_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<drone_c::msg::PidConsts_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      drone_c::msg::PidConsts_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<drone_c::msg::PidConsts_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<drone_c::msg::PidConsts_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<drone_c::msg::PidConsts_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__drone_c__msg__PidConsts
    std::shared_ptr<drone_c::msg::PidConsts_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__drone_c__msg__PidConsts
    std::shared_ptr<drone_c::msg::PidConsts_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const PidConsts_ & other) const
  {
    if (this->rate_pitch != other.rate_pitch) {
      return false;
    }
    if (this->rate_roll != other.rate_roll) {
      return false;
    }
    if (this->stablize_pitch != other.stablize_pitch) {
      return false;
    }
    if (this->stablize_roll != other.stablize_roll) {
      return false;
    }
    if (this->rate_yaw != other.rate_yaw) {
      return false;
    }
    return true;
  }
  bool operator!=(const PidConsts_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct PidConsts_

// alias to use template instance with default allocator
using PidConsts =
  drone_c::msg::PidConsts_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace drone_c

#endif  // DRONE_C__MSG__DETAIL__PID_CONSTS__STRUCT_HPP_
