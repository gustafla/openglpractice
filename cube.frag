#version 100

precision mediump float;

varying vec4 v_pos;

uniform float u_time;
uniform float u_fft_bass;
uniform float u_fft_treble;

uniform float u_df;

void main() {
  float c = abs(-u_df/3.);
  gl_FragColor = vec4(vec3(c+0.3, c*c+0.2, c*c*c+0.2), /**/1.);
}
