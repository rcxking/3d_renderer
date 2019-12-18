# CMakeLists.txt

# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

project(3D_Renderer)

# Use C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Clock Application
add_executable(Clock 
  applications/clock/clock.cpp
)
target_include_directories(Clock PUBLIC
  src
)

# Cannon Application
add_executable(Cannon
  applications/cannon/cannon.cpp
)
target_include_directories(Cannon PUBLIC
  src
)

# Catch Unit Tests
find_package(Catch2 REQUIRED)
add_executable(Tests
  tests/test.cpp
)
target_include_directories(Tests PUBLIC
  src
)
target_link_libraries(Tests Catch2::Catch2)
include(CTest)
include(Catch)
catch_discover_tests(Tests)