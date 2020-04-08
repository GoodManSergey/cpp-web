cmake_minimum_required(VERSION 3.8)

project(cpp_web)

file(GLOB_RECURSE SOURCE_FILES src/*.cpp)
add_executable(cpp_web ${SOURCE_FILES} src/ClientConnection/ClientConnection.cpp src/ClientConnection/ClientConnection.h)
target_compile_options(cpp_web PUBLIC -std=c++17)
