cmake_minimum_required(VERSION 3.29)
project(hashing)

set(CMAKE_CXX_STANDARD 23)

find_package(OpenSSL REQUIRED)

add_executable(hashing main.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC
        ${OPENSSL_INCLUDE_DIR}
)
target_link_libraries(${PROJECT_NAME} PUBLIC
        #${OPENSSL_LIBRARIES}
        ssl
        crypto
)
