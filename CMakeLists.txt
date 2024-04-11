cmake_minimum_required(VERSION 3.15)
project(Serendipity)

# test executable file path
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# set include path
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_subdirectory(test/Data-Structure/list_test)
add_subdirectory(test/Encoding/base64)
add_subdirectory(test/Encoding/hex)
add_subdirectory(test/Encoding/MD5)
add_subdirectory(test/Encoding/MD4)
add_subdirectory(test/Encrypt/tea)
add_subdirectory(test/Encrypt/rc4)
add_subdirectory(test/Encrypt/SM4)