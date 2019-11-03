#version 330 core

layout (location = 0) in vec3 v_position;

uniform mat4 model_matrix;

void main() {
  gl_Position = model_matrix * vec4(v_position, 1.);
}
