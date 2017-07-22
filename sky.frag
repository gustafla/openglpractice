#version 100

precision highp float;
precision highp int;

varying vec4 v_pos;

uniform float u_time;
uniform float u_fft_bass;
uniform float u_fft_treble;
uniform float u_sunpos_x;
uniform float u_sunpos_y;
uniform vec2 u_resolution;

void main() {
  vec2 pos = vec2(v_pos.x * u_resolution.x/u_resolution.y, v_pos.y);
  float l = pow(1.-distance(vec2(u_sunpos_x, u_sunpos_y), pos), 3.);
  gl_FragColor = vec4(vec3(l), 1.);
}
