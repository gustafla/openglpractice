#version 100

precision highp float;

varying vec4 v_pos;

uniform float u_time;
uniform float u_fft_bass;
uniform float u_fft_treble;

void main() {
  gl_FragColor = vec4(vec3(1./max(length(v_pos.xy)*10.-10., 1.0)), 1.);
}
