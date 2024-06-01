cmake_minimum_required(VERSION 3.15)

project(encode_hex_test)

include_directories("../../../include")

set(
    source_file_path
        ../../../src
)

add_executable(
    sha2_test
        main.c
    ${source_file_path}/digest/sha2.c
    ${source_file_path}/encode/hex.c
)