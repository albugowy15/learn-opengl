#version 330 core
layout(location = 0) in vec3 aPos;

uniform float horizontalOffset;

out vec3 finalPos;

void main() {
  finalPos = vec3(aPos.x + horizontalOffset, aPos.y, aPos.z);
  gl_Position = vec4(finalPos, 1.0);
}
