cmake_minimum_required (VERSION 3.0)

project (fdc)

add_subdirectory(./fdc)

add_executable(fdc-cli ./fdc-cli.cpp)

target_link_libraries(fdc-cli fdc)

install(TARGETS fdc-cli DESTINATION bin)


