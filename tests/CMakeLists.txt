add_subdirectory(dependencies)

enable_testing()
add_executable(tests test_engine.cpp)
target_link_libraries(tests GTest::gtest_main toml11::toml11 engine)

include(GoogleTest)
gtest_discover_tests(tests)