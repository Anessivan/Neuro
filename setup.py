import pybind11
from distutils.core import setup, Extension

ext_modules = [
    Extension(
        'ensemble', 
        ['src/Source.cpp'], 
        include_dirs=[pybind11.get_include()],  
        language='c++', 
        extra_compile_args=['-std=c++17'],
        extra_link_args=[]
    ),
]

setup(
    name='ensemble', 
    version='1.0.1',
    ext_modules=ext_modules,
    requires=['pybind11'],  
)
