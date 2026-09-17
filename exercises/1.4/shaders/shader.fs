#version 330 core
in vec3 finalPos;
out vec4 fragment_color;

void main() {
  fragment_color = vec4(finalPos, 1.0);
}
