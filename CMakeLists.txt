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
target_compile_options(Clock PRIVATE -Wall -Werror)
target_include_directories(Clock PUBLIC
  src
)

# Cannon Application
add_executable(Cannon
  applications/cannon/cannon.cpp
)
target_compile_options(Cannon PRIVATE -Wall -Werror)
target_include_directories(Cannon PUBLIC
  src
)

# SphereCast Application
add_executable(SphereCast
  applications/spherecast/spherecast.cpp
)
target_compile_options(SphereCast PRIVATE -Wall -Werror)
target_include_directories(SphereCast PUBLIC
  src
)

# ShadedSphere Application
add_executable(ShadedSphere
  applications/shadedsphere/shadedsphere.cpp
)
target_compile_options(ShadedSphere PRIVATE -Wall -Werror)
target_include_directories(ShadedSphere PUBLIC
  src
)

# Catch Unit Tests
find_package(Catch2 REQUIRED)
add_executable(Tests
  tests/test.cpp
)
target_compile_options(Tests PRIVATE -Wall -Werror)
target_include_directories(Tests PUBLIC
  src
)
target_link_libraries(Tests Catch2::Catch2)
include(CTest)
include(Catch)
catch_discover_tests(Tests)
