cmake_minimum_required(VERSION 3.6)
project(asteroids CXX)

add_subdirectory(thirdparty/googletest)

include(cmake/settings.cmake)
config_compiler_and_linker()

add_subdirectory(src)
add_subdirectory(test)

set(SOURCE_FILES main.cpp)
cxx_executable(asteroids
        asteroids_lib
        ${SOURCE_FILES})
