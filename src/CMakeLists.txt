
add_executable(frankenstein main.cpp)
add_subdirectory(dependencies)
add_subdirectory(engine)
target_link_libraries(frankenstein PRIVATE SDL2 toml11::toml11 engine)
target_compile_options(frankenstein PRIVATE -Wall)



# adding tests
