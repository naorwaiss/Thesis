// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__type_support.cpp.em
// with input from drone_c:msg/ImuFilter.idl
// generated code does not contain a copyright notice
#include "drone_c/msg/detail/imu_filter__rosidl_typesupport_fastrtps_cpp.hpp"
#include "drone_c/msg/detail/imu_filter__struct.hpp"

#include <limits>
#include <stdexcept>
#include <string>
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_fastrtps_cpp/identifier.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_fastrtps_cpp/wstring_conversion.hpp"
#include "fastcdr/Cdr.h"


// forward declaration of message dependencies and their conversion functions

namespace drone_c
{

namespace msg
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_drone_c
cdr_serialize(
  const drone_c::msg::ImuFilter & ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Member: acc_lpf_x
  cdr << ros_message.acc_lpf_x;
  // Member: acc_lpf_y
  cdr << ros_message.acc_lpf_y;
  // Member: acc_lpf_z
  cdr << ros_message.acc_lpf_z;
  // Member: gyro_hpf_x
  cdr << ros_message.gyro_hpf_x;
  // Member: gyro_hpf_y
  cdr << ros_message.gyro_hpf_y;
  // Member: gyro_hpf_z
  cdr << ros_message.gyro_hpf_z;
  // Member: gyro_lpf_x
  cdr << ros_message.gyro_lpf_x;
  // Member: gyro_lpf_y
  cdr << ros_message.gyro_lpf_y;
  // Member: gyro_lpf_z
  cdr << ros_message.gyro_lpf_z;
  // Member: mag_lpf_x
  cdr << ros_message.mag_lpf_x;
  // Member: mag_lpf_y
  cdr << ros_message.mag_lpf_y;
  // Member: mag_lpf_z
  cdr << ros_message.mag_lpf_z;
  return true;
}

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_drone_c
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  drone_c::msg::ImuFilter & ros_message)
{
  // Member: acc_lpf_x
  cdr >> ros_message.acc_lpf_x;

  // Member: acc_lpf_y
  cdr >> ros_message.acc_lpf_y;

  // Member: acc_lpf_z
  cdr >> ros_message.acc_lpf_z;

  // Member: gyro_hpf_x
  cdr >> ros_message.gyro_hpf_x;

  // Member: gyro_hpf_y
  cdr >> ros_message.gyro_hpf_y;

  // Member: gyro_hpf_z
  cdr >> ros_message.gyro_hpf_z;

  // Member: gyro_lpf_x
  cdr >> ros_message.gyro_lpf_x;

  // Member: gyro_lpf_y
  cdr >> ros_message.gyro_lpf_y;

  // Member: gyro_lpf_z
  cdr >> ros_message.gyro_lpf_z;

  // Member: mag_lpf_x
  cdr >> ros_message.mag_lpf_x;

  // Member: mag_lpf_y
  cdr >> ros_message.mag_lpf_y;

  // Member: mag_lpf_z
  cdr >> ros_message.mag_lpf_z;

  return true;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_drone_c
get_serialized_size(
  const drone_c::msg::ImuFilter & ros_message,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Member: acc_lpf_x
  {
    size_t item_size = sizeof(ros_message.acc_lpf_x);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: acc_lpf_y
  {
    size_t item_size = sizeof(ros_message.acc_lpf_y);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: acc_lpf_z
  {
    size_t item_size = sizeof(ros_message.acc_lpf_z);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: gyro_hpf_x
  {
    size_t item_size = sizeof(ros_message.gyro_hpf_x);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: gyro_hpf_y
  {
    size_t item_size = sizeof(ros_message.gyro_hpf_y);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: gyro_hpf_z
  {
    size_t item_size = sizeof(ros_message.gyro_hpf_z);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: gyro_lpf_x
  {
    size_t item_size = sizeof(ros_message.gyro_lpf_x);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: gyro_lpf_y
  {
    size_t item_size = sizeof(ros_message.gyro_lpf_y);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: gyro_lpf_z
  {
    size_t item_size = sizeof(ros_message.gyro_lpf_z);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: mag_lpf_x
  {
    size_t item_size = sizeof(ros_message.mag_lpf_x);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: mag_lpf_y
  {
    size_t item_size = sizeof(ros_message.mag_lpf_y);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: mag_lpf_z
  {
    size_t item_size = sizeof(ros_message.mag_lpf_z);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_drone_c
max_serialized_size_ImuFilter(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  size_t last_member_size = 0;
  (void)last_member_size;
  (void)padding;
  (void)wchar_size;

  full_bounded = true;
  is_plain = true;


  // Member: acc_lpf_x
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Member: acc_lpf_y
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Member: acc_lpf_z
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Member: gyro_hpf_x
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Member: gyro_hpf_y
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Member: gyro_hpf_z
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Member: gyro_lpf_x
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Member: gyro_lpf_y
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Member: gyro_lpf_z
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Member: mag_lpf_x
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Member: mag_lpf_y
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Member: mag_lpf_z
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = drone_c::msg::ImuFilter;
    is_plain =
      (
      offsetof(DataType, mag_lpf_z) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static bool _ImuFilter__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  auto typed_message =
    static_cast<const drone_c::msg::ImuFilter *>(
    untyped_ros_message);
  return cdr_serialize(*typed_message, cdr);
}

static bool _ImuFilter__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  auto typed_message =
    static_cast<drone_c::msg::ImuFilter *>(
    untyped_ros_message);
  return cdr_deserialize(cdr, *typed_message);
}

static uint32_t _ImuFilter__get_serialized_size(
  const void * untyped_ros_message)
{
  auto typed_message =
    static_cast<const drone_c::msg::ImuFilter *>(
    untyped_ros_message);
  return static_cast<uint32_t>(get_serialized_size(*typed_message, 0));
}

static size_t _ImuFilter__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_ImuFilter(full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}

static message_type_support_callbacks_t _ImuFilter__callbacks = {
  "drone_c::msg",
  "ImuFilter",
  _ImuFilter__cdr_serialize,
  _ImuFilter__cdr_deserialize,
  _ImuFilter__get_serialized_size,
  _ImuFilter__max_serialized_size
};

static rosidl_message_type_support_t _ImuFilter__handle = {
  rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
  &_ImuFilter__callbacks,
  get_message_typesupport_handle_function,
};

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace drone_c

namespace rosidl_typesupport_fastrtps_cpp
{

template<>
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_EXPORT_drone_c
const rosidl_message_type_support_t *
get_message_type_support_handle<drone_c::msg::ImuFilter>()
{
  return &drone_c::msg::typesupport_fastrtps_cpp::_ImuFilter__handle;
}

}  // namespace rosidl_typesupport_fastrtps_cpp

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, drone_c, msg, ImuFilter)() {
  return &drone_c::msg::typesupport_fastrtps_cpp::_ImuFilter__handle;
}

#ifdef __cplusplus
}
#endif
