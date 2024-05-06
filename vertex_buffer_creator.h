#ifndef GLSL_LEARNING_VERTEX_BUFFER_CREATOR_H
#define GLSL_LEARNING_VERTEX_BUFFER_CREATOR_H

#include <glad/glad.h>

class VertexBufferCreator {
public:
    static GLuint single_colourful_triangle();
    static GLuint textured_quad();
};

#endif //GLSL_LEARNING_VERTEX_BUFFER_CREATOR_H
