cmake_minimum_required(VERSION 3.15)

project(encode_hex_test)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../../../include")

set(
    source_file_path
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../src/
)

add_executable(
    md4_test
    main.c
    ${source_file_path}/encode/md4.c
    ${source_file_path}/encode/hex.c
)