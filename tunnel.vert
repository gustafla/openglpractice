#version 100

precision highp float;

attribute vec3 a_pos;
varying vec4 v_pos;
uniform mat4 u_projection;
uniform float u_time;
uniform float u_fft_treble;
uniform float u_fft_bass;

float rand(vec2 co){
  return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

void main() {
  vec4 p = vec4(
      a_pos.x*(1.-u_fft_bass*0.02+rand(a_pos.xz+u_time*0.1)*0.14),
      a_pos.y*(1.-u_fft_treble*0.03+rand(a_pos.zy+u_time*0.1)*0.14),
      a_pos.z+mod(u_time*5., 1.)-12.,
      1.);
  gl_Position = v_pos = u_projection * p;
}
