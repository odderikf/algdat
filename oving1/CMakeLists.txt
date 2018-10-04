cmake_minimum_required(VERSION 3.5)
project(oving1)

set(CMAKE_CXX_STANDARD 17)
SET(MY_LIB_DIR "../mylib/")

add_executable(oving1 main.cpp)

target_include_directories(oving1 PRIVATE ${MY_LIB_DIR})