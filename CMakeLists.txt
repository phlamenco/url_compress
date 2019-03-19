cmake_minimum_required(VERSION 3.12)
project(url_compress)

set(CMAKE_CXX_STANDARD 14)

# gtest
include_directories(
    thirdparty/googletest/googletest/include
    thirdparty/googletest/googletest)
add_subdirectory(thirdparty/googletest)

add_library(url_compress
    avl_tree_compression.h
    avl_tree_compression.cc
    url_block.cc
    url_block.h
    utility.h)

add_executable(url_block_test
    url_block_test.cc)

target_link_libraries(url_block_test
    url_compress
    gtest
    gtest_main)

add_executable(avl_tree_compression_test
    avl_tree_compression_test.cc)
target_link_libraries(avl_tree_compression_test
    url_compress
    gtest
    gtest_main)