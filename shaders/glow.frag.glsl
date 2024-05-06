#version 460

layout(location=0) in vec2 vUV;
layout (location=0) out vec4 FragColor;

layout (binding=0) uniform BlobSettings {
    vec4 InnerColor;
    vec4 OuterColor;
    float RadiusInner;
    float RadiusOuter;
};

void main() {
    float dx = vUV.x - 0.5;
    float dy = vUV.y - 0.5;
    float dist = sqrt(dx*dx + dy*dy);
    FragColor = mix( InnerColor, OuterColor,
      smoothstep( RadiusInner, RadiusOuter, dist ));
}