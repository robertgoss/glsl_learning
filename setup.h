//
// Based on the book. Code to setup and load shader programs
//

#ifndef GLSL_LEARNING_SETUP_H
#define GLSL_LEARNING_SETUP_H

#include <string>
#include <vector>
#include <functional>

#include <glad/glad.h>

struct GLFWwindow;

GLuint loadShader(const std::string& path, uint64_t shaderType);
GLuint makeProgram(const std::vector<GLuint>& shaders);
GLFWwindow* initWindow();

using RenderCallback = const std::function<void(float)>&;
void render(GLFWwindow*, RenderCallback drawing);

#endif //GLSL_LEARNING_SETUP_H
