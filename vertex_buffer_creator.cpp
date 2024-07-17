#include "vertex_buffer_creator.h"

#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

GLuint VertexBufferCreator::cube(GLuint& count, float size) {
    GLfloat side2 = size / 2.0f;

    std::vector<GLfloat> p = {
            // Front
            -side2, -side2, side2, side2, -side2, side2, side2,  side2, side2,  -side2,  side2, side2,
            // Right
            side2, -side2, side2, side2, -side2, -side2, side2,  side2, -side2, side2,  side2, side2,
            // Back
            -side2, -side2, -side2, -side2,  side2, -side2, side2,  side2, -side2, side2, -side2, -side2,
            // Left
            -side2, -side2, side2, -side2,  side2, side2, -side2,  side2, -side2, -side2, -side2, -side2,
            // Bottom
            -side2, -side2, side2, -side2, -side2, -side2, side2, -side2, -side2, side2, -side2, side2,
            // Top
            -side2,  side2, side2, side2,  side2, side2, side2,  side2, -side2, -side2,  side2, -side2
    };

    std::vector<GLfloat> n = {
            // Front
            0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
            // Right
            1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
            // Back
            0.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f,
            // Left
            -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
            // Bottom
            0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f,
            // Top
            0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f
    };

    // Colours
    std::vector<GLfloat> c;
    for (auto f : n) {
        c.push_back(fabs(f));
    }

    std::vector<GLfloat> tex = {
            // Front
            0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
            // Right
            0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
            // Back
            0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
            // Left
            0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
            // Bottom
            0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
            // Top
            0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f
    };

    std::vector<GLuint> el = {
            0,1,2,0,2,3,
            4,5,6,4,6,7,
            8,9,10,8,10,11,
            12,13,14,12,14,15,
            16,17,18,16,18,19,
            20,21,22,20,22,23
    };

    count = el.size();
    return from_buffers(el, p, &n, &c, &tex);
}

GLuint VertexBufferCreator::open_cylinder(GLuint &count, GLuint nsides) {
    float radius = 0.5;
    float height = 1.0;
    int nVerts  = nsides * 2;
    // Points
    std::vector<GLfloat> p(3 * nVerts);
    // Colours
    std::vector<GLfloat> c(3 * nVerts);
    // Normals
    std::vector<GLfloat> n(3 * nVerts);
    // Tex coords
    std::vector<GLfloat> tex(2 * nVerts);
    // Elements
    std::vector<GLuint> el(6 * nsides);

    float sideFactor = glm::two_pi<float>() / nsides;
    int idx = 0, tidx = 0;
    for( GLuint side = 0; side < nsides; side++ ) {
        float v = side * sideFactor;
        float cv = cos(v);
        float sv = sin(v);
        for(int i = 0; i < 2; ++i) {
            p[idx] = radius * cv;
            p[idx + 1] = radius * sv;
            if (i == 0) {
                p[idx + 2] = height / 2;
            } else {
                p[idx + 2] = -height / 2;
            }
            n[idx] = cv;
            n[idx + 1] = sv;
            n[idx + 2] = 0;
            c[idx] = fabs(n[idx]);
            c[idx + 1] = fabs(n[idx + 1]);
            c[idx + 2] = fabs(n[idx + 2]);
            tex[tidx] = v / glm::two_pi<float>();
            if (i == 0) {
                tex[tidx + 1] = 0.0;
            } else {
                tex[tidx + 1] = 1.0;
            }
            tidx += 2;
            idx += 3;
        }
    }

    idx = 0;
    for( GLuint side = 0; side < nsides; side++ ) {
        int sideBase = side * 2;
        int nextSideBase = ((side+1) % nsides) * 2;
        // The quad
        el[idx] = sideBase;
        el[idx+1] = sideBase + 1;
        el[idx+2] = nextSideBase;
        el[idx+4] = sideBase + 1;;
        el[idx+3] = nextSideBase;
        el[idx+5] = nextSideBase + 1;
        idx += 6;
    }
    count = el.size();
    return from_buffers(el, p, &n, &c, &tex);
}

GLuint VertexBufferCreator::torus(GLuint& count, GLuint nsides, GLuint nrings) {
    float outerRadius = 0.5;
    float innerRadius = 0.2;
    GLuint faces = nsides * nrings;
    int nVerts  = nsides * (nrings+1);   // One extra ring to duplicate first ring

    // Points
    std::vector<GLfloat> p(3 * nVerts);
    // Colours
    std::vector<GLfloat> c(3 * nVerts);
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
            c[idx] = fabs(n[idx]);
            c[idx+1] = fabs(n[idx+1]);
            c[idx+2] = fabs(n[idx+2]);
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
            el[idx+3] = ringStart + side;
            el[idx+4] = nextRingStart + nextSide;
            el[idx+5] = (ringStart + nextSide);
            idx += 6;
        }
    }
    count = el.size();
    return from_buffers(el, p, &n, &c, &tex);
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
    return from_buffers(elems, positionData, 0, &colorData, 0);
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
    return from_buffers(elems, positionData, 0, 0, &uvData);
}

GLuint VertexBufferCreator::from_buffers(
        const std::vector<GLuint>& elem,
        const std::vector<GLfloat>& pos,
        const std::vector<GLfloat>* norm,
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

    // Setup norm buffer (if exists)
    GLuint normHandle=0;
    if (norm) {
        glGenBuffers(1, &normHandle);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, normHandle);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, norm->size() * sizeof(GLfloat)*3, norm->data(), GL_STATIC_DRAW);
    }

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

    if (norm) {
        glBindBuffer(GL_ARRAY_BUFFER, normHandle);
        glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 0, 0 );
        glEnableVertexAttribArray(1);  // Vertex position
    }

    if (colour) {
        glBindBuffer(GL_ARRAY_BUFFER, colourHandle);
        glVertexAttribPointer( 2, 3, GL_FLOAT, GL_FALSE, 0, 0 );
        glEnableVertexAttribArray(2);  // Vertex position
    }

    if (uv) {
        glBindBuffer(GL_ARRAY_BUFFER, uvHandle);
        glVertexAttribPointer( 3, 2, GL_FLOAT, GL_FALSE, 0, 0 );
        glEnableVertexAttribArray(3);  // Vertex position
    }

    return vaoHandle;
}

GLuint VertexBufferCreator::named(const std::string& name, GLuint& count) {
    if (name == "cube") {
        return cube(count, 1.0);
    } else if (name == "torus") {
        return torus(count, 16,32);
    } else if (name == "torus-basic") {
        return torus(count, 8,12);
    } else if (name == "open-cylinder") {
        return open_cylinder(count, 20);
    }
    return 0;
}