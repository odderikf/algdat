cmake_minimum_required(VERSION 3.5)
project(oving2)
set(CMAKE_CXX_STANDARD 17)

add_executable(oving2 svar.cpp)

add_compile_options(-I/usr/include/python3.5)
