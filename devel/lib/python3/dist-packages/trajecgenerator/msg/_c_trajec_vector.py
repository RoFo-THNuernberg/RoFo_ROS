# This Python file uses the following encoding: utf-8
"""autogenerated by genpy from trajecgenerator/c_trajec_vector.msg. Do not edit."""
import codecs
import sys
python3 = True if sys.hexversion > 0x03000000 else False
import genpy
import struct

import trajecgenerator.msg

class c_trajec_vector(genpy.Message):
  _md5sum = "d88f63147d96501d5ff38e0f76d36cc9"
  _type = "trajecgenerator/c_trajec_vector"
  _has_header = False  # flag to mark the presence of a Header object
  _full_text = """c_trajec[] points

================================================================================
MSG: trajecgenerator/c_trajec
float32 x
float32 y
float32 dx
float32 dy
float32 ddx
float32 ddy
uint64 timestamp
"""
  __slots__ = ['points']
  _slot_types = ['trajecgenerator/c_trajec[]']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.

    The available fields are:
       points

    :param args: complete set of field values, in .msg order
    :param kwds: use keyword arguments corresponding to message field names
    to set specific fields.
    """
    if args or kwds:
      super(c_trajec_vector, self).__init__(*args, **kwds)
      # message fields cannot be None, assign default values for those that are
      if self.points is None:
        self.points = []
    else:
      self.points = []

  def _get_types(self):
    """
    internal API method
    """
    return self._slot_types

  def serialize(self, buff):
    """
    serialize message into buffer
    :param buff: buffer, ``StringIO``
    """
    try:
      length = len(self.points)
      buff.write(_struct_I.pack(length))
      for val1 in self.points:
        _x = val1
        buff.write(_get_struct_6fQ().pack(_x.x, _x.y, _x.dx, _x.dy, _x.ddx, _x.ddy, _x.timestamp))
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(locals().get('_x', self)))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(locals().get('_x', self)))))

  def deserialize(self, str):
    """
    unpack serialized message in str into this message instance
    :param str: byte array of serialized message, ``str``
    """
    if python3:
      codecs.lookup_error("rosmsg").msg_type = self._type
    try:
      if self.points is None:
        self.points = None
      end = 0
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      self.points = []
      for i in range(0, length):
        val1 = trajecgenerator.msg.c_trajec()
        _x = val1
        start = end
        end += 32
        (_x.x, _x.y, _x.dx, _x.dy, _x.ddx, _x.ddy, _x.timestamp,) = _get_struct_6fQ().unpack(str[start:end])
        self.points.append(val1)
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e)  # most likely buffer underfill


  def serialize_numpy(self, buff, numpy):
    """
    serialize message with numpy array types into buffer
    :param buff: buffer, ``StringIO``
    :param numpy: numpy python module
    """
    try:
      length = len(self.points)
      buff.write(_struct_I.pack(length))
      for val1 in self.points:
        _x = val1
        buff.write(_get_struct_6fQ().pack(_x.x, _x.y, _x.dx, _x.dy, _x.ddx, _x.ddy, _x.timestamp))
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(locals().get('_x', self)))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(locals().get('_x', self)))))

  def deserialize_numpy(self, str, numpy):
    """
    unpack serialized message in str into this message instance using numpy for array types
    :param str: byte array of serialized message, ``str``
    :param numpy: numpy python module
    """
    if python3:
      codecs.lookup_error("rosmsg").msg_type = self._type
    try:
      if self.points is None:
        self.points = None
      end = 0
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      self.points = []
      for i in range(0, length):
        val1 = trajecgenerator.msg.c_trajec()
        _x = val1
        start = end
        end += 32
        (_x.x, _x.y, _x.dx, _x.dy, _x.ddx, _x.ddy, _x.timestamp,) = _get_struct_6fQ().unpack(str[start:end])
        self.points.append(val1)
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e)  # most likely buffer underfill

_struct_I = genpy.struct_I
def _get_struct_I():
    global _struct_I
    return _struct_I
_struct_6fQ = None
def _get_struct_6fQ():
    global _struct_6fQ
    if _struct_6fQ is None:
        _struct_6fQ = struct.Struct("<6fQ")
    return _struct_6fQ
