cmake_minimum_required(VERSION 3.6 FATAL_ERROR)

project(samples)

include(cmake/function.cmake)

add_subdirectory(stack_lib)
add_subdirectory(main)
