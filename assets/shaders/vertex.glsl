#version 330 core

out vec3 fragmentColor;
out vec3 fragmentNormal;
out float lightDistance;
out vec2 UV;

layout(location = 0) in vec3 G_Position;
layout(location = 1) in vec3 G_Color;
layout(location = 2) in vec3 G_Normal;
layout(location = 3) in vec2 G_UV;

uniform mat4 G_Mvp;
uniform vec3 G_LightPosition;

void main(){
  lightDistance = length(G_LightPosition - G_Position);
  gl_Position = G_Mvp * vec4(G_Position, 1);
  fragmentColor = G_Color;
  fragmentNormal = G_Normal;
  UV = G_UV;
}
