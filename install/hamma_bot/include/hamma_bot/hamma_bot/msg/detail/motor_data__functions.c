// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from hamma_bot:msg/MotorData.idl
// generated code does not contain a copyright notice
#include "hamma_bot/msg/detail/motor_data__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
hamma_bot__msg__MotorData__init(hamma_bot__msg__MotorData * msg)
{
  if (!msg) {
    return false;
  }
  // left_motor
  // right_motor
  return true;
}

void
hamma_bot__msg__MotorData__fini(hamma_bot__msg__MotorData * msg)
{
  if (!msg) {
    return;
  }
  // left_motor
  // right_motor
}

bool
hamma_bot__msg__MotorData__are_equal(const hamma_bot__msg__MotorData * lhs, const hamma_bot__msg__MotorData * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // left_motor
  if (lhs->left_motor != rhs->left_motor) {
    return false;
  }
  // right_motor
  if (lhs->right_motor != rhs->right_motor) {
    return false;
  }
  return true;
}

bool
hamma_bot__msg__MotorData__copy(
  const hamma_bot__msg__MotorData * input,
  hamma_bot__msg__MotorData * output)
{
  if (!input || !output) {
    return false;
  }
  // left_motor
  output->left_motor = input->left_motor;
  // right_motor
  output->right_motor = input->right_motor;
  return true;
}

hamma_bot__msg__MotorData *
hamma_bot__msg__MotorData__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  hamma_bot__msg__MotorData * msg = (hamma_bot__msg__MotorData *)allocator.allocate(sizeof(hamma_bot__msg__MotorData), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(hamma_bot__msg__MotorData));
  bool success = hamma_bot__msg__MotorData__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
hamma_bot__msg__MotorData__destroy(hamma_bot__msg__MotorData * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    hamma_bot__msg__MotorData__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
hamma_bot__msg__MotorData__Sequence__init(hamma_bot__msg__MotorData__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  hamma_bot__msg__MotorData * data = NULL;

  if (size) {
    data = (hamma_bot__msg__MotorData *)allocator.zero_allocate(size, sizeof(hamma_bot__msg__MotorData), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = hamma_bot__msg__MotorData__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        hamma_bot__msg__MotorData__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
hamma_bot__msg__MotorData__Sequence__fini(hamma_bot__msg__MotorData__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      hamma_bot__msg__MotorData__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

hamma_bot__msg__MotorData__Sequence *
hamma_bot__msg__MotorData__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  hamma_bot__msg__MotorData__Sequence * array = (hamma_bot__msg__MotorData__Sequence *)allocator.allocate(sizeof(hamma_bot__msg__MotorData__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = hamma_bot__msg__MotorData__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
hamma_bot__msg__MotorData__Sequence__destroy(hamma_bot__msg__MotorData__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    hamma_bot__msg__MotorData__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
hamma_bot__msg__MotorData__Sequence__are_equal(const hamma_bot__msg__MotorData__Sequence * lhs, const hamma_bot__msg__MotorData__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!hamma_bot__msg__MotorData__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
hamma_bot__msg__MotorData__Sequence__copy(
  const hamma_bot__msg__MotorData__Sequence * input,
  hamma_bot__msg__MotorData__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(hamma_bot__msg__MotorData);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    hamma_bot__msg__MotorData * data =
      (hamma_bot__msg__MotorData *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!hamma_bot__msg__MotorData__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          hamma_bot__msg__MotorData__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!hamma_bot__msg__MotorData__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
