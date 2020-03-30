aux_source_directory(. SRCS)

add_library(fdc ${SRCS})

set_target_properties(fdc PROPERTIES PUBLIC_HEADER "fdc.hpp")

install(TARGETS fdc DESTINATION lib PUBLIC_HEADER DESTINATION include)

install(FILES fdc.hpp DESTINATION include RENAME fdc)
