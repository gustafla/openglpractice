#version 100

precision highp float;

attribute vec3 a_pos;

varying vec4 v_pos;

void main() {
  gl_Position = v_pos = vec4(a_pos, 1.0);
}
