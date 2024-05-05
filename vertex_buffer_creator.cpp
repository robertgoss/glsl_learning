#include "vertex_buffer_creator.h"

GLuint VertexBufferCreator::single_colourful_triangle() {
    GLuint vaoHandle;
    float positionData[] = {
            -0.8f, -0.8f, 0.0f,
            0.8f, -0.8f, 0.0f,
            0.0f, 0.8f, 0.0f };
    float colorData[] = {
            1.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 1.0f };
    // Create and populate the buffer objects
    GLuint vboHandle[2];
    glGenBuffers(2, vboHandle);
    GLuint positionBufferHandle = vboHandle[0];
    GLuint colorBufferHandle = vboHandle[1];
    // Populate the position and colour buffers
    glBindBuffer(GL_ARRAY_BUFFER, positionBufferHandle);
    glBufferData(GL_ARRAY_BUFFER, 9*sizeof(float),
                 positionData, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, colorBufferHandle);
    glBufferData(GL_ARRAY_BUFFER, 9*sizeof(float),
                 colorData, GL_STATIC_DRAW);
    // Setup the vertex array object
    glGenVertexArrays(1, &vaoHandle);
    glBindVertexArray(vaoHandle);
    // Enable the vertex attribute arrays
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    // Map the indices to the buffers
    glBindVertexBuffer(0, positionBufferHandle, 0, sizeof(GLfloat)*3);
    glBindVertexBuffer(1, colorBufferHandle, 0, sizeof(GLfloat)*3);
    glVertexAttribFormat(0, 3, GL_FLOAT, GL_FALSE, 0);
    glVertexAttribBinding(0, 0);
    glVertexAttribFormat(1, 3, GL_FLOAT, GL_FALSE, 0);
    glVertexAttribBinding(1, 1);
    // Return handle
    return vaoHandle;
}