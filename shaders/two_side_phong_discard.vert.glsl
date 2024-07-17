#version 460

layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec3 VertexNormal;
layout (location = 3) in vec2 VertexTexCoord;

layout (location=0) out vec3 FrontColor;
layout (location=1) out vec3 BackColor;
layout (location=2) out vec2 TexCoord;

uniform struct LightInfo {
  vec4 Position;
  vec3 La;
  vec3 Ld;
  vec3 Ls;
} Light;

uniform struct MaterialInfo {
  vec3 Ka;
  vec3 Kd;
  vec3 Ks;
  float Shininess;
} Material;

uniform mat4 ModelViewMatrix;
uniform mat3 NormalMatrix;
uniform mat4 ProjectionMatrix;
uniform mat4 MVP;

void getCamSpace( out vec3 norm, out vec3 position ) {
  norm = normalize( NormalMatrix * VertexNormal);
  position = (ModelViewMatrix * vec4(VertexPosition, 1.0)).xyz;
}

vec3 phongModel( vec3 position, vec3 n) {
  vec3 ambient = Light.La * Material.Ka;
  vec3 s = normalize(Light.Position.xyz - position);
  float sDotN = max(dot(s,n), 0.0);
  vec3 diffuse = Light.Ld * Material.Kd * sDotN;
  vec3 spec = vec3(0.0);
  if (sDotN > 0.0) {
    vec3 v = normalize(-position);
    vec3 r = reflect(-s, n);
    spec = Light.Ls * Material.Ks * pow(max(dot(r,v), 0.0), Material.Shininess);
  }
  return ambient + diffuse + spec;
}

void main()
{
  vec3 camNorm, camPosition;
  getCamSpace(camNorm, camPosition);
  FrontColor = phongModel( camPosition, camNorm );
  BackColor = phongModel( camPosition, -camNorm );
  gl_Position = MVP * vec4(VertexPosition,1.0);
  TexCoord = VertexTexCoord;
}