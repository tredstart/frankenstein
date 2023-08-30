FetchContent_Declare(toml11
        GIT_REPOSITORY https://github.com/ToruNiina/toml11.git
        GIT_TAG v3.7.1
)
FetchContent_MakeAvailable(toml11)

FetchContent_Declare(
        Box2D
        GIT_REPOSITORY https://github.com/erincatto/box2d.git
        GIT_TAG v2.4.1
)
FetchContent_MakeAvailable(Box2D)

FetchContent_Declare(
        SFML
        URL https://github.com/SFML/SFML/archive/refs/tags/2.6.0.zip
)
FetchContent_MakeAvailable(SFML)

FetchContent_Declare(
        lua
        URL https://github.com/lua/lua/archive/refs/tags/v5.4.6.tar.gz
)
FetchContent_MakeAvailable(lua)

FetchContent_Declare(
        sol2
        URL https://github.com/ThePhD/sol2/archive/refs/tags/v3.3.0.tar.gz
)
FetchContent_MakeAvailable(sol2)
