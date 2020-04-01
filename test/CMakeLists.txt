include_directories(../src)

file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false *.h *.cpp)

add_executable(fdc-test ${TEST_SOURCES})

target_link_libraries(fdc-test fdc gtest)

add_test(NAME fdc-test COMMAND fdc-test)
