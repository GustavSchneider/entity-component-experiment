#version 410 core

layout (location = 0) in vec3 v_position;
out vec3 out_values;

uniform vec2 cursor_pos;
uniform float time;

float rand(vec2 p) {
  p += float(gl_VertexID) + time;
  return fract(sin(dot(vec2(12.153252, 68.9459324),p)) * 10224.214124);  
}

float noise( vec2 p ) { 
  vec2 i = floor( p );
  vec2 f = fract( p );	
  vec2 u = f*f*(3.0-2.0*f);
  return -1.0+2.0*mix(mix( rand( i + vec2(0.0,0.0) ), 
                           rand( i + vec2(1.0,0.0) ), u.x),
                      mix( rand( i + vec2(0.0,1.0) ), 
                           rand( i + vec2(1.0,1.0) ), u.x), u.y);
}

float fbm(vec2 v) {
    v*=5;
    float sum = 0.;
    for (int i = 0; i < 6; i++) {
        float e = pow(2., float(i));
        sum += noise(v * vec2(e)) / e;
    }
    return sum;
}

void main() {
  vec2 e = vec2(0.001, 0.0);
  vec2 p = v_position.xy;
  vec2 grad = vec2(fbm(p + e.xy) - fbm(p - e.xy),
                   fbm(p + e.yx) - fbm(p - e.yx)) / e.x;
  //float s = rand(vec2(float(gl_VertexID) + time)) * 0.00001;
  //p += s * grad;
  ///out_values = vec3(p, v_position.z);
  vec3 d_pos = vec3(cursor_pos,0.) - v_position;
  float dist = length(d_pos);
  dist = dist * dist;
  vec3 pos = v_position + vec3(grad.y, - grad.x, 0.) * 0.001;
  pos += 0.1 * d_pos / dist;
  pos = max(pos, vec3(-1));
  pos = min(pos, vec3(1));
  pos.z +=  0.1 * rand(vec2(gl_VertexID));
  out_values = pos;
}
