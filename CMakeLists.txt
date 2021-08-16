cmake_minimum_required(VERSION 3.20)
project(cDetectron)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})


include_directories(./include/)
include_directories(./include/imgui/)

add_subdirectory(../../ThirdPartySoftwares/glfw-3.3.4 cmake-build-debug)

add_executable(cDetectron main.cpp src/glad.c include/ShaderManager.h include/stb_image.h include/CameraManager.h include/CoordSystem.h include/GeneralBox.h include/LightSource.h include/PlaneTextured.h include/TextureManager.h include/Setup.h include/Line.h include/Mesh.h include/Model.h)

add_library(imgui STATIC
        src/imgui.cpp
        src/imgui_demo.cpp
        src/imgui_draw.cpp
        src/imgui_impl_glfw.cpp
        src/imgui_impl_opengl3.cpp
        src/imgui_tables.cpp
        src/imgui_widgets.cpp
        src/glad.c
)


target_link_libraries(cDetectron glfw)
target_link_libraries(cDetectron assimp)
target_link_libraries(cDetectron imgui)
