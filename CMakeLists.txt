cmake_minimum_required(VERSION 3.26)
project(OpenGL)

set(CMAKE_CXX_STANDARD 11)

add_executable(OpenGL
        src/Shader.h
        src/main.cpp
        src/Utils.h
        src/Shader.cpp
)

include_directories("${CMAKE_SOURCE_DIR}/ThirdParty/include")

if (WIN32)
    target_link_libraries(OpenGL "${CMAKE_SOURCE_DIR}/ThirdParty/win32-libs/glfw3dll.lib")
    set(CMAKE_CXX_FLAGS "-static -static-libstdc++ -static-libgcc")

endif ()
