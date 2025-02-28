// generated from rosidl_typesupport_fastrtps_c/resource/idl__type_support_c.cpp.em
// with input from drone_c:msg/ImuFilter.idl
// generated code does not contain a copyright notice
#include "drone_c/msg/detail/imu_filter__rosidl_typesupport_fastrtps_c.h"


#include <cassert>
#include <limits>
#include <string>
#include "rosidl_typesupport_fastrtps_c/identifier.h"
#include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "drone_c/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "drone_c/msg/detail/imu_filter__struct.h"
#include "drone_c/msg/detail/imu_filter__functions.h"
#include "fastcdr/Cdr.h"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

// includes and forward declarations of message dependencies and their conversion functions

#if defined(__cplusplus)
extern "C"
{
#endif


// forward declare type support functions


using _ImuFilter__ros_msg_type = drone_c__msg__ImuFilter;

static bool _ImuFilter__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const _ImuFilter__ros_msg_type * ros_message = static_cast<const _ImuFilter__ros_msg_type *>(untyped_ros_message);
  // Field name: acc_lpf_x
  {
    cdr << ros_message->acc_lpf_x;
  }

  // Field name: acc_lpf_y
  {
    cdr << ros_message->acc_lpf_y;
  }

  // Field name: acc_lpf_z
  {
    cdr << ros_message->acc_lpf_z;
  }

  // Field name: gyro_hpf_x
  {
    cdr << ros_message->gyro_hpf_x;
  }

  // Field name: gyro_hpf_y
  {
    cdr << ros_message->gyro_hpf_y;
  }

  // Field name: gyro_hpf_z
  {
    cdr << ros_message->gyro_hpf_z;
  }

  // Field name: gyro_lpf_x
  {
    cdr << ros_message->gyro_lpf_x;
  }

  // Field name: gyro_lpf_y
  {
    cdr << ros_message->gyro_lpf_y;
  }

  // Field name: gyro_lpf_z
  {
    cdr << ros_message->gyro_lpf_z;
  }

  // Field name: mag_lpf_x
  {
    cdr << ros_message->mag_lpf_x;
  }

  // Field name: mag_lpf_y
  {
    cdr << ros_message->mag_lpf_y;
  }

  // Field name: mag_lpf_z
  {
    cdr << ros_message->mag_lpf_z;
  }

  return true;
}

static bool _ImuFilter__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  _ImuFilter__ros_msg_type * ros_message = static_cast<_ImuFilter__ros_msg_type *>(untyped_ros_message);
  // Field name: acc_lpf_x
  {
    cdr >> ros_message->acc_lpf_x;
  }

  // Field name: acc_lpf_y
  {
    cdr >> ros_message->acc_lpf_y;
  }

  // Field name: acc_lpf_z
  {
    cdr >> ros_message->acc_lpf_z;
  }

  // Field name: gyro_hpf_x
  {
    cdr >> ros_message->gyro_hpf_x;
  }

  // Field name: gyro_hpf_y
  {
    cdr >> ros_message->gyro_hpf_y;
  }

  // Field name: gyro_hpf_z
  {
    cdr >> ros_message->gyro_hpf_z;
  }

  // Field name: gyro_lpf_x
  {
    cdr >> ros_message->gyro_lpf_x;
  }

  // Field name: gyro_lpf_y
  {
    cdr >> ros_message->gyro_lpf_y;
  }

  // Field name: gyro_lpf_z
  {
    cdr >> ros_message->gyro_lpf_z;
  }

  // Field name: mag_lpf_x
  {
    cdr >> ros_message->mag_lpf_x;
  }

  // Field name: mag_lpf_y
  {
    cdr >> ros_message->mag_lpf_y;
  }

  // Field name: mag_lpf_z
  {
    cdr >> ros_message->mag_lpf_z;
  }

  return true;
}  // NOLINT(readability/fn_size)

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_drone_c
size_t get_serialized_size_drone_c__msg__ImuFilter(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _ImuFilter__ros_msg_type * ros_message = static_cast<const _ImuFilter__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // field.name acc_lpf_x
  {
    size_t item_size = sizeof(ros_message->acc_lpf_x);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name acc_lpf_y
  {
    size_t item_size = sizeof(ros_message->acc_lpf_y);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name acc_lpf_z
  {
    size_t item_size = sizeof(ros_message->acc_lpf_z);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name gyro_hpf_x
  {
    size_t item_size = sizeof(ros_message->gyro_hpf_x);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name gyro_hpf_y
  {
    size_t item_size = sizeof(ros_message->gyro_hpf_y);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name gyro_hpf_z
  {
    size_t item_size = sizeof(ros_message->gyro_hpf_z);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name gyro_lpf_x
  {
    size_t item_size = sizeof(ros_message->gyro_lpf_x);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name gyro_lpf_y
  {
    size_t item_size = sizeof(ros_message->gyro_lpf_y);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name gyro_lpf_z
  {
    size_t item_size = sizeof(ros_message->gyro_lpf_z);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name mag_lpf_x
  {
    size_t item_size = sizeof(ros_message->mag_lpf_x);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name mag_lpf_y
  {
    size_t item_size = sizeof(ros_message->mag_lpf_y);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name mag_lpf_z
  {
    size_t item_size = sizeof(ros_message->mag_lpf_z);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

static uint32_t _ImuFilter__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_drone_c__msg__ImuFilter(
      untyped_ros_message, 0));
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_drone_c
size_t max_serialized_size_drone_c__msg__ImuFilter(
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

  // member: acc_lpf_x
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // member: acc_lpf_y
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // member: acc_lpf_z
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // member: gyro_hpf_x
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // member: gyro_hpf_y
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // member: gyro_hpf_z
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // member: gyro_lpf_x
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // member: gyro_lpf_y
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // member: gyro_lpf_z
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // member: mag_lpf_x
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // member: mag_lpf_y
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // member: mag_lpf_z
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
    using DataType = drone_c__msg__ImuFilter;
    is_plain =
      (
      offsetof(DataType, mag_lpf_z) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static size_t _ImuFilter__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_drone_c__msg__ImuFilter(
    full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}


static message_type_support_callbacks_t __callbacks_ImuFilter = {
  "drone_c::msg",
  "ImuFilter",
  _ImuFilter__cdr_serialize,
  _ImuFilter__cdr_deserialize,
  _ImuFilter__get_serialized_size,
  _ImuFilter__max_serialized_size
};

static rosidl_message_type_support_t _ImuFilter__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_ImuFilter,
  get_message_typesupport_handle_function,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, drone_c, msg, ImuFilter)() {
  return &_ImuFilter__type_support;
}

#if defined(__cplusplus)
}
#endif
