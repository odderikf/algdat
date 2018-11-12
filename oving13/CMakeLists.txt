cmake_minimum_required(VERSION 3.10)
project(oving13)

set(CMAKE_CXX_STANDARD 17)

add_executable(oving13 main.cpp dijkstra.cpp graph.cpp)

target_compile_options(oving13 PRIVATE -O3 -Wall -Wextra -pedantic -Werror -Wno-reorder -Wno-unused)

