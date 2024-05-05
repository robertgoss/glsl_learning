#include <iostream>
#include <fstream>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "setup.h"
#include "vertex_buffer_creator.h"

// All based on OpenGL4 Shading Language cookbook, David Wolff.

int main() {
    GLFWwindow* window = initWindow();

    GLuint vertShader = loadShader("basic.vert.glsl", GL_VERTEX_SHADER);
    GLuint fragShader = loadShader("basic.frag.glsl", GL_FRAGMENT_SHADER);
    GLuint programHandle = makeProgram({vertShader, fragShader});

    // Setup the triangle data
    GLuint vaoHandle = VertexBufferCreator::single_colourful_triangle();

    float angle = 0.0f;
    GLint location = glGetUniformLocation(programHandle, "RotationMatrix");

    RenderCallback callback = [&angle, vaoHandle, location](float _time) {
        angle += 0.01;
        if (angle > 360) {
            angle -= 360;
        }

        glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f,0.0f,1.0f));

        glUniformMatrix4fv(location, 1, GL_FALSE, &rotationMatrix[0][0]);

        glBindVertexArray(vaoHandle);
        glDrawArrays(GL_TRIANGLES, 0, 3 );
    };

    render(window, callback);
}
