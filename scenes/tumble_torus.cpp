// Basic torus model rendering to test lighting shaders

// Chapter 3

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../setup.h"
#include "../vertex_buffer_creator.h"

#include <cstring>

// All based on OpenGL4 Shading Language cookbook, David Wolff.

void tumble_torus_main() {
    GLFWwindow* window = initWindow();

    GLuint vertShader = loadShader("rotate.vert.glsl", GL_VERTEX_SHADER);
    GLuint fragShader = loadShader("basic.frag.glsl", GL_FRAGMENT_SHADER);
    GLuint programHandle = makeProgram({vertShader, fragShader});

    // Setup the triangle data
    GLuint count = 0;
    GLuint vaoHandle = VertexBufferCreator::torus(count);

    float angle = 0.0f;
    GLint location = glGetUniformLocation(programHandle, "RotationMatrix");

    RenderCallback callback = [&angle, vaoHandle, location, count](float _time) {
        angle += 0.01;
        if (angle > 360) {
            angle -= 360;
        }
        double angle2 = angle * 1.45;
        if (angle2 > 360) {
            angle2 -= 360;
        }

        glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f,cos(angle2),sin(angle2)));

        glUniformMatrix4fv(location, 1, GL_FALSE, &rotationMatrix[0][0]);

        glBindVertexArray(vaoHandle);
        glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, 0);
    };

    render(window, callback);
}