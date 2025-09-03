function(create_gtest_files)
    cmake_parse_arguments(
        ARGS        # Prefix
        ""          # Options
        ""          # List of names of single-value arguments
        "PROJECT_TEST_CPP_LIST;PROJECT_TEST_HEADER_LIST;PROJECT_TEST_LINKED_LIBRARIES"
        ${ARGS}
    )

    message(STATUS "Adding tests")

    foreach(TEST_CASE ${ARGS_PROJECT_TEST_CPP_LIST})
        # Get filename without extension
        get_filename_component(TEST_CASE_NAME_WITHOUT_EXTENSION ${TEST_CASE} NAME_WE)

        # Get innermost directory name
        get_filename_component(TEST_CASE_DIRECTORY ${TEST_CASE} PATH)
        get_filename_component(TEST_CASE_INNERMOST_DIRECTORY ${TEST_CASE_DIRECTORY} NAME_WE)

        # Construct executable name
        set(EXEC_NAME "${TEST_CASE_INNERMOST_DIRECTORY}_${TEST_CASE_NAME_WITHOUT_EXTENSION}")

        # Construct test name
        set(TEST_NAME "${EXEC_NAME}_TEST")

        # Add executable and test
        add_executable(${EXEC_NAME} ${TEST_CASE} ${ARGS_PROJECT_TEST_HEADER_LIST})
        target_link_libraries(${EXEC_NAME} ${ARGS_PROJECT_TEST_LINKED_LIBRARIES})
        add_test(${TEST_NAME} ${EXEC_NAME})
    endforeach()
endfunction()

function(add_gtest_subdirectory IS_GOOGLETEST_FOUND)
    if (EXISTS /usr/src/googletest)
        add_subdirectory(/usr/src/googletest ${CMAKE_BINARY_DIR}/googletest)
    elseif (EXISTS /usr/src/gmock)
        add_subdirectory(/usr/src/gmock ${CMAKE_BINARY_DIR}/gmock)
    elseif (EXISTS /usr/src/gtest)
        add_subdirectory(/usr/src/gtest ${CMAKE_BINARY_DIR}/gtest)
    else()
        set(IS_GOOGLETEST_FOUND FALSE PARENT_SCOPE)
        return()
    endif()
    set(IS_GOOGLETEST_FOUNC TRUE PARENT_SCOPE)
endfunction()

function(add_gtest_requirements GOOGLETEST_REQUIRED_LIBRARIES)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-undef")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-missing-field-initializers")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-format-nonliteral")

    if (NOT (ENVIRONMENT STREQUAL "LINUX")) # Windows
        find_package(GTest REQUIRED)
        find_package(GMock REQUIRED)
        set(${GOOGLETEST_REQUIRED_LIBRARIES} GTest::GTest GTest::Main ${GMOCK_BOTH_LIBRARIES} PARENT_SCOPE)
        return()
    endif()

    if ((NOT TARGET gtest) AND (NOT TARGET gmock))
        add_gtest_subdirectory(IS_GOOGLETEST_FOUND)
        if (NOT IS_GOOGLETEST_FOUND)
            message(FATAL_ERROR "Googletest not found. Please install libgtest-dev and googletest")
            return()
        endif()
    endif()

    set(${GOOGLETEST_REQUIRED_LIBRARIES} gtest gmock gtest_main gmock_main PARENT_SCOPE)
endfunction()