cmake_minimum_required(VERSION 3.26)
project(glsl_learning)

set(CMAKE_CXX_STANDARD 17)

include_directories(GL/include)

add_executable(glsl_learning main.cpp
        GL/src/glad.c
        glad/glad.h)

find_package(glm CONFIG REQUIRED)
target_link_libraries(glsl_learning PRIVATE glm::glm)

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(glsl_learning PRIVATE glfw)
