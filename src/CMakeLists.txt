cmake_minimum_required (VERSION 3.0)

project (fdc)

set(FDC_VERSION_MAJOR 1)
set(FDC_VERSION_MINOR 0)
set(FDC_VERSION_PATCH 0)

add_subdirectory(./fdc)

add_executable(fdc-cli ./fdc-cli.cpp)

target_link_libraries(fdc-cli fdc)

install(TARGETS fdc-cli DESTINATION bin)

