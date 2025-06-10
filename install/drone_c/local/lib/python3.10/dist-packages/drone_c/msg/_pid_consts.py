# generated from rosidl_generator_py/resource/_idl.py.em
# with input from drone_c:msg/PidConsts.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

# Member 'rate_pitch'
# Member 'rate_roll'
# Member 'stablize_pitch'
# Member 'stablize_roll'
# Member 'rate_yaw'
import numpy  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_PidConsts(type):
    """Metaclass of message 'PidConsts'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('drone_c')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'drone_c.msg.PidConsts')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__pid_consts
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__pid_consts
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__pid_consts
            cls._TYPE_SUPPORT = module.type_support_msg__msg__pid_consts
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__pid_consts

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class PidConsts(metaclass=Metaclass_PidConsts):
    """Message class 'PidConsts'."""

    __slots__ = [
        '_rate_pitch',
        '_rate_roll',
        '_stablize_pitch',
        '_stablize_roll',
        '_rate_yaw',
    ]

    _fields_and_field_types = {
        'rate_pitch': 'float[3]',
        'rate_roll': 'float[3]',
        'stablize_pitch': 'float[3]',
        'stablize_roll': 'float[3]',
        'rate_yaw': 'float[3]',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.Array(rosidl_parser.definition.BasicType('float'), 3),  # noqa: E501
        rosidl_parser.definition.Array(rosidl_parser.definition.BasicType('float'), 3),  # noqa: E501
        rosidl_parser.definition.Array(rosidl_parser.definition.BasicType('float'), 3),  # noqa: E501
        rosidl_parser.definition.Array(rosidl_parser.definition.BasicType('float'), 3),  # noqa: E501
        rosidl_parser.definition.Array(rosidl_parser.definition.BasicType('float'), 3),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        if 'rate_pitch' not in kwargs:
            self.rate_pitch = numpy.zeros(3, dtype=numpy.float32)
        else:
            self.rate_pitch = numpy.array(kwargs.get('rate_pitch'), dtype=numpy.float32)
            assert self.rate_pitch.shape == (3, )
        if 'rate_roll' not in kwargs:
            self.rate_roll = numpy.zeros(3, dtype=numpy.float32)
        else:
            self.rate_roll = numpy.array(kwargs.get('rate_roll'), dtype=numpy.float32)
            assert self.rate_roll.shape == (3, )
        if 'stablize_pitch' not in kwargs:
            self.stablize_pitch = numpy.zeros(3, dtype=numpy.float32)
        else:
            self.stablize_pitch = numpy.array(kwargs.get('stablize_pitch'), dtype=numpy.float32)
            assert self.stablize_pitch.shape == (3, )
        if 'stablize_roll' not in kwargs:
            self.stablize_roll = numpy.zeros(3, dtype=numpy.float32)
        else:
            self.stablize_roll = numpy.array(kwargs.get('stablize_roll'), dtype=numpy.float32)
            assert self.stablize_roll.shape == (3, )
        if 'rate_yaw' not in kwargs:
            self.rate_yaw = numpy.zeros(3, dtype=numpy.float32)
        else:
            self.rate_yaw = numpy.array(kwargs.get('rate_yaw'), dtype=numpy.float32)
            assert self.rate_yaw.shape == (3, )

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.__slots__, self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s[1:] + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        if all(self.rate_pitch != other.rate_pitch):
            return False
        if all(self.rate_roll != other.rate_roll):
            return False
        if all(self.stablize_pitch != other.stablize_pitch):
            return False
        if all(self.stablize_roll != other.stablize_roll):
            return False
        if all(self.rate_yaw != other.rate_yaw):
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def rate_pitch(self):
        """Message field 'rate_pitch'."""
        return self._rate_pitch

    @rate_pitch.setter
    def rate_pitch(self, value):
        if isinstance(value, numpy.ndarray):
            assert value.dtype == numpy.float32, \
                "The 'rate_pitch' numpy.ndarray() must have the dtype of 'numpy.float32'"
            assert value.size == 3, \
                "The 'rate_pitch' numpy.ndarray() must have a size of 3"
            self._rate_pitch = value
            return
        if __debug__:
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 len(value) == 3 and
                 all(isinstance(v, float) for v in value) and
                 all(not (val < -3.402823466e+38 or val > 3.402823466e+38) or math.isinf(val) for val in value)), \
                "The 'rate_pitch' field must be a set or sequence with length 3 and each value of type 'float' and each float in [-340282346600000016151267322115014000640.000000, 340282346600000016151267322115014000640.000000]"
        self._rate_pitch = numpy.array(value, dtype=numpy.float32)

    @builtins.property
    def rate_roll(self):
        """Message field 'rate_roll'."""
        return self._rate_roll

    @rate_roll.setter
    def rate_roll(self, value):
        if isinstance(value, numpy.ndarray):
            assert value.dtype == numpy.float32, \
                "The 'rate_roll' numpy.ndarray() must have the dtype of 'numpy.float32'"
            assert value.size == 3, \
                "The 'rate_roll' numpy.ndarray() must have a size of 3"
            self._rate_roll = value
            return
        if __debug__:
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 len(value) == 3 and
                 all(isinstance(v, float) for v in value) and
                 all(not (val < -3.402823466e+38 or val > 3.402823466e+38) or math.isinf(val) for val in value)), \
                "The 'rate_roll' field must be a set or sequence with length 3 and each value of type 'float' and each float in [-340282346600000016151267322115014000640.000000, 340282346600000016151267322115014000640.000000]"
        self._rate_roll = numpy.array(value, dtype=numpy.float32)

    @builtins.property
    def stablize_pitch(self):
        """Message field 'stablize_pitch'."""
        return self._stablize_pitch

    @stablize_pitch.setter
    def stablize_pitch(self, value):
        if isinstance(value, numpy.ndarray):
            assert value.dtype == numpy.float32, \
                "The 'stablize_pitch' numpy.ndarray() must have the dtype of 'numpy.float32'"
            assert value.size == 3, \
                "The 'stablize_pitch' numpy.ndarray() must have a size of 3"
            self._stablize_pitch = value
            return
        if __debug__:
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 len(value) == 3 and
                 all(isinstance(v, float) for v in value) and
                 all(not (val < -3.402823466e+38 or val > 3.402823466e+38) or math.isinf(val) for val in value)), \
                "The 'stablize_pitch' field must be a set or sequence with length 3 and each value of type 'float' and each float in [-340282346600000016151267322115014000640.000000, 340282346600000016151267322115014000640.000000]"
        self._stablize_pitch = numpy.array(value, dtype=numpy.float32)

    @builtins.property
    def stablize_roll(self):
        """Message field 'stablize_roll'."""
        return self._stablize_roll

    @stablize_roll.setter
    def stablize_roll(self, value):
        if isinstance(value, numpy.ndarray):
            assert value.dtype == numpy.float32, \
                "The 'stablize_roll' numpy.ndarray() must have the dtype of 'numpy.float32'"
            assert value.size == 3, \
                "The 'stablize_roll' numpy.ndarray() must have a size of 3"
            self._stablize_roll = value
            return
        if __debug__:
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 len(value) == 3 and
                 all(isinstance(v, float) for v in value) and
                 all(not (val < -3.402823466e+38 or val > 3.402823466e+38) or math.isinf(val) for val in value)), \
                "The 'stablize_roll' field must be a set or sequence with length 3 and each value of type 'float' and each float in [-340282346600000016151267322115014000640.000000, 340282346600000016151267322115014000640.000000]"
        self._stablize_roll = numpy.array(value, dtype=numpy.float32)

    @builtins.property
    def rate_yaw(self):
        """Message field 'rate_yaw'."""
        return self._rate_yaw

    @rate_yaw.setter
    def rate_yaw(self, value):
        if isinstance(value, numpy.ndarray):
            assert value.dtype == numpy.float32, \
                "The 'rate_yaw' numpy.ndarray() must have the dtype of 'numpy.float32'"
            assert value.size == 3, \
                "The 'rate_yaw' numpy.ndarray() must have a size of 3"
            self._rate_yaw = value
            return
        if __debug__:
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 len(value) == 3 and
                 all(isinstance(v, float) for v in value) and
                 all(not (val < -3.402823466e+38 or val > 3.402823466e+38) or math.isinf(val) for val in value)), \
                "The 'rate_yaw' field must be a set or sequence with length 3 and each value of type 'float' and each float in [-340282346600000016151267322115014000640.000000, 340282346600000016151267322115014000640.000000]"
        self._rate_yaw = numpy.array(value, dtype=numpy.float32)
