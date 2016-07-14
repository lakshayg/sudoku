cmake_minimum_required(VERSION 2.8)
project(sudoku)

add_subdirectory(minisat EXCLUDE_FROM_ALL)
include_directories(minisat)

set(CMAKE_CXX_FLAGS "-Wall -pedantic -std=c++11 -O2")
add_executable(main src/main.cpp)
target_link_libraries(main minisat-lib-static)
