cmake_minimum_required(VERSION 3.15)
project(Serendipity)

# test executable file path
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# set include path
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Data-Structure
add_subdirectory(test/Data-Structure/list_test)

# Encoding
add_subdirectory(test/Encoding/base64)
add_subdirectory(test/Encoding/hex)
add_subdirectory(test/Encoding/morse)

# Digest
add_subdirectory(test/digest/MD5)
add_subdirectory(test/digest/MD4)
add_subdirectory(test/digest/SHA2)

# Encrypt
add_subdirectory(test/Encrypt/tea)
add_subdirectory(test/Encrypt/rc4)
add_subdirectory(test/Encrypt/SM4)