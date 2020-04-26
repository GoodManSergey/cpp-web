cmake_minimum_required(VERSION 3.8)

project(cpp_web)

file(GLOB_RECURSE SOURCE_FILES src/*.cpp src/*/*.cpp src/*/*/*.cpp)
add_executable(cpp_web ${SOURCE_FILES})
find_package (Threads)
target_link_libraries (cpp_web Threads::Threads)
target_compile_options(cpp_web PUBLIC -std=c++17)
