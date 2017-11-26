set(SOURCES core.c)
set(HEADERS core.h)

add_library(core ${SOURCES} ${HEADERS})
target_link_libraries(core graphic)