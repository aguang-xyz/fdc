cmake_minimum_required (VERSION 3.0)

project (fdc)

set(FDC_VERSION_MAJOR 1)
set(FDC_VERSION_MINOR 0)
set(FDC_VERSION_PATCH 0)


add_subdirectory(src)
add_subdirectory(test)

add_subdirectory(lib/gtest EXCLUDE_FROM_ALL)

enable_testing()
