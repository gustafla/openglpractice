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
  gl_FragColor = vec4(vec3(v_pos.y), 1.);
}
