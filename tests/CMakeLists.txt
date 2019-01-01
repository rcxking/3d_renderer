cmake_minimum_required(VERSION 2.8)
project(UnitTests)

# Include headers and sources
include_directories("../src")
set(SRCS test.cpp)

# Catch unit test framework
find_package(Catch2 REQUIRED)

add_executable(UnitTests ${SRCS})

target_link_libraries(UnitTests Catch2::Catch2)
