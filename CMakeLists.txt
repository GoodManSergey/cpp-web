cmake_minimum_required(VERSION 3.8)

project(cpp_web)

file(GLOB_RECURSE SOURCE_FILES src/*.cpp src/*/*.cpp src/*/*/*.cpp)
add_library(cpp_web STATIC ${SOURCE_FILES})
find_package (Threads)
target_link_libraries (cpp_web Threads::Threads)
target_compile_options(cpp_web PUBLIC -std=c++17)
INSTALL(EXPORT cpp_web
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/cpp_web
        FILE        cpp_web.cmake)
