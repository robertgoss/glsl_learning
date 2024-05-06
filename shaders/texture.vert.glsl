#version 460
layout (location=0) in vec3 VertexPosition;
layout (location=1) in vec2 VertexUV;

layout (location=0) out vec2 vUV;

void main()
{
    vUV = VertexUV;

    gl_Position = vec4(VertexPosition,1.0);
}