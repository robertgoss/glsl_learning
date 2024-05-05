#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

int main() {
    std::cout << "Hello, World!" << std::endl;

    if(!glfwInit()) {
        std::cerr << "Unable to init glfw!" << std::endl;
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(800, 600, "GLSL Learning", nullptr, nullptr);
    if(!window) {
        std::cerr << "Unable to load open window!" << std::endl;
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent( window );

    if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cerr << "Unable to load OpenGL functions!" << std::endl;
        exit(EXIT_FAILURE);
    }
    return 0;
}
