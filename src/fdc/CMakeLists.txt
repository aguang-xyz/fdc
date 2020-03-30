aux_source_directory(. SRCS)

add_library(fdc SHARED ${SRCS})

set_target_properties(fdc PROPERTIES PUBLIC_HEADER "fdc.hpp")

install(TARGETS fdc
        LIBRARY DESTINATION lib
        PUBLIC_HEADER DESTINATION include)

install(FILES fdc.hpp DESTINATION include RENAME fdc)
