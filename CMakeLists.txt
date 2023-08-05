cmake_minimum_required(VERSION 3.26)
project(c_engine C)

set(CMAKE_C_STANDARD 23)

add_executable(c_engine main.c)
target_link_libraries(c_engine SDL2)
add_subdirectory(ecs)
add_subdirectory(core)