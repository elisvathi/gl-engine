cmake_minimum_required(VERSION 2.8.12)
project(GPU_Engine)

add_definitions("-std=c++11")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
file(COPY assets DESTINATION ${CMAKE_BINARY_DIR}/bin)
conan_basic_setup()

add_executable(GEngine main.cpp)
target_link_libraries(GEngine ${CONAN_LIBS})
