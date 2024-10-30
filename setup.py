from distutils.core import setup
from Cython.Build import cythonize
from distutils.extension import Extension
import numpy


setup(ext_modules=cythonize("my_python_module.py"),include_dirs=[numpy.get_include()])
