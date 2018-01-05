set(SOURCES core.c)
set(HEADERS core.h)

add_library(core_mc ${SOURCES} ${HEADERS})
target_link_libraries(core_mc graphic_mc)