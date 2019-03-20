cmake_minimum_required(VERSION 3.12)
project(url_compress)

set(CMAKE_CXX_STANDARD 14)

# test function
function(DO_GTEST)
  set(options OPTIONAL FAST)
  set(oneValueArgs NAME TESTDATA)
  set(multiValueArgs DEPS SRCS)
  cmake_parse_arguments(DO_GTEST "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
  add_executable(${DO_GTEST_NAME}
      ${DO_GTEST_NAME}.cc ${DO_GTEST_SRCS})
  target_link_libraries(${DO_GTEST_NAME}
      ${DO_GTEST_DEPS}
      gtest
      gtest_main)
  if (DO_GTEST_TESTDATA)
    message(STATUS "coping testdata: ${CMAKE_CURRENT_SOURCE_DIR}/${DO_GTEST_TESTDATA}")
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/${DO_GTEST_TESTDATA} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)
  endif()
endfunction()

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
    node_array.cc
    node_array.h
    url_retrieve.cc
    url_retrieve.h
    utility.h)

DO_GTEST(NAME url_block_test DEPS url_compress)
DO_GTEST(NAME avl_tree_compression_test DEPS url_compress)
DO_GTEST(NAME url_retrieve_test DEPS url_compress)
