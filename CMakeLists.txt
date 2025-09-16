cmake_minimum_required(VERSION 3.15)

project(UnitConverterAI LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Library with conversion logic
add_library(converter
    src/converter.cpp
)
target_include_directories(converter PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Executable
add_executable(unit_converter
    src/main.cpp
)
target_link_libraries(unit_converter PRIVATE converter)

enable_testing()

# Try to locate an installed GoogleTest per user instruction
option(ENABLE_TESTS "Build GoogleTest-based tests" ON)
find_package(GTest QUIET)
if(GTest_FOUND AND ENABLE_TESTS)
    message(STATUS "Found GTest: ${GTest_DIR}")
    add_subdirectory(tset)
elseif(NOT GTest_FOUND)
    message(WARNING "GTest not found by find_package(GTest). Ensure GoogleTest is installed and visible to CMake. Skipping tests.")
else()
    message(STATUS "Tests are disabled (ENABLE_TESTS=OFF). Skipping test targets.")
endif()


