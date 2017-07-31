#version 100

precision highp float;

attribute vec3 a_pos;
varying vec4 v_pos;

uniform mat4 u_projection;
uniform float u_time;
uniform float u_fft_bass;
uniform float u_fft_treble;

#define PI 3.14159265

void main() {
  float a = atan(a_pos.y, a_pos.x);
  float v =
    sin(a_pos.z*10.+u_time*3.)*0.3*u_fft_treble
    + /*(*/sin(a*3.+u_time)*0.06*u_fft_bass
    //+ sin(a*5.+u_time*0.9)*0.07*u_fft_bass)
    * max(sin(a_pos.z*3.+u_time*6.), 0.)
    + sin(a_pos.z*2.-u_time*4.*PI)*0.5
    + 1.5;
  vec4 p = v_pos = vec4(a_pos.x*v, a_pos.y*v, a_pos.z - 20., 1.);
  gl_Position = u_projection * p;
}
