#include "vertex_buffer_creator.h"

#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

GLuint VertexBufferCreator::torus(GLuint& count) {
    GLuint nsides = 8;
    GLuint nrings = 12;
    float outerRadius = 0.5;
    float innerRadius = 0.2;
    GLuint faces = nsides * nrings;
    int nVerts  = nsides * (nrings+1);   // One extra ring to duplicate first ring

    // Points
    std::vector<GLfloat> p(3 * nVerts);
    // Normals
    std::vector<GLfloat> n(3 * nVerts);
    // Tex coords
    std::vector<GLfloat> tex(2 * nVerts);
    // Elements
    std::vector<GLuint> el(6 * faces);

    // Generate the vertex data
    float ringFactor = glm::two_pi<float>() / nrings;
    float sideFactor = glm::two_pi<float>() / nsides;
    int idx = 0, tidx = 0;
    for( GLuint ring = 0; ring <= nrings; ring++ ) {
        float u = ring * ringFactor;
        float cu = cos(u);
        float su = sin(u);
        for( GLuint side = 0; side < nsides; side++ ) {
            float v = side * sideFactor;
            float cv = cos(v);
            float sv = sin(v);
            float r = (outerRadius + innerRadius * cv);
            p[idx] = r * cu;
            p[idx + 1] = r * su;
            p[idx + 2] = innerRadius * sv;
            n[idx] = cv * cu * r;
            n[idx + 1] = cv * su * r;
            n[idx + 2] = sv * r;
            tex[tidx] = u / glm::two_pi<float>();
            tex[tidx + 1] = v / glm::two_pi<float>();
            tidx += 2;
            // Normalize
            float len = sqrt( n[idx] * n[idx] +
                              n[idx+1] * n[idx+1] +
                              n[idx+2] * n[idx+2] );
            n[idx] /= len;
            n[idx+1] /= len;
            n[idx+2] /= len;
            idx += 3;
        }
    }

    idx = 0;
    for( GLuint ring = 0; ring < nrings; ring++ ) {
        GLuint ringStart = ring * nsides;
        GLuint nextRingStart = (ring + 1) * nsides;
        for( GLuint side = 0; side < nsides; side++ ) {
            int nextSide = (side+1) % nsides;
            // The quad
            el[idx] = (ringStart + side);
            el[idx+1] = (nextRingStart + side);
            el[idx+2] = (nextRingStart + nextSide);
            //el[idx+4] = ringStart + side;
            //el[idx+3] = nextRingStart + nextSide;
            //el[idx+5] = (ringStart + nextSide);
            idx += 6;
        }
    }
    count = el.size();
    return from_buffers(el, p, &n, &tex);
}

GLuint VertexBufferCreator::single_colourful_triangle(GLuint& count) {
    std::vector<GLuint> elems = {
            1,0,2
    };
    count = elems.size();
    std::vector<GLfloat> positionData = {
            -0.8f, -0.8f, 0.0f,
            0.8f, -0.8f, 0.0f,
            0.0f, 0.8f, 0.0f };
    std::vector<GLfloat> colorData = {
            1.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 1.0f };
    return from_buffers(elems, positionData, &colorData, 0);
}

GLuint VertexBufferCreator::textured_quad(GLuint& count){
    GLuint vaoHandle;
    std::vector<GLuint> elems = {
            1,0,2,
            1,2,3
    };
    count = elems.size();
    std::vector<GLfloat> positionData = {
            -1.0f, -1.0f, 0.0f,
            1.0f, -1.0f, 0.0f,
            -1.0f, 1.0f, 0.0f,
            1.0f, 1.0f, 0.0f};
    std::vector<GLfloat> uvData = {
            0.0f, 0.0f,
            1.0f, 0.0f,
            0.0f, 1.0f,
            1.0f, 1.0f};
    // Create and populate the buffer objects
    return from_buffers(elems, positionData, 0, &uvData);
}

GLuint VertexBufferCreator::from_buffers(
        const std::vector<GLuint>& elem,
        const std::vector<GLfloat>& pos,
        const std::vector<GLfloat>* colour,
        const std::vector<GLfloat>* uv)
{
    // Setup elem buffer
    GLuint elemHandle;
    glGenBuffers(1, &elemHandle);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elemHandle);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, elem.size() * sizeof(GLuint), elem.data(), GL_STATIC_DRAW);

    // Setup position buffer
    GLuint positionHandle;
    glGenBuffers(1, &positionHandle);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, positionHandle);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, pos.size() * sizeof(GLfloat)*3, pos.data(), GL_STATIC_DRAW);

    // Setup colour buffer (if exists)
    GLuint colourHandle=0;
    if (colour) {
        glGenBuffers(1, &colourHandle);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, colourHandle);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, colour->size() * sizeof(GLfloat)*3, colour->data(), GL_STATIC_DRAW);
    }

    // Setup uv buffer (if exists)
    GLuint uvHandle = 0;
    if (uv) {
        glGenBuffers(1, &uvHandle);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, uvHandle);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, uv->size() * sizeof(GLfloat)*2, uv->data(), GL_STATIC_DRAW);
    }

    // Setup the vertex array object
    GLuint vaoHandle;
    glGenVertexArrays(1, &vaoHandle);
    glBindVertexArray(vaoHandle);
    // Do the bindings
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elemHandle);

    // Position
    glBindBuffer(GL_ARRAY_BUFFER, positionHandle);
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, 0 );
    glEnableVertexAttribArray(0);  // Vertex position

    if (colour) {
        glBindBuffer(GL_ARRAY_BUFFER, colourHandle);
        glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 0, 0 );
        glEnableVertexAttribArray(1);  // Vertex position
    }

    if (uv) {
        glBindBuffer(GL_ARRAY_BUFFER, uvHandle);
        glVertexAttribPointer( 2, 2, GL_FLOAT, GL_FALSE, 0, 0 );
        glEnableVertexAttribArray(2);  // Vertex position
    }

    return vaoHandle;
}