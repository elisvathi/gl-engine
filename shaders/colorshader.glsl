#version 330 core
out vec3 color;
in vec3 fragmentColor;
in vec2 UV;
uniform sampler2D G_Texture;

void main() {
  color = fragmentColor;
}
