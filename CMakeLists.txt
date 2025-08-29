cmake_minimum_required(VERSION 3.22)

project(time_calculator CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(OUTPUT_NAME time_calculator)

set(PROJECT_SOURCES
    src/main.cpp
    src/Time.cpp
)

add_executable(${OUTPUT_NAME} ${PROJECT_SOURCES})