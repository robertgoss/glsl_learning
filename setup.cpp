#include "setup.h"

#include <fstream>
#include <iostream>

#include <GLFW/glfw3.h>

std::string loadShaderAsString(const std::string& path) {
    std::string fullPath = "../shaders/" + path;
    std::fstream file(fullPath, std::ios_base::in);
    std::string str((std::istreambuf_iterator<char>(file)),
                    std::istreambuf_iterator<char>());
    return str;
}

GLuint loadShader(const std::string& path, uint64_t shaderType) {
    // Create a vertex shader
    GLuint shader = glCreateShader(shaderType);
    if (shader == 0) {
        std::cerr << "Unable to create shader - " << path << std::endl;
        exit(EXIT_FAILURE);
    }
    // Load the shader code
    std::string shaderCode = loadShaderAsString(path);
    const GLchar* codeArray[] = {shaderCode.c_str()};
    glShaderSource(shader, 1, codeArray, nullptr);
    glCompileShader(shader);
    // Check the status
    GLint result;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        std::cerr << "Shader compilation failed - " << path << std::endl;
        // Get and print the log info
        GLint logLen;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLen);
        if (logLen > 0) {
            std::string log(logLen, ' ');
            GLsizei written;
            glGetShaderInfoLog(shader, logLen, &written, log.data());
            std::cerr << "Shader log: " << std::endl << log << std::endl;
        }
        exit(EXIT_FAILURE);
    }
    return shader;
}

GLuint makeProgram(const std::vector<GLuint>& shaders) {
    GLuint programHandle = glCreateProgram();
    if(!programHandle) {
        std::cerr << "Unable to create program" << std::endl;
        exit(EXIT_FAILURE);
    }
    // Attach shaders
    for(GLuint shader : shaders) {
        glAttachShader(programHandle, shader);
    }
    // Link to make a program
    glLinkProgram(programHandle);
    // Verify the link
    GLint status;
    glGetProgramiv(programHandle, GL_LINK_STATUS, &status);
    if(status == GL_FALSE) {
        std::cerr << "Failed to link shader program!" << std::endl;
        // Get and print the log info
        GLint logLen;
        glGetProgramiv(programHandle, GL_INFO_LOG_LENGTH, &logLen);
        if (logLen > 0) {
            std::string log(logLen, ' ');
            GLsizei written;
            glGetProgramInfoLog(programHandle, logLen, &written, log.data());
            std::cerr << "Shader log: " << std::endl << log << std::endl;
        }
        exit(EXIT_FAILURE);
    }
    // Load it into pipeline
    glUseProgram(programHandle);
    // Tidy up
    for (GLuint shader : shaders) {
        glDetachShader(programHandle, shader);
        glDeleteShader(shader);
    }

    return programHandle;
}

GLFWwindow* initWindow() {
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

    return window;
}

void render(GLFWwindow* window, RenderCallback callback) {
    // Setup to do the renderings
    glfwSwapInterval(1);

    while (!glfwWindowShouldClose(window))
    {
        float ratio;
        int width, height;

        glfwGetFramebufferSize(window, &width, &height);

        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);

        callback(float(glfwGetTime()));

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Teardown of window
    glfwDestroyWindow(window);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}