//
// Based on the book. Code to setup and load shader programs
//

#ifndef GLSL_LEARNING_SETUP_H
#define GLSL_LEARNING_SETUP_H

#include <string>
#include <vector>
#include <functional>

#include <glad/glad.h>
#include <glm/glm.hpp>

struct GLFWwindow;

GLuint loadShader(const std::string& path, uint64_t shaderType);
GLuint makeProgram(const std::vector<GLuint>& shaders);
GLuint setUniform(GLuint handle, const std::string&, const glm::vec3& v);
GLuint setUniform(GLuint handle, const std::string&, const glm::vec4& v);
GLuint setUniform(GLuint handle, const std::string&, const glm::mat3& m);
GLuint setUniform(GLuint handle, const std::string&, const glm::mat4& m);
GLFWwindow* initWindow();

using RenderCallback = const std::function<void(float, const glm::mat4&)>&;
void render(GLFWwindow*, bool use_depth, RenderCallback drawing);

#endif //GLSL_LEARNING_SETUP_H
