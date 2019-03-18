cmake_minimum_required(VERSION 3.12)
project(url_compress)

set(CMAKE_CXX_STANDARD 14)

# gtest
include_directories(
    thirdparty/googletest/googletest/include
    thirdparty/googletest/googletest)
add_subdirectory(thirdparty/googletest)

add_library(url_compress
    avl_tree.h
    avl_tree.cc
    compressed_url_array.cc
    compressed_url_array.h
    utility.h)