
add_executable(frankenstein main.cpp)
add_subdirectory(dependencies)
add_subdirectory(engine)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
target_link_libraries(frankenstein PRIVATE SDL2 SDL2_image toml11::toml11 engine)
target_compile_options(frankenstein PRIVATE -Wall)
