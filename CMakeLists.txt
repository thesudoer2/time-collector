cmake_minimum_required(VERSION 3.22)

project(time_calculator CXX)

# options
option(ENABLE_TESTS "Set to ON to enable building of tests" OFF)

# sources
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(OUTPUT_NAME time_calculator)
set(PROJECT_SOURCE_DIR "src")

set(PROJECT_SOURCE_NO_MAIN
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Time.cpp
)

set(SRC_LIST
    ${PROJECT_SOURCE_NO_MAIN}
    src/main.cpp
)

# tests
if (ENABLE_TESTS)
    message(STATUS "Building of tests is enabled")
    add_compile_definitions(ENABLE_TEST)
    enable_testing()
    add_subdirectory(test)
endif()

add_executable(${OUTPUT_NAME} ${SRC_LIST})