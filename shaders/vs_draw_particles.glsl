#version 440 core

layout (location = 0) in vec3 v_position;

out float id;
out vec3 pos;

layout(std140, binding=0) uniform camera_matrices {
   mat4 view_matrix;
   mat4 proj_matrix;
};

void main() {
  id = float(gl_VertexID);
  vec3 p =  (view_matrix * vec4(v_position, 1.)).xyz;
  float dist = length(p);
  gl_Position = proj_matrix * vec4(p, 1.);
  //gl_Position = vec4(v_position, 1.);
  pos = v_position;
}
