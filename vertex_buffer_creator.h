#ifndef GLSL_LEARNING_VERTEX_BUFFER_CREATOR_H
#define GLSL_LEARNING_VERTEX_BUFFER_CREATOR_H

#include <glad/glad.h>

#include <vector>

class VertexBufferCreator {
public:
    static GLuint single_colourful_triangle(GLuint& vert_count);
    static GLuint textured_quad(GLuint& vert_count);
    static GLuint torus(GLuint& vert_count);

private:
    static GLuint from_buffers(
            const std::vector<GLuint>& elem,
            const std::vector<GLfloat>& pos,
            const std::vector<GLfloat>* colour,
            const std::vector<GLfloat>* uv
            );
};

#endif //GLSL_LEARNING_VERTEX_BUFFER_CREATOR_H
