#version 330 core
layout (location=0) in vec3 a_pos;
layout (location=1) in vec3 a_color;

out vec3 o_color;
out vec4 o_pos;

uniform float u_h_offset;

void main() {
  gl_Position = o_pos = vec4(a_pos.x+u_h_offset, -a_pos.y, a_pos.z, 1.0);
  o_color = a_color;
}
