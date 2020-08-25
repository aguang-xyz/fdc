include_directories(../../lib)

aux_source_directory(. SRCS)

add_library(fdc ${SRCS})

set_target_properties(fdc PROPERTIES PUBLIC_HEADER "fdc.h")

target_link_libraries(fdc ${CMAKE_SOURCE_DIR}/lib/glpk/libglpk.a)

install(TARGETS fdc DESTINATION lib PUBLIC_HEADER DESTINATION include)

install(FILES fdc.h DESTINATION include RENAME fdc)
