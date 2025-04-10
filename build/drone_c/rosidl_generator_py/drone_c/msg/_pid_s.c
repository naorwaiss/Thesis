// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from drone_c:msg/Pid.idl
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
#include "drone_c/msg/detail/pid__struct.h"
#include "drone_c/msg/detail/pid__functions.h"


ROSIDL_GENERATOR_C_EXPORT
bool drone_c__msg__pid__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[21];
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
    assert(strncmp("drone_c.msg._pid.Pid", full_classname_dest, 20) == 0);
  }
  drone_c__msg__Pid * ros_message = _ros_message;
  {  // error_pitch
    PyObject * field = PyObject_GetAttrString(_pymsg, "error_pitch");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->error_pitch = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // error_roll
    PyObject * field = PyObject_GetAttrString(_pymsg, "error_roll");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->error_roll = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // error_yaw
    PyObject * field = PyObject_GetAttrString(_pymsg, "error_yaw");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->error_yaw = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // p_pitch
    PyObject * field = PyObject_GetAttrString(_pymsg, "p_pitch");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->p_pitch = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // p_roll
    PyObject * field = PyObject_GetAttrString(_pymsg, "p_roll");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->p_roll = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // p_yaw
    PyObject * field = PyObject_GetAttrString(_pymsg, "p_yaw");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->p_yaw = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // i_pitch
    PyObject * field = PyObject_GetAttrString(_pymsg, "i_pitch");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->i_pitch = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // i_roll
    PyObject * field = PyObject_GetAttrString(_pymsg, "i_roll");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->i_roll = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // i_yaw
    PyObject * field = PyObject_GetAttrString(_pymsg, "i_yaw");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->i_yaw = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // d_pitch
    PyObject * field = PyObject_GetAttrString(_pymsg, "d_pitch");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->d_pitch = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // d_roll
    PyObject * field = PyObject_GetAttrString(_pymsg, "d_roll");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->d_roll = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // d_yaw
    PyObject * field = PyObject_GetAttrString(_pymsg, "d_yaw");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->d_yaw = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // sum_pitch
    PyObject * field = PyObject_GetAttrString(_pymsg, "sum_pitch");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->sum_pitch = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // sum_roll
    PyObject * field = PyObject_GetAttrString(_pymsg, "sum_roll");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->sum_roll = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // sum_yaw
    PyObject * field = PyObject_GetAttrString(_pymsg, "sum_yaw");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->sum_yaw = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * drone_c__msg__pid__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of Pid */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("drone_c.msg._pid");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "Pid");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  drone_c__msg__Pid * ros_message = (drone_c__msg__Pid *)raw_ros_message;
  {  // error_pitch
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->error_pitch);
    {
      int rc = PyObject_SetAttrString(_pymessage, "error_pitch", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // error_roll
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->error_roll);
    {
      int rc = PyObject_SetAttrString(_pymessage, "error_roll", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // error_yaw
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->error_yaw);
    {
      int rc = PyObject_SetAttrString(_pymessage, "error_yaw", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // p_pitch
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->p_pitch);
    {
      int rc = PyObject_SetAttrString(_pymessage, "p_pitch", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // p_roll
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->p_roll);
    {
      int rc = PyObject_SetAttrString(_pymessage, "p_roll", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // p_yaw
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->p_yaw);
    {
      int rc = PyObject_SetAttrString(_pymessage, "p_yaw", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // i_pitch
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->i_pitch);
    {
      int rc = PyObject_SetAttrString(_pymessage, "i_pitch", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // i_roll
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->i_roll);
    {
      int rc = PyObject_SetAttrString(_pymessage, "i_roll", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // i_yaw
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->i_yaw);
    {
      int rc = PyObject_SetAttrString(_pymessage, "i_yaw", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // d_pitch
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->d_pitch);
    {
      int rc = PyObject_SetAttrString(_pymessage, "d_pitch", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // d_roll
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->d_roll);
    {
      int rc = PyObject_SetAttrString(_pymessage, "d_roll", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // d_yaw
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->d_yaw);
    {
      int rc = PyObject_SetAttrString(_pymessage, "d_yaw", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // sum_pitch
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->sum_pitch);
    {
      int rc = PyObject_SetAttrString(_pymessage, "sum_pitch", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // sum_roll
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->sum_roll);
    {
      int rc = PyObject_SetAttrString(_pymessage, "sum_roll", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // sum_yaw
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->sum_yaw);
    {
      int rc = PyObject_SetAttrString(_pymessage, "sum_yaw", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}
