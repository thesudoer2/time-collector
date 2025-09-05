cmake_minimum_required(VERSION 3.22)
project(time_collector_tests LANGUAGES CXX)

message(STATUS "===================== Configuring ${PROJECT_NAME} =====================")

# Find helper modules from repo root (optional)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
include(Helpers OPTIONAL)

include(${CMAKE_CURRENT_LIST_DIR}/ResourcesList.cmake OPTIONAL)

include(FetchContent)
set(GTEST_VERSION v1.14.0)

set(GTEST_LIBRARIES)
add_gtest_requirements(GTEST_LIBRARIES)

add_executable(unit_tests
    ${TEST_SOURCES}
)

target_include_directories(unit_tests PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/src
)

if (TARGET time)
    target_link_libraries(unit_tests PRIVATE time)
endif()
if (TARGET grammar)
    target_link_libraries(unit_tests PRIVATE grammar)
endif()

target_link_libraries(unit_tests PRIVATE
    GTest::gtest
    GTest::gtest_main
    GTest::gmock
)

foreach(RES ${TIME_COLLECTOR_TEST_NON_CODE_RESOURCES})
  get_filename_component(RES_DIR "${RES}" PATH)
  add_custom_command(TARGET unit_tests POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory
            "$<TARGET_FILE_DIR:unit_tests>/test-data/${RES_DIR}"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${RES}" "$<TARGET_FILE_DIR:unit_tests>/test-data/${RES_DIR}"
    VERBATIM
  )
endforeach()

# Register the test with CTest
add_test(NAME unit_tests COMMAND unit_tests)

include(GoogleTest)

message(STATUS "===================== Finished ${PROJECT_NAME} =====================")
