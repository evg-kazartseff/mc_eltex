add_subdirectory(graphic_mc)
add_subdirectory(core_mc)
add_executable(my_mc main.c)
target_link_libraries(my_mc core_mc)