// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from hamma_bot:msg/Pwm.idl
// generated code does not contain a copyright notice

#ifndef HAMMA_BOT__MSG__DETAIL__PWM__FUNCTIONS_H_
#define HAMMA_BOT__MSG__DETAIL__PWM__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "hamma_bot/msg/rosidl_generator_c__visibility_control.h"

#include "hamma_bot/msg/detail/pwm__struct.h"

/// Initialize msg/Pwm message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * hamma_bot__msg__Pwm
 * )) before or use
 * hamma_bot__msg__Pwm__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_hamma_bot
bool
hamma_bot__msg__Pwm__init(hamma_bot__msg__Pwm * msg);

/// Finalize msg/Pwm message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_hamma_bot
void
hamma_bot__msg__Pwm__fini(hamma_bot__msg__Pwm * msg);

/// Create msg/Pwm message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * hamma_bot__msg__Pwm__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_hamma_bot
hamma_bot__msg__Pwm *
hamma_bot__msg__Pwm__create();

/// Destroy msg/Pwm message.
/**
 * It calls
 * hamma_bot__msg__Pwm__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_hamma_bot
void
hamma_bot__msg__Pwm__destroy(hamma_bot__msg__Pwm * msg);

/// Check for msg/Pwm message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_hamma_bot
bool
hamma_bot__msg__Pwm__are_equal(const hamma_bot__msg__Pwm * lhs, const hamma_bot__msg__Pwm * rhs);

/// Copy a msg/Pwm message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_hamma_bot
bool
hamma_bot__msg__Pwm__copy(
  const hamma_bot__msg__Pwm * input,
  hamma_bot__msg__Pwm * output);

/// Initialize array of msg/Pwm messages.
/**
 * It allocates the memory for the number of elements and calls
 * hamma_bot__msg__Pwm__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_hamma_bot
bool
hamma_bot__msg__Pwm__Sequence__init(hamma_bot__msg__Pwm__Sequence * array, size_t size);

/// Finalize array of msg/Pwm messages.
/**
 * It calls
 * hamma_bot__msg__Pwm__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_hamma_bot
void
hamma_bot__msg__Pwm__Sequence__fini(hamma_bot__msg__Pwm__Sequence * array);

/// Create array of msg/Pwm messages.
/**
 * It allocates the memory for the array and calls
 * hamma_bot__msg__Pwm__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_hamma_bot
hamma_bot__msg__Pwm__Sequence *
hamma_bot__msg__Pwm__Sequence__create(size_t size);

/// Destroy array of msg/Pwm messages.
/**
 * It calls
 * hamma_bot__msg__Pwm__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_hamma_bot
void
hamma_bot__msg__Pwm__Sequence__destroy(hamma_bot__msg__Pwm__Sequence * array);

/// Check for msg/Pwm message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_hamma_bot
bool
hamma_bot__msg__Pwm__Sequence__are_equal(const hamma_bot__msg__Pwm__Sequence * lhs, const hamma_bot__msg__Pwm__Sequence * rhs);

/// Copy an array of msg/Pwm messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_hamma_bot
bool
hamma_bot__msg__Pwm__Sequence__copy(
  const hamma_bot__msg__Pwm__Sequence * input,
  hamma_bot__msg__Pwm__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // HAMMA_BOT__MSG__DETAIL__PWM__FUNCTIONS_H_
