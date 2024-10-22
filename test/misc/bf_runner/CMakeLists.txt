cmake_minimum_required(VERSION 3.15)

project(misc_bf_runner_test)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../../../include")

set(
        source_file_path
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../src/
)

add_executable(
        bf_runner_test
        main.c
        ${source_file_path}/misc/bf_runner/bf.c
)