add_executable(converter_tests
    converter_tests.cpp
)

target_link_libraries(converter_tests PRIVATE
    converter
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(converter_tests)


