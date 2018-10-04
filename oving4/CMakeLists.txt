cmake_minimum_required(VERSION 3.10)
project(oving4)

set(CMAKE_CXX_STANDARD 14)

add_executable(del1.out del1.cpp NumberDoubleLinkedList.cpp NumberDoubleLinkedList.hpp)
add_executable(del1p del1.cpp NumberDoubleLinkedListPointer.cpp NumberDoubleLinkedList.hpp)
add_executable(del3.out del3.cpp)


