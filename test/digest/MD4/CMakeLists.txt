cmake_minimum_required(VERSION 3.15)

project(encode_hex_test)

include_directories("../../../include")

set(
    source_file_path
        ../../../src
)

add_executable(
    md4_test
        main.c
    ${source_file_path}/digest/md4.c
    ${source_file_path}/encode/hex.c
)