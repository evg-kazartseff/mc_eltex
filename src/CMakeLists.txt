add_subdirectory(graphic)
add_subdirectory(core)
add_executable(${CMAKE_PROJECT_NAME} main.c)
target_link_libraries(${CMAKE_PROJECT_NAME} core)