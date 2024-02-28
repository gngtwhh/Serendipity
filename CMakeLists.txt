cmake_minimum_required(VERSION 3.15)
project(Serendipity)

# test executable file path
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# set include path
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_subdirectory(test/Data-Structure/list_test)
add_subdirectory(test/Encoding/base64)