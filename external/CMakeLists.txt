if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    message(STATUS "HAVE TO ADD SUPPORT OF TESTING")
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/googletest)
    include(CTest)
    if (BUILD_TESTING)
        add_executable(testing
                ${CMAKE_CURRENT_SOURCE_DIR}/../test/tests.cpp
        )

        target_include_directories(testing PUBLIC

        )
        target_link_libraries(testing PRIVATE
                GTest::gtest_main
                HashingUtils
                ConverterUtils
        )

        set_target_properties(testing PROPERTIES
                RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../build-test"
        )

        include(GoogleTest)
        gtest_discover_tests(testing)
    endif ()
else ()
    message(STATUS "DO NOT ADDING SUPPORT OF TESTING")
endif ()