cmake_minimum_required(VERSION 3.26)
project(frankenstein LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
add_executable(frankenstein main.cpp)
find_package(toml11 CONFIG REQUIRED)

target_link_libraries(frankenstein PRIVATE SDL2 toml11::toml11)
target_compile_options(frankenstein PRIVATE -Wall)

add_subdirectory(engine)
add_subdirectory(ecs)
add_subdirectory(core)