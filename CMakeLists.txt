cmake_minimum_required(VERSION 3.26)
project(frankenstein C)

set(CMAKE_C_STANDARD 23)

add_executable(frankenstein main.c)
target_link_libraries(frankenstein SDL2)
add_subdirectory(ecs)
add_subdirectory(core)