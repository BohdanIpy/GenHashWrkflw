cmake_minimum_required(VERSION 3.29)

set(MAJOR_VERSION 1)
set(MINOR_VERSION 0)
set(PATCH_VERSION 5)

set(VERS "${MAJOR_VERSION}.${MINOR_VERSION}.${PATCH_VERSION}")

project(hashing VERSION ${VERS})

configure_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/version.h.in"
        "${CMAKE_CURRENT_BINARY_DIR}/version.h"
)

set(CMAKE_CXX_STANDARD 23)

message(STATUS ${CMAKE_BUILD_TYPE})

find_package(OpenSSL REQUIRED)

add_library(HashingUtils INTERFACE)
target_include_directories(HashingUtils INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/HashingUtils
)
target_link_libraries(HashingUtils INTERFACE
        ssl
        crypto
)

add_library(ConverterUtils INTERFACE)
target_include_directories(HashingUtils INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/ConverterUtils
)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/external)

add_executable(hashing ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_BINARY_DIR}
)

target_link_libraries(${PROJECT_NAME} PUBLIC
        HashingUtils
        ConverterUtils
)
