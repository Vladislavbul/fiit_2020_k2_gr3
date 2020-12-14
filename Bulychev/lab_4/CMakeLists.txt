cmake_minimum_required(VERSION 3.6 FATAL_ERROR)

project(polynom)

include(cmake/function.cmake)

add_subdirectory(library)
add_subdirectory(main)

option(BTEST "build test?" OFF)

if(BTEST)
    add_subdirectory(gtest)
    
endif()
