#version 100

precision highp float;

varying vec4 v_pos;

uniform float u_time;
uniform float u_fft_bass;
uniform float u_fft_treble;

void main() {
  vec2 p = vec2(sin(u_time), cos(u_time));
  gl_FragColor = vec4(v_pos.x, sin(u_time), 1.0, 1.0);
  if (distance(v_pos.xy, p) < 0.02) {
    gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
  }
  if (length(v_pos.xy+vec2(-0.5, 0.0)) < 0.3) {
    gl_FragColor = vec4(vec3(u_fft_bass), 1.0);
  }
  if (length(v_pos.xy+vec2(0.5, 0.0)) < 0.3) {
    gl_FragColor = vec4(vec3(u_fft_treble), 1.0);
  }
}
