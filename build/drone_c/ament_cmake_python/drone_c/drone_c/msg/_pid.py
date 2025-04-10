# generated from rosidl_generator_py/resource/_idl.py.em
# with input from drone_c:msg/Pid.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_Pid(type):
    """Metaclass of message 'Pid'."""

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
                'drone_c.msg.Pid')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__pid
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__pid
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__pid
            cls._TYPE_SUPPORT = module.type_support_msg__msg__pid
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__pid

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class Pid(metaclass=Metaclass_Pid):
    """Message class 'Pid'."""

    __slots__ = [
        '_error_pitch',
        '_error_roll',
        '_error_yaw',
        '_p_pitch',
        '_p_roll',
        '_p_yaw',
        '_i_pitch',
        '_i_roll',
        '_i_yaw',
        '_d_pitch',
        '_d_roll',
        '_d_yaw',
        '_sum_pitch',
        '_sum_roll',
        '_sum_yaw',
    ]

    _fields_and_field_types = {
        'error_pitch': 'float',
        'error_roll': 'float',
        'error_yaw': 'float',
        'p_pitch': 'float',
        'p_roll': 'float',
        'p_yaw': 'float',
        'i_pitch': 'float',
        'i_roll': 'float',
        'i_yaw': 'float',
        'd_pitch': 'float',
        'd_roll': 'float',
        'd_yaw': 'float',
        'sum_pitch': 'float',
        'sum_roll': 'float',
        'sum_yaw': 'float',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.error_pitch = kwargs.get('error_pitch', float())
        self.error_roll = kwargs.get('error_roll', float())
        self.error_yaw = kwargs.get('error_yaw', float())
        self.p_pitch = kwargs.get('p_pitch', float())
        self.p_roll = kwargs.get('p_roll', float())
        self.p_yaw = kwargs.get('p_yaw', float())
        self.i_pitch = kwargs.get('i_pitch', float())
        self.i_roll = kwargs.get('i_roll', float())
        self.i_yaw = kwargs.get('i_yaw', float())
        self.d_pitch = kwargs.get('d_pitch', float())
        self.d_roll = kwargs.get('d_roll', float())
        self.d_yaw = kwargs.get('d_yaw', float())
        self.sum_pitch = kwargs.get('sum_pitch', float())
        self.sum_roll = kwargs.get('sum_roll', float())
        self.sum_yaw = kwargs.get('sum_yaw', float())

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
        if self.error_pitch != other.error_pitch:
            return False
        if self.error_roll != other.error_roll:
            return False
        if self.error_yaw != other.error_yaw:
            return False
        if self.p_pitch != other.p_pitch:
            return False
        if self.p_roll != other.p_roll:
            return False
        if self.p_yaw != other.p_yaw:
            return False
        if self.i_pitch != other.i_pitch:
            return False
        if self.i_roll != other.i_roll:
            return False
        if self.i_yaw != other.i_yaw:
            return False
        if self.d_pitch != other.d_pitch:
            return False
        if self.d_roll != other.d_roll:
            return False
        if self.d_yaw != other.d_yaw:
            return False
        if self.sum_pitch != other.sum_pitch:
            return False
        if self.sum_roll != other.sum_roll:
            return False
        if self.sum_yaw != other.sum_yaw:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def error_pitch(self):
        """Message field 'error_pitch'."""
        return self._error_pitch

    @error_pitch.setter
    def error_pitch(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'error_pitch' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'error_pitch' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._error_pitch = value

    @builtins.property
    def error_roll(self):
        """Message field 'error_roll'."""
        return self._error_roll

    @error_roll.setter
    def error_roll(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'error_roll' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'error_roll' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._error_roll = value

    @builtins.property
    def error_yaw(self):
        """Message field 'error_yaw'."""
        return self._error_yaw

    @error_yaw.setter
    def error_yaw(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'error_yaw' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'error_yaw' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._error_yaw = value

    @builtins.property
    def p_pitch(self):
        """Message field 'p_pitch'."""
        return self._p_pitch

    @p_pitch.setter
    def p_pitch(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'p_pitch' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'p_pitch' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._p_pitch = value

    @builtins.property
    def p_roll(self):
        """Message field 'p_roll'."""
        return self._p_roll

    @p_roll.setter
    def p_roll(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'p_roll' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'p_roll' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._p_roll = value

    @builtins.property
    def p_yaw(self):
        """Message field 'p_yaw'."""
        return self._p_yaw

    @p_yaw.setter
    def p_yaw(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'p_yaw' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'p_yaw' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._p_yaw = value

    @builtins.property
    def i_pitch(self):
        """Message field 'i_pitch'."""
        return self._i_pitch

    @i_pitch.setter
    def i_pitch(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'i_pitch' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'i_pitch' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._i_pitch = value

    @builtins.property
    def i_roll(self):
        """Message field 'i_roll'."""
        return self._i_roll

    @i_roll.setter
    def i_roll(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'i_roll' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'i_roll' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._i_roll = value

    @builtins.property
    def i_yaw(self):
        """Message field 'i_yaw'."""
        return self._i_yaw

    @i_yaw.setter
    def i_yaw(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'i_yaw' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'i_yaw' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._i_yaw = value

    @builtins.property
    def d_pitch(self):
        """Message field 'd_pitch'."""
        return self._d_pitch

    @d_pitch.setter
    def d_pitch(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'd_pitch' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'd_pitch' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._d_pitch = value

    @builtins.property
    def d_roll(self):
        """Message field 'd_roll'."""
        return self._d_roll

    @d_roll.setter
    def d_roll(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'd_roll' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'd_roll' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._d_roll = value

    @builtins.property
    def d_yaw(self):
        """Message field 'd_yaw'."""
        return self._d_yaw

    @d_yaw.setter
    def d_yaw(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'd_yaw' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'd_yaw' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._d_yaw = value

    @builtins.property
    def sum_pitch(self):
        """Message field 'sum_pitch'."""
        return self._sum_pitch

    @sum_pitch.setter
    def sum_pitch(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'sum_pitch' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'sum_pitch' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._sum_pitch = value

    @builtins.property
    def sum_roll(self):
        """Message field 'sum_roll'."""
        return self._sum_roll

    @sum_roll.setter
    def sum_roll(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'sum_roll' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'sum_roll' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._sum_roll = value

    @builtins.property
    def sum_yaw(self):
        """Message field 'sum_yaw'."""
        return self._sum_yaw

    @sum_yaw.setter
    def sum_yaw(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'sum_yaw' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'sum_yaw' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._sum_yaw = value
