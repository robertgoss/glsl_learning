// Basic circle glow drawn with fragment shader

// Chapter 2

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../setup.h"
#include "../vertex_buffer_creator.h"

#include <cstring>

// All based on OpenGL4 Shading Language cookbook, David Wolff.

void fragment_circle_main() {
    GLFWwindow* window = initWindow();

    GLuint vertShader = loadShader("texture.vert.glsl", GL_VERTEX_SHADER);
    GLuint fragShader = loadShader("glow.frag.glsl", GL_FRAGMENT_SHADER);
    GLuint programHandle = makeProgram({vertShader, fragShader});

    // Setup the triangle data
    GLuint count = 0;
    GLuint vaoHandle = VertexBufferCreator::textured_quad(count);

    GLuint blockIndex = glGetUniformBlockIndex(programHandle, "BlobSettings");
    GLint blockSize;
    glGetActiveUniformBlockiv(programHandle, blockIndex, GL_UNIFORM_BLOCK_DATA_SIZE, &blockSize);
    GLubyte* blockBuffer;
    blockBuffer = (GLubyte*) malloc(blockSize);
    // Query for each offset
    const GLchar* names[] = {
            "InnerColor", "OuterColor", "RadiusInner", "RadiusOuter"
    };
    GLuint indices[4];
    glGetUniformIndices(programHandle, 4, names, indices);
    GLint offset[4];
    glGetActiveUniformsiv(programHandle, 4, indices, GL_UNIFORM_OFFSET, offset);
    // Store data in the buffer
    GLfloat outerColor[] = {0.0f, 0.0f, 0.0f, 0.0f};
    GLfloat innerColor[] = {1.0f,1.0f, 0.75f, 1.0f};
    GLfloat innerRadius = 0.25f;
    GLfloat  outerRadius = 0.45f;

    memcpy(blockBuffer + offset[0], innerColor, 4*sizeof(GLfloat));
    memcpy(blockBuffer + offset[1], outerColor, 4*sizeof(GLfloat));
    memcpy(blockBuffer + offset[2], &innerRadius, sizeof(GLfloat));
    memcpy(blockBuffer + offset[3], &outerRadius, sizeof(GLfloat));

    // Copy the buffer over
    GLuint uboHandle;
    glGenBuffers(1, &uboHandle);
    glBindBuffer(GL_UNIFORM_BUFFER, uboHandle);
    glBufferData(GL_UNIFORM_BUFFER, blockSize, blockBuffer, GL_DYNAMIC_DRAW);
    glBindBufferBase(GL_UNIFORM_BUFFER, 0, uboHandle);

    RenderCallback callback = [vaoHandle, count](float _time, const glm::mat4& _) {


        glBindVertexArray(vaoHandle);
        glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, 0);
    };

    render(window, false, callback);
}