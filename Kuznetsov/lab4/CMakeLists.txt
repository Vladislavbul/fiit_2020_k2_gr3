cmake_minimum_required(VERSION 3.6 FATAL_ERROR)

project(samples)

include(cmake/function.cmake)

add_subdirectory(polinomial_lib)
add_subdirectory(main)

option(BTEST "build test?" OFF)

if(BTEST)
    add_subdirectory(gtest)
    add_subdirectory(test)
endif()
