// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from hamma_bot:msg/Pwm.idl
// generated code does not contain a copyright notice
#include "hamma_bot/msg/detail/pwm__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
hamma_bot__msg__Pwm__init(hamma_bot__msg__Pwm * msg)
{
  if (!msg) {
    return false;
  }
  // pwm_left_motor
  // pwm_right_motor
  return true;
}

void
hamma_bot__msg__Pwm__fini(hamma_bot__msg__Pwm * msg)
{
  if (!msg) {
    return;
  }
  // pwm_left_motor
  // pwm_right_motor
}

bool
hamma_bot__msg__Pwm__are_equal(const hamma_bot__msg__Pwm * lhs, const hamma_bot__msg__Pwm * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // pwm_left_motor
  if (lhs->pwm_left_motor != rhs->pwm_left_motor) {
    return false;
  }
  // pwm_right_motor
  if (lhs->pwm_right_motor != rhs->pwm_right_motor) {
    return false;
  }
  return true;
}

bool
hamma_bot__msg__Pwm__copy(
  const hamma_bot__msg__Pwm * input,
  hamma_bot__msg__Pwm * output)
{
  if (!input || !output) {
    return false;
  }
  // pwm_left_motor
  output->pwm_left_motor = input->pwm_left_motor;
  // pwm_right_motor
  output->pwm_right_motor = input->pwm_right_motor;
  return true;
}

hamma_bot__msg__Pwm *
hamma_bot__msg__Pwm__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  hamma_bot__msg__Pwm * msg = (hamma_bot__msg__Pwm *)allocator.allocate(sizeof(hamma_bot__msg__Pwm), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(hamma_bot__msg__Pwm));
  bool success = hamma_bot__msg__Pwm__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
hamma_bot__msg__Pwm__destroy(hamma_bot__msg__Pwm * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    hamma_bot__msg__Pwm__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
hamma_bot__msg__Pwm__Sequence__init(hamma_bot__msg__Pwm__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  hamma_bot__msg__Pwm * data = NULL;

  if (size) {
    data = (hamma_bot__msg__Pwm *)allocator.zero_allocate(size, sizeof(hamma_bot__msg__Pwm), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = hamma_bot__msg__Pwm__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        hamma_bot__msg__Pwm__fini(&data[i - 1]);
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
hamma_bot__msg__Pwm__Sequence__fini(hamma_bot__msg__Pwm__Sequence * array)
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
      hamma_bot__msg__Pwm__fini(&array->data[i]);
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

hamma_bot__msg__Pwm__Sequence *
hamma_bot__msg__Pwm__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  hamma_bot__msg__Pwm__Sequence * array = (hamma_bot__msg__Pwm__Sequence *)allocator.allocate(sizeof(hamma_bot__msg__Pwm__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = hamma_bot__msg__Pwm__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
hamma_bot__msg__Pwm__Sequence__destroy(hamma_bot__msg__Pwm__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    hamma_bot__msg__Pwm__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
hamma_bot__msg__Pwm__Sequence__are_equal(const hamma_bot__msg__Pwm__Sequence * lhs, const hamma_bot__msg__Pwm__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!hamma_bot__msg__Pwm__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
hamma_bot__msg__Pwm__Sequence__copy(
  const hamma_bot__msg__Pwm__Sequence * input,
  hamma_bot__msg__Pwm__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(hamma_bot__msg__Pwm);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    hamma_bot__msg__Pwm * data =
      (hamma_bot__msg__Pwm *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!hamma_bot__msg__Pwm__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          hamma_bot__msg__Pwm__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!hamma_bot__msg__Pwm__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
