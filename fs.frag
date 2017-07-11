#version 330 core
out vec4 FragColor;
uniform float u_time;
void main() {
  FragColor = vec4(mod(u_time, 1.0), 0.2, 1.0, 1.0);
}
