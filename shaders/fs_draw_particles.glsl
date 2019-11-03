#version 410 core

out vec4 color;

in float id;
in vec3 pos;

void main() {
  color = vec4(pos.xy,1., 1.);
}
