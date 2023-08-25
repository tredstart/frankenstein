
add_executable(frankenstein main.cpp)
add_subdirectory(dependencies)

target_link_libraries(frankenstein PRIVATE SDL2 toml11::toml11)
target_compile_options(frankenstein PRIVATE -Wall)

add_subdirectory(engine)
add_subdirectory(ecs)
add_subdirectory(core)

# adding tests
