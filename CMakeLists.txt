cmake_minimum_required(VERSION 3.20)

project(Raytracer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_BUILD_TYPE Debug)

include_directories("${Raytracer_SOURCE_DIR}/include/")

file(GLOB SOURCE_FILES "${Raytracer_SOURCE_DIR}/src/*.cpp")

add_executable(raytracer ${SOURCE_FILES})
