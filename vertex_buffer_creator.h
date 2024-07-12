#ifndef GLSL_LEARNING_VERTEX_BUFFER_CREATOR_H
#define GLSL_LEARNING_VERTEX_BUFFER_CREATOR_H

#include <glad/glad.h>

#include <vector>
#include <string>

class VertexBufferCreator {
public:
    static GLuint single_colourful_triangle(GLuint& count);
    static GLuint textured_quad(GLuint& count);
    static GLuint torus(GLuint& count,  GLuint nsides, GLuint nrings);
    static GLuint cube(GLuint& count, float size);
    static GLuint named(const std::string& name, GLuint& count);

private:
    static GLuint from_buffers(
            const std::vector<GLuint>& elem,
            const std::vector<GLfloat>& pos,
            const std::vector<GLfloat>* normal,
            const std::vector<GLfloat>* colour,
            const std::vector<GLfloat>* uv
            );
};

#endif //GLSL_LEARNING_VERTEX_BUFFER_CREATOR_H
