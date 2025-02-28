// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from drone_c:msg/ImuFilter.idl
// generated code does not contain a copyright notice
#include "drone_c/msg/detail/imu_filter__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
drone_c__msg__ImuFilter__init(drone_c__msg__ImuFilter * msg)
{
  if (!msg) {
    return false;
  }
  // acc_lpf_x
  // acc_lpf_y
  // acc_lpf_z
  // gyro_hpf_x
  // gyro_hpf_y
  // gyro_hpf_z
  // gyro_lpf_x
  // gyro_lpf_y
  // gyro_lpf_z
  // mag_lpf_x
  // mag_lpf_y
  // mag_lpf_z
  return true;
}

void
drone_c__msg__ImuFilter__fini(drone_c__msg__ImuFilter * msg)
{
  if (!msg) {
    return;
  }
  // acc_lpf_x
  // acc_lpf_y
  // acc_lpf_z
  // gyro_hpf_x
  // gyro_hpf_y
  // gyro_hpf_z
  // gyro_lpf_x
  // gyro_lpf_y
  // gyro_lpf_z
  // mag_lpf_x
  // mag_lpf_y
  // mag_lpf_z
}

bool
drone_c__msg__ImuFilter__are_equal(const drone_c__msg__ImuFilter * lhs, const drone_c__msg__ImuFilter * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // acc_lpf_x
  if (lhs->acc_lpf_x != rhs->acc_lpf_x) {
    return false;
  }
  // acc_lpf_y
  if (lhs->acc_lpf_y != rhs->acc_lpf_y) {
    return false;
  }
  // acc_lpf_z
  if (lhs->acc_lpf_z != rhs->acc_lpf_z) {
    return false;
  }
  // gyro_hpf_x
  if (lhs->gyro_hpf_x != rhs->gyro_hpf_x) {
    return false;
  }
  // gyro_hpf_y
  if (lhs->gyro_hpf_y != rhs->gyro_hpf_y) {
    return false;
  }
  // gyro_hpf_z
  if (lhs->gyro_hpf_z != rhs->gyro_hpf_z) {
    return false;
  }
  // gyro_lpf_x
  if (lhs->gyro_lpf_x != rhs->gyro_lpf_x) {
    return false;
  }
  // gyro_lpf_y
  if (lhs->gyro_lpf_y != rhs->gyro_lpf_y) {
    return false;
  }
  // gyro_lpf_z
  if (lhs->gyro_lpf_z != rhs->gyro_lpf_z) {
    return false;
  }
  // mag_lpf_x
  if (lhs->mag_lpf_x != rhs->mag_lpf_x) {
    return false;
  }
  // mag_lpf_y
  if (lhs->mag_lpf_y != rhs->mag_lpf_y) {
    return false;
  }
  // mag_lpf_z
  if (lhs->mag_lpf_z != rhs->mag_lpf_z) {
    return false;
  }
  return true;
}

bool
drone_c__msg__ImuFilter__copy(
  const drone_c__msg__ImuFilter * input,
  drone_c__msg__ImuFilter * output)
{
  if (!input || !output) {
    return false;
  }
  // acc_lpf_x
  output->acc_lpf_x = input->acc_lpf_x;
  // acc_lpf_y
  output->acc_lpf_y = input->acc_lpf_y;
  // acc_lpf_z
  output->acc_lpf_z = input->acc_lpf_z;
  // gyro_hpf_x
  output->gyro_hpf_x = input->gyro_hpf_x;
  // gyro_hpf_y
  output->gyro_hpf_y = input->gyro_hpf_y;
  // gyro_hpf_z
  output->gyro_hpf_z = input->gyro_hpf_z;
  // gyro_lpf_x
  output->gyro_lpf_x = input->gyro_lpf_x;
  // gyro_lpf_y
  output->gyro_lpf_y = input->gyro_lpf_y;
  // gyro_lpf_z
  output->gyro_lpf_z = input->gyro_lpf_z;
  // mag_lpf_x
  output->mag_lpf_x = input->mag_lpf_x;
  // mag_lpf_y
  output->mag_lpf_y = input->mag_lpf_y;
  // mag_lpf_z
  output->mag_lpf_z = input->mag_lpf_z;
  return true;
}

drone_c__msg__ImuFilter *
drone_c__msg__ImuFilter__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  drone_c__msg__ImuFilter * msg = (drone_c__msg__ImuFilter *)allocator.allocate(sizeof(drone_c__msg__ImuFilter), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(drone_c__msg__ImuFilter));
  bool success = drone_c__msg__ImuFilter__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
drone_c__msg__ImuFilter__destroy(drone_c__msg__ImuFilter * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    drone_c__msg__ImuFilter__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
drone_c__msg__ImuFilter__Sequence__init(drone_c__msg__ImuFilter__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  drone_c__msg__ImuFilter * data = NULL;

  if (size) {
    data = (drone_c__msg__ImuFilter *)allocator.zero_allocate(size, sizeof(drone_c__msg__ImuFilter), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = drone_c__msg__ImuFilter__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        drone_c__msg__ImuFilter__fini(&data[i - 1]);
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
drone_c__msg__ImuFilter__Sequence__fini(drone_c__msg__ImuFilter__Sequence * array)
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
      drone_c__msg__ImuFilter__fini(&array->data[i]);
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

drone_c__msg__ImuFilter__Sequence *
drone_c__msg__ImuFilter__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  drone_c__msg__ImuFilter__Sequence * array = (drone_c__msg__ImuFilter__Sequence *)allocator.allocate(sizeof(drone_c__msg__ImuFilter__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = drone_c__msg__ImuFilter__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
drone_c__msg__ImuFilter__Sequence__destroy(drone_c__msg__ImuFilter__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    drone_c__msg__ImuFilter__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
drone_c__msg__ImuFilter__Sequence__are_equal(const drone_c__msg__ImuFilter__Sequence * lhs, const drone_c__msg__ImuFilter__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!drone_c__msg__ImuFilter__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
drone_c__msg__ImuFilter__Sequence__copy(
  const drone_c__msg__ImuFilter__Sequence * input,
  drone_c__msg__ImuFilter__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(drone_c__msg__ImuFilter);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    drone_c__msg__ImuFilter * data =
      (drone_c__msg__ImuFilter *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!drone_c__msg__ImuFilter__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          drone_c__msg__ImuFilter__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!drone_c__msg__ImuFilter__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
