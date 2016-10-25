cmake_minimum_required(VERSION 3.5)
project(asteroids CXX)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Limited Configs" FORCE)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

add_subdirectory(thirdparty/googletest)

include_directories(thirdparty/stb)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

find_package(glbinding REQUIRED)

find_package(GLM REQUIRED)
include_directories(${GLM_INCLUDE_DIR})

find_package(POCO REQUIRED)
include_directories(${Poco_INCLUDE_DIRS})

include(cmake/settings.cmake)
config_compiler_and_linker()
enable_testing()

add_definitions(-DASTEROIDS_BASE_DIR="${CMAKE_CURRENT_SOURCE_DIR}")

add_subdirectory(src)
add_subdirectory(test)

set(SOURCE_FILES main.cpp)
cxx_executable(asteroids asteroids_lib ${SOURCE_FILES})
target_link_libraries(asteroids ${SDL2_LIBRARY})
target_link_libraries(asteroids ${OPENGL_LIBRARIES})
target_link_libraries(asteroids ${Poco_Foundation_LIBRARY})
target_link_libraries(asteroids glbinding::glbinding)
