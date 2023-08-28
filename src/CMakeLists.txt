
add_executable(frankenstein main.cpp)
add_subdirectory(dependencies)
add_subdirectory(engine)

target_link_libraries(frankenstein PUBLIC sfml-graphics sfml-audio sfml-window sfml-system toml11::toml11 engine)
target_compile_options(frankenstein PUBLIC -Wall)
