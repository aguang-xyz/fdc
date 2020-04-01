add_subdirectory(./fdc)

add_executable(fdc-cli ./main.cpp)

target_link_libraries(fdc-cli fdc)

install(TARGETS fdc-cli DESTINATION bin)
