// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__type_support.cpp.em
// with input from ground_bot:msg/RollerData.idl
// generated code does not contain a copyright notice
#include "ground_bot/msg/detail/roller_data__rosidl_typesupport_fastrtps_cpp.hpp"
#include "ground_bot/msg/detail/roller_data__struct.hpp"

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

namespace ground_bot
{

namespace msg
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_ground_bot
cdr_serialize(
  const ground_bot::msg::RollerData & ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Member: tension
  cdr << ros_message.tension;
  // Member: dis_tension
  cdr << ros_message.dis_tension;
  // Member: error
  cdr << ros_message.error;
  // Member: error_sum
  cdr << ros_message.error_sum;
  return true;
}

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_ground_bot
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  ground_bot::msg::RollerData & ros_message)
{
  // Member: tension
  cdr >> ros_message.tension;

  // Member: dis_tension
  cdr >> ros_message.dis_tension;

  // Member: error
  cdr >> ros_message.error;

  // Member: error_sum
  cdr >> ros_message.error_sum;

  return true;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_ground_bot
get_serialized_size(
  const ground_bot::msg::RollerData & ros_message,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Member: tension
  {
    size_t item_size = sizeof(ros_message.tension);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: dis_tension
  {
    size_t item_size = sizeof(ros_message.dis_tension);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: error
  {
    size_t item_size = sizeof(ros_message.error);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: error_sum
  {
    size_t item_size = sizeof(ros_message.error_sum);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_ground_bot
max_serialized_size_RollerData(
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


  // Member: tension
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Member: dis_tension
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Member: error
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Member: error_sum
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
    using DataType = ground_bot::msg::RollerData;
    is_plain =
      (
      offsetof(DataType, error_sum) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static bool _RollerData__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  auto typed_message =
    static_cast<const ground_bot::msg::RollerData *>(
    untyped_ros_message);
  return cdr_serialize(*typed_message, cdr);
}

static bool _RollerData__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  auto typed_message =
    static_cast<ground_bot::msg::RollerData *>(
    untyped_ros_message);
  return cdr_deserialize(cdr, *typed_message);
}

static uint32_t _RollerData__get_serialized_size(
  const void * untyped_ros_message)
{
  auto typed_message =
    static_cast<const ground_bot::msg::RollerData *>(
    untyped_ros_message);
  return static_cast<uint32_t>(get_serialized_size(*typed_message, 0));
}

static size_t _RollerData__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_RollerData(full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}

static message_type_support_callbacks_t _RollerData__callbacks = {
  "ground_bot::msg",
  "RollerData",
  _RollerData__cdr_serialize,
  _RollerData__cdr_deserialize,
  _RollerData__get_serialized_size,
  _RollerData__max_serialized_size
};

static rosidl_message_type_support_t _RollerData__handle = {
  rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
  &_RollerData__callbacks,
  get_message_typesupport_handle_function,
};

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace ground_bot

namespace rosidl_typesupport_fastrtps_cpp
{

template<>
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_EXPORT_ground_bot
const rosidl_message_type_support_t *
get_message_type_support_handle<ground_bot::msg::RollerData>()
{
  return &ground_bot::msg::typesupport_fastrtps_cpp::_RollerData__handle;
}

}  // namespace rosidl_typesupport_fastrtps_cpp

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, ground_bot, msg, RollerData)() {
  return &ground_bot::msg::typesupport_fastrtps_cpp::_RollerData__handle;
}

#ifdef __cplusplus
}
#endif
