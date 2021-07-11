from distutils.core import setup, Extension
from Cython.Build import cythonize

setup(
	name="timsort",
	ext_modules=[Extension(name="timsort_cpp", sources=["timsort_cpp.cpp"])]
)

setup(
	name="timsort",
    ext_modules=cythonize("timsort_cython.pyx")
)