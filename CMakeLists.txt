project(my_mc)

cmake_minimum_required(VERSION 3.8)

set(CMAKE_C_STANDARD 11)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/lib)

link_libraries(panel ncurses)

add_subdirectory(src)