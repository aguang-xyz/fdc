aux_source_directory(. SRCS)

add_library(fdc ${SRCS})

install(TARGETS fdc DESTINATION bin)

install(FILES fdc.h DESTINATION include)
