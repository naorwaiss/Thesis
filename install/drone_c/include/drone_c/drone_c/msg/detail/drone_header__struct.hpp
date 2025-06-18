// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from drone_c:msg/DroneHeader.idl
// generated code does not contain a copyright notice

#ifndef DRONE_C__MSG__DETAIL__DRONE_HEADER__STRUCT_HPP_
#define DRONE_C__MSG__DETAIL__DRONE_HEADER__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__drone_c__msg__DroneHeader __attribute__((deprecated))
#else
# define DEPRECATED__drone_c__msg__DroneHeader __declspec(deprecated)
#endif

namespace drone_c
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct DroneHeader_
{
  using Type = DroneHeader_<ContainerAllocator>;

  explicit DroneHeader_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      std::fill<typename std::array<int32_t, 6>::iterator, int32_t>(this->mac_adress.begin(), this->mac_adress.end(), 0l);
      this->drone_mode = 0l;
      this->drone_filter = 0l;
    }
  }

  explicit DroneHeader_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : mac_adress(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      std::fill<typename std::array<int32_t, 6>::iterator, int32_t>(this->mac_adress.begin(), this->mac_adress.end(), 0l);
      this->drone_mode = 0l;
      this->drone_filter = 0l;
    }
  }

  // field types and members
  using _mac_adress_type =
    std::array<int32_t, 6>;
  _mac_adress_type mac_adress;
  using _drone_mode_type =
    int32_t;
  _drone_mode_type drone_mode;
  using _drone_filter_type =
    int32_t;
  _drone_filter_type drone_filter;

  // setters for named parameter idiom
  Type & set__mac_adress(
    const std::array<int32_t, 6> & _arg)
  {
    this->mac_adress = _arg;
    return *this;
  }
  Type & set__drone_mode(
    const int32_t & _arg)
  {
    this->drone_mode = _arg;
    return *this;
  }
  Type & set__drone_filter(
    const int32_t & _arg)
  {
    this->drone_filter = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    drone_c::msg::DroneHeader_<ContainerAllocator> *;
  using ConstRawPtr =
    const drone_c::msg::DroneHeader_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<drone_c::msg::DroneHeader_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<drone_c::msg::DroneHeader_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      drone_c::msg::DroneHeader_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<drone_c::msg::DroneHeader_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      drone_c::msg::DroneHeader_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<drone_c::msg::DroneHeader_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<drone_c::msg::DroneHeader_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<drone_c::msg::DroneHeader_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__drone_c__msg__DroneHeader
    std::shared_ptr<drone_c::msg::DroneHeader_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__drone_c__msg__DroneHeader
    std::shared_ptr<drone_c::msg::DroneHeader_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const DroneHeader_ & other) const
  {
    if (this->mac_adress != other.mac_adress) {
      return false;
    }
    if (this->drone_mode != other.drone_mode) {
      return false;
    }
    if (this->drone_filter != other.drone_filter) {
      return false;
    }
    return true;
  }
  bool operator!=(const DroneHeader_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct DroneHeader_

// alias to use template instance with default allocator
using DroneHeader =
  drone_c::msg::DroneHeader_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace drone_c

#endif  // DRONE_C__MSG__DETAIL__DRONE_HEADER__STRUCT_HPP_
