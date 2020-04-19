# CMake version requirement.
cmake_minimum_required (VERSION 3.0)

# Project name.
project (fdc)

# Turn on unit test.
enable_testing()

# Version.
set(FDC_VERSION_MAJOR 1)
set(FDC_VERSION_MINOR 0)
set(FDC_VERSION_PATCH 1)

# Turn on compiler's optimization for execution time.
set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -O3")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

# Source.
add_subdirectory(src)

# Test.
add_subdirectory(test)

# Google Test Framework.
add_subdirectory(lib/gtest EXCLUDE_FROM_ALL)
