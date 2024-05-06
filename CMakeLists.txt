cmake_minimum_required(VERSION 3.26)
project(glsl_learning)

set(CMAKE_CXX_STANDARD 17)

include_directories(GL/include)

add_executable(glsl_learning main.cpp
        GL/src/glad.c
        GL/include/glad/glad.h
        setup.h
        setup.cpp
        vertex_buffer_creator.h
        vertex_buffer_creator.h
        vertex_buffer_creator.cpp
        scenes/spinning_triangle.cpp
        scenes/fragment_circle.cpp)

find_package(glm CONFIG REQUIRED)
target_link_libraries(glsl_learning PRIVATE glm::glm)

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(glsl_learning PRIVATE glfw)
