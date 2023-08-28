add_library(engine engine.cpp engine.h)
add_subdirectory(ecs)
add_subdirectory(core)
target_link_libraries(engine PUBLIC toml11::toml11)