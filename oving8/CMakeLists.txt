cmake_minimum_required(VERSION 3.10)
project(oving8)

set(CMAKE_CXX_FLAGS "-fpermissive")
set(CMAKE_CXX_STANDARD 17)

add_executable(oving8.out main.cpp ../mylib/graph.cpp ../mylib/dijkstra.cpp)
add_compile_options(oving8 -O3 -Wall -Wextra)
