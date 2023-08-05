cmake_minimum_required(VERSION 3.26)
project(c_engine C)

set(CMAKE_C_STANDARD 23)



add_executable(c_engine main.c
        systems.h
        systems.c
        vector.c
        vector.h
        components.c
        components.h
        )
target_link_libraries(c_engine SDL2)
