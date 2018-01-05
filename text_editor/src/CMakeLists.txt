add_subdirectory(graphic_te)
add_subdirectory(core_te)
add_executable(te main.c)
target_link_libraries(te core_te)
