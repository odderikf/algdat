cmake_minimum_required(VERSION 3.10)
project(oving12)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost COMPONENTS filesystem system REQUIRED)

add_library(huffman_tree STATIC huffman_tree.cpp)
add_executable(compress compress.cpp)
add_executable(decompress decompress.cpp)
add_executable(t test.cpp)

target_compile_options(compress PRIVATE -lboost_filesystem -lboost_system -Wall -Wextra -pedantic -Werror -Wno-reorder -Wno-unused)
target_compile_options(decompress PRIVATE -lboost_filesystem -lboost_system -Wall -Wextra -pedantic -Werror -Wno-reorder -Wno-unused)

target_link_libraries(compress
        ${Boost_FILESYSTEM_LIBRARY}
        ${Boost_SYSTEM_LIBRARY}
        huffman_tree
)
target_link_libraries(decompress
        ${Boost_FILESYSTEM_LIBRARY}
        ${Boost_SYSTEM_LIBRARY}
        huffman_tree
)
target_link_libraries(t
        ${Boost_FILESYSTEM_LIBRARY}
        ${Boost_SYSTEM_LIBRARY}
        huffman_tree
        )
