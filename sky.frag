#version 100

precision highp float;
precision highp int;

varying vec4 v_pos;

uniform float u_time;
uniform float u_fft_bass;
uniform float u_fft_treble;
uniform float u_sunpos_x;
uniform float u_sunpos_y;

void main() {
  float l = v_pos.y;
  l += distance(vec2(u_sunpos_x, u_sunpos_y), v_pos.xy);
  l += u_fft_bass;
  l += u_fft_treble;
  gl_FragColor = vec4(vec3(l), 1.);
}
