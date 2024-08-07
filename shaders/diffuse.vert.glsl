#version 460

layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec3 VertexNormal;

layout (location=0) out vec3 vColor;

uniform vec4 LightPosition;
uniform vec3 Kd;
uniform vec3 Ld;

uniform mat4 ModelViewMatrix;
uniform mat3 NormalMatrix;
uniform mat4 ProjectionMatrix;
uniform mat4 MVP;

void main()
{
  vec3 tnorm = normalize( NormalMatrix * VertexNormal);
  vec4 camCoords = ModelViewMatrix * (vec4(VertexPosition,1.0));
  vec3 s = normalize(vec3(LightPosition - camCoords));
  vColor = Ld * Kd * max( dot( s, tnorm ), 0.0 );
  gl_Position = MVP * vec4(VertexPosition,1.0);
}