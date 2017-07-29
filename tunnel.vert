#version 100

precision highp float;

attribute vec3 a_pos;
varying vec4 v_pos;
uniform mat4 u_projection;
uniform float u_time;
uniform float u_fft_treble;
uniform float u_fft_bass;

void main() {
  vec4 p = vec4(a_pos.x*(1.-u_fft_bass*0.02), a_pos.y*(1.-u_fft_treble*0.03), a_pos.z+mod(u_time*3., 1.)-12., 1.);
  gl_Position = v_pos = u_projection * p;
}
