#version 330 core

layout(location = 0) out vec4 out_albedo;
layout(location = 1) out vec4 out_material;
layout(location = 2) out vec4 out_normal;
layout(location = 3) out vec4 out_position;

uniform vec4 color;
void main() {
  out_albedo = vec4(color.xyz, 1.);
}
