# generated from rosidl_generator_py/resource/_idl.py.em
# with input from drone_c:msg/ImuFilter.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_ImuFilter(type):
    """Metaclass of message 'ImuFilter'."""

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
                'drone_c.msg.ImuFilter')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__imu_filter
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__imu_filter
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__imu_filter
            cls._TYPE_SUPPORT = module.type_support_msg__msg__imu_filter
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__imu_filter

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class ImuFilter(metaclass=Metaclass_ImuFilter):
    """Message class 'ImuFilter'."""

    __slots__ = [
        '_acc_lpf_x',
        '_acc_lpf_y',
        '_acc_lpf_z',
        '_gyro_hpf_x',
        '_gyro_hpf_y',
        '_gyro_hpf_z',
        '_gyro_lpf_x',
        '_gyro_lpf_y',
        '_gyro_lpf_z',
        '_mag_lpf_x',
        '_mag_lpf_y',
        '_mag_lpf_z',
    ]

    _fields_and_field_types = {
        'acc_lpf_x': 'float',
        'acc_lpf_y': 'float',
        'acc_lpf_z': 'float',
        'gyro_hpf_x': 'float',
        'gyro_hpf_y': 'float',
        'gyro_hpf_z': 'float',
        'gyro_lpf_x': 'float',
        'gyro_lpf_y': 'float',
        'gyro_lpf_z': 'float',
        'mag_lpf_x': 'float',
        'mag_lpf_y': 'float',
        'mag_lpf_z': 'float',
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
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.acc_lpf_x = kwargs.get('acc_lpf_x', float())
        self.acc_lpf_y = kwargs.get('acc_lpf_y', float())
        self.acc_lpf_z = kwargs.get('acc_lpf_z', float())
        self.gyro_hpf_x = kwargs.get('gyro_hpf_x', float())
        self.gyro_hpf_y = kwargs.get('gyro_hpf_y', float())
        self.gyro_hpf_z = kwargs.get('gyro_hpf_z', float())
        self.gyro_lpf_x = kwargs.get('gyro_lpf_x', float())
        self.gyro_lpf_y = kwargs.get('gyro_lpf_y', float())
        self.gyro_lpf_z = kwargs.get('gyro_lpf_z', float())
        self.mag_lpf_x = kwargs.get('mag_lpf_x', float())
        self.mag_lpf_y = kwargs.get('mag_lpf_y', float())
        self.mag_lpf_z = kwargs.get('mag_lpf_z', float())

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
        if self.acc_lpf_x != other.acc_lpf_x:
            return False
        if self.acc_lpf_y != other.acc_lpf_y:
            return False
        if self.acc_lpf_z != other.acc_lpf_z:
            return False
        if self.gyro_hpf_x != other.gyro_hpf_x:
            return False
        if self.gyro_hpf_y != other.gyro_hpf_y:
            return False
        if self.gyro_hpf_z != other.gyro_hpf_z:
            return False
        if self.gyro_lpf_x != other.gyro_lpf_x:
            return False
        if self.gyro_lpf_y != other.gyro_lpf_y:
            return False
        if self.gyro_lpf_z != other.gyro_lpf_z:
            return False
        if self.mag_lpf_x != other.mag_lpf_x:
            return False
        if self.mag_lpf_y != other.mag_lpf_y:
            return False
        if self.mag_lpf_z != other.mag_lpf_z:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def acc_lpf_x(self):
        """Message field 'acc_lpf_x'."""
        return self._acc_lpf_x

    @acc_lpf_x.setter
    def acc_lpf_x(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'acc_lpf_x' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'acc_lpf_x' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._acc_lpf_x = value

    @builtins.property
    def acc_lpf_y(self):
        """Message field 'acc_lpf_y'."""
        return self._acc_lpf_y

    @acc_lpf_y.setter
    def acc_lpf_y(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'acc_lpf_y' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'acc_lpf_y' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._acc_lpf_y = value

    @builtins.property
    def acc_lpf_z(self):
        """Message field 'acc_lpf_z'."""
        return self._acc_lpf_z

    @acc_lpf_z.setter
    def acc_lpf_z(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'acc_lpf_z' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'acc_lpf_z' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._acc_lpf_z = value

    @builtins.property
    def gyro_hpf_x(self):
        """Message field 'gyro_hpf_x'."""
        return self._gyro_hpf_x

    @gyro_hpf_x.setter
    def gyro_hpf_x(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'gyro_hpf_x' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'gyro_hpf_x' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._gyro_hpf_x = value

    @builtins.property
    def gyro_hpf_y(self):
        """Message field 'gyro_hpf_y'."""
        return self._gyro_hpf_y

    @gyro_hpf_y.setter
    def gyro_hpf_y(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'gyro_hpf_y' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'gyro_hpf_y' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._gyro_hpf_y = value

    @builtins.property
    def gyro_hpf_z(self):
        """Message field 'gyro_hpf_z'."""
        return self._gyro_hpf_z

    @gyro_hpf_z.setter
    def gyro_hpf_z(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'gyro_hpf_z' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'gyro_hpf_z' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._gyro_hpf_z = value

    @builtins.property
    def gyro_lpf_x(self):
        """Message field 'gyro_lpf_x'."""
        return self._gyro_lpf_x

    @gyro_lpf_x.setter
    def gyro_lpf_x(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'gyro_lpf_x' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'gyro_lpf_x' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._gyro_lpf_x = value

    @builtins.property
    def gyro_lpf_y(self):
        """Message field 'gyro_lpf_y'."""
        return self._gyro_lpf_y

    @gyro_lpf_y.setter
    def gyro_lpf_y(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'gyro_lpf_y' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'gyro_lpf_y' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._gyro_lpf_y = value

    @builtins.property
    def gyro_lpf_z(self):
        """Message field 'gyro_lpf_z'."""
        return self._gyro_lpf_z

    @gyro_lpf_z.setter
    def gyro_lpf_z(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'gyro_lpf_z' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'gyro_lpf_z' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._gyro_lpf_z = value

    @builtins.property
    def mag_lpf_x(self):
        """Message field 'mag_lpf_x'."""
        return self._mag_lpf_x

    @mag_lpf_x.setter
    def mag_lpf_x(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'mag_lpf_x' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'mag_lpf_x' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._mag_lpf_x = value

    @builtins.property
    def mag_lpf_y(self):
        """Message field 'mag_lpf_y'."""
        return self._mag_lpf_y

    @mag_lpf_y.setter
    def mag_lpf_y(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'mag_lpf_y' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'mag_lpf_y' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._mag_lpf_y = value

    @builtins.property
    def mag_lpf_z(self):
        """Message field 'mag_lpf_z'."""
        return self._mag_lpf_z

    @mag_lpf_z.setter
    def mag_lpf_z(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'mag_lpf_z' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'mag_lpf_z' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._mag_lpf_z = value
