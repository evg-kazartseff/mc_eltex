set(SOURCES core.c IOfile.c)
set(HEADERS core.h IOfile.h)

add_library(core_te ${SOURCES} ${HEADERS})
target_link_libraries(core_te graphic_te)