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

    GLuint vertShader = loadShader("diffuse.vert.glsl", GL_VERTEX_SHADER);
    GLuint fragShader = loadShader("basic.frag.glsl", GL_FRAGMENT_SHADER);
    GLuint programHandle = makeProgram({vertShader, fragShader});

    // Query for each offset
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(-35.0f), glm::vec3(1.0f,0.0f,0.0f));
    model = glm::rotate(model, glm::radians(35.0f), glm::vec3(0.0f,1.0f,0.0f));
    glm::mat4 view = glm::lookAt(glm::vec3(0.0f,0.0f,2.0f), glm::vec3(0.0f,0.0f,0.0f), glm::vec3(0.0f,1.0f,0.0f));


    setUniform(programHandle, "Kd", glm::vec3(0.9f, 0.5f, 0.3f));
    setUniform(programHandle, "Ld", glm::vec3(1.0f, 1.0f, 1.0f));
    setUniform(programHandle, "LightPosition", view * glm::vec4(5.0f,5.0f,2.0f,1.0f) );

    // Setup the triangle data
    GLuint count = 0;
    GLuint vaoHandle = VertexBufferCreator::torus(count);

    float angle = 0.0f;
    GLint location = glGetUniformLocation(programHandle, "RotationMatrix");

    RenderCallback callback = [&](float _time, const glm::mat4 proj) {
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

        glm::mat4 mv = view * model;
        setUniform(programHandle, "ModelViewMatrix", mv);
        setUniform(programHandle, "NormalMatrix",
                   glm::mat3( glm::vec3(mv[0]), glm::vec3(mv[1]), glm::vec3(mv[2]) ));
        setUniform(programHandle, "MVP", proj * mv);

        glBindVertexArray(vaoHandle);
        glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, 0);
    };

    render(window, true,callback);
}