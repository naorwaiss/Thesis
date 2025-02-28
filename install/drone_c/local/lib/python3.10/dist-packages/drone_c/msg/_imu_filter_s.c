// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from drone_c:msg/ImuFilter.idl
// generated code does not contain a copyright notice
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <Python.h>
#include <stdbool.h>
#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-function"
#endif
#include "numpy/ndarrayobject.h"
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif
#include "rosidl_runtime_c/visibility_control.h"
#include "drone_c/msg/detail/imu_filter__struct.h"
#include "drone_c/msg/detail/imu_filter__functions.h"


ROSIDL_GENERATOR_C_EXPORT
bool drone_c__msg__imu_filter__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[34];
    {
      char * class_name = NULL;
      char * module_name = NULL;
      {
        PyObject * class_attr = PyObject_GetAttrString(_pymsg, "__class__");
        if (class_attr) {
          PyObject * name_attr = PyObject_GetAttrString(class_attr, "__name__");
          if (name_attr) {
            class_name = (char *)PyUnicode_1BYTE_DATA(name_attr);
            Py_DECREF(name_attr);
          }
          PyObject * module_attr = PyObject_GetAttrString(class_attr, "__module__");
          if (module_attr) {
            module_name = (char *)PyUnicode_1BYTE_DATA(module_attr);
            Py_DECREF(module_attr);
          }
          Py_DECREF(class_attr);
        }
      }
      if (!class_name || !module_name) {
        return false;
      }
      snprintf(full_classname_dest, sizeof(full_classname_dest), "%s.%s", module_name, class_name);
    }
    assert(strncmp("drone_c.msg._imu_filter.ImuFilter", full_classname_dest, 33) == 0);
  }
  drone_c__msg__ImuFilter * ros_message = _ros_message;
  {  // acc_lpf_x
    PyObject * field = PyObject_GetAttrString(_pymsg, "acc_lpf_x");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->acc_lpf_x = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // acc_lpf_y
    PyObject * field = PyObject_GetAttrString(_pymsg, "acc_lpf_y");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->acc_lpf_y = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // acc_lpf_z
    PyObject * field = PyObject_GetAttrString(_pymsg, "acc_lpf_z");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->acc_lpf_z = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // gyro_hpf_x
    PyObject * field = PyObject_GetAttrString(_pymsg, "gyro_hpf_x");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->gyro_hpf_x = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // gyro_hpf_y
    PyObject * field = PyObject_GetAttrString(_pymsg, "gyro_hpf_y");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->gyro_hpf_y = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // gyro_hpf_z
    PyObject * field = PyObject_GetAttrString(_pymsg, "gyro_hpf_z");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->gyro_hpf_z = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // gyro_lpf_x
    PyObject * field = PyObject_GetAttrString(_pymsg, "gyro_lpf_x");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->gyro_lpf_x = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // gyro_lpf_y
    PyObject * field = PyObject_GetAttrString(_pymsg, "gyro_lpf_y");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->gyro_lpf_y = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // gyro_lpf_z
    PyObject * field = PyObject_GetAttrString(_pymsg, "gyro_lpf_z");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->gyro_lpf_z = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // mag_lpf_x
    PyObject * field = PyObject_GetAttrString(_pymsg, "mag_lpf_x");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->mag_lpf_x = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // mag_lpf_y
    PyObject * field = PyObject_GetAttrString(_pymsg, "mag_lpf_y");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->mag_lpf_y = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // mag_lpf_z
    PyObject * field = PyObject_GetAttrString(_pymsg, "mag_lpf_z");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->mag_lpf_z = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * drone_c__msg__imu_filter__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of ImuFilter */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("drone_c.msg._imu_filter");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "ImuFilter");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  drone_c__msg__ImuFilter * ros_message = (drone_c__msg__ImuFilter *)raw_ros_message;
  {  // acc_lpf_x
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->acc_lpf_x);
    {
      int rc = PyObject_SetAttrString(_pymessage, "acc_lpf_x", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // acc_lpf_y
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->acc_lpf_y);
    {
      int rc = PyObject_SetAttrString(_pymessage, "acc_lpf_y", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // acc_lpf_z
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->acc_lpf_z);
    {
      int rc = PyObject_SetAttrString(_pymessage, "acc_lpf_z", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // gyro_hpf_x
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->gyro_hpf_x);
    {
      int rc = PyObject_SetAttrString(_pymessage, "gyro_hpf_x", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // gyro_hpf_y
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->gyro_hpf_y);
    {
      int rc = PyObject_SetAttrString(_pymessage, "gyro_hpf_y", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // gyro_hpf_z
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->gyro_hpf_z);
    {
      int rc = PyObject_SetAttrString(_pymessage, "gyro_hpf_z", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // gyro_lpf_x
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->gyro_lpf_x);
    {
      int rc = PyObject_SetAttrString(_pymessage, "gyro_lpf_x", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // gyro_lpf_y
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->gyro_lpf_y);
    {
      int rc = PyObject_SetAttrString(_pymessage, "gyro_lpf_y", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // gyro_lpf_z
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->gyro_lpf_z);
    {
      int rc = PyObject_SetAttrString(_pymessage, "gyro_lpf_z", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // mag_lpf_x
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->mag_lpf_x);
    {
      int rc = PyObject_SetAttrString(_pymessage, "mag_lpf_x", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // mag_lpf_y
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->mag_lpf_y);
    {
      int rc = PyObject_SetAttrString(_pymessage, "mag_lpf_y", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // mag_lpf_z
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->mag_lpf_z);
    {
      int rc = PyObject_SetAttrString(_pymessage, "mag_lpf_z", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}
