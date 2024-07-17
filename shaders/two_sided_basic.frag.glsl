#version 460

layout(location=0) in vec3 FrontColor;
layout(location=1) in vec3 BackColor;
layout (location=0) out vec4 FragColor;

void main() {
    if (gl_FrontFacing) {
        FragColor = vec4(FrontColor, 1.0);
    } else {
        FragColor = vec4(BackColor, 1.0);
    }
}