cmake_minimum_required(VERSION 2.8)
project(UnitTests)

# Include headers and sources
include_directories("../src")
set(SRCS test.cpp)
set(TUPLETESTSRCS TupleTest.cpp)

add_executable(UnitTests ${SRCS})
add_executable(TupleTest ${TUPLETESTSRCS})

# Catch2 unit test framework
find_package(Catch2 REQUIRED)
target_link_libraries(UnitTests Catch2::Catch2)
target_link_libraries(TupleTest Catch2::Catch2)
