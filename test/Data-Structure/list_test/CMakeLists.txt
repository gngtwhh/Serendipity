cmake_minimum_required(VERSION 3.15)

project(adt_list_test)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../../../include")

set(
    source_file_path
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../src/
)

add_executable(
    adt_list_test
    main.c
    ${source_file_path}/adt/list.c
)