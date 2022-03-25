import pybind11
from distutils.core import setup, Extension

ext_modules = [
    Extension(
        'ensemble', # имя библиотеки собранной pybind11
        ['src/Source.cpp'], # Тестовый файлик который компилируем
        include_dirs=[pybind11.get_include()],  # не забываем добавить инклюды pybind11
        language='c++', # Указываем язык
        extra_compile_args=['-std=c++17'], # флаг с++11
        extra_link_args=[]
    ),
]

setup(
    name='ensemble', # имя библиотеки собранной pybind11
    version='1.0.0',
    # author='maxkost',
    # author_email='maximkostyukov@yandex.ru',
    # description='numerical methods extension',
    ext_modules=ext_modules,
    requires=['pybind11'],  # Указываем зависимость от pybind11
)