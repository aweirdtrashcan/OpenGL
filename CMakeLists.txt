cmake_minimum_required(VERSION 3.26)
project(OpenGL)

set(CMAKE_CXX_STANDARD 20)

add_executable(OpenGL
        src/core/Shader.h
        src/main.cpp
        src/core/Utils.h
        src/core/Shader.cpp
        src/includes.h
        src/core/Image.cpp
        src/core/Image.h
        src/core/Texture.cpp
        src/core/Texture.h
        src/core/io/Keyboard.cpp
        src/core/io/Keyboard.h
        src/core/io/Mouse.cpp
        src/core/io/Mouse.h
        src/core/io/Joystick.cpp
        src/core/io/Joystick.h
        src/core/Camera.cpp
        src/core/Camera.h)

include_directories("${CMAKE_SOURCE_DIR}/ThirdParty/include")
include_directories("${CMAKE_SOURCE_DIR}/src")

if (WIN32)
    target_link_libraries(OpenGL "${CMAKE_SOURCE_DIR}/ThirdParty/win32-libs/libglfw3.a")
    set(CMAKE_CXX_FLAGS "-static -static-libstdc++ -static-libgcc")

elseif (LINUX)
    target_link_libraries(OpenGL glfw)
endif ()
