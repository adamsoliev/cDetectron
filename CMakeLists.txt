cmake_minimum_required(VERSION 3.20)
project(cDetectron)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})


include_directories(./include/)

add_subdirectory(../../ThirdPartySoftwares/glfw-3.3.4 cmake-build-debug)

add_executable(cDetectron main.cpp src/glad.c)

target_link_libraries(cDetectron glfw)
