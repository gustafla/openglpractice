#version 100

precision highp float;

attribute vec3 a_pos;
varying vec4 v_pos;

uniform mat4 u_projection;
uniform mat4 u_translation;
uniform mat4 u_rotation;
uniform float u_time;
uniform float u_fft_bass;
uniform float u_fft_treble;

uniform float u_df;

void main() {
  v_pos = u_translation * u_rotation * vec4(a_pos*min(-u_df/4., 1.), 1.);
  gl_Position = u_projection * v_pos;
}
