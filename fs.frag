#version 330 core
out vec4 FragColor;

in vec4 o_pos;

uniform float u_time;

void main() {
  FragColor = vec4(o_pos.xyz*mod(u_time, 1.), 1.0);
}
