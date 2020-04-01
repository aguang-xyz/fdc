aux_source_directory(. SRCS)

add_library(fdc ${SRCS})

set_target_properties(fdc PROPERTIES PUBLIC_HEADER "fdc.h")

install(TARGETS fdc DESTINATION lib PUBLIC_HEADER DESTINATION include)

install(FILES fdc.h DESTINATION include RENAME fdc)
