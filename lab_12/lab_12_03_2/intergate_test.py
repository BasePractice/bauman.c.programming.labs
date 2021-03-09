# LINK: https://docs.python.org/3/library/ctypes.html
# coding=utf-8
import unittest
import os.path
from ctypes import *

me = os.path.abspath(os.path.dirname(__file__))
# NOTICE:  путь для библиотеки. Указан относительный путь при сборке cmake в папку .build_w64
lb = cdll.LoadLibrary(os.path.join(me, "../../.build_w64/lab_12/lab_12_03_2", "liblab_12_03_2.dll"))

copy = lb.copy
copy.restype = c_longlong
copy.argtypes = [POINTER(c_longlong), c_longlong, POINTER(c_longlong), c_longlong]


class CopyLibrary(unittest.TestCase):
    def test_preallocate(self):
        dst = (c_longlong * 256)()
        src = (c_longlong * 8)(1, 2, 1, 2, 2, 3, 2, 4)
        ret = copy(dst, 256, src, 8)
        self.assertEqual(ret, 4)
        self.assertEqual(dst[0], 1)
        self.assertEqual(dst[1], 2)
        self.assertEqual(dst[2], 3)
        self.assertEqual(dst[3], 4)

    def test_postallocate(self):
        src = (c_longlong * 8)(1, 2, 1, 2, 2, 3, 2, 4)
        length = copy(None, 0, src, 8)
        self.assertEqual(length, 4)
        dst = (c_longlong * length)()
        ret = copy(dst, length, src, 8)
        self.assertEqual(ret, length)
        self.assertEqual(dst[0], 1)
        self.assertEqual(dst[1], 2)
        self.assertEqual(dst[2], 3)
        self.assertEqual(dst[3], 4)


if __name__ == '__main__':
    unittest.main()
