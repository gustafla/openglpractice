#version 100

precision highp float;
precision highp int;

varying vec4 v_pos;

uniform float u_time;
uniform float u_fft_bass;
uniform float u_fft_treble;
uniform float u_sky_sunpos_x;
uniform float u_sky_sunpos_y;
uniform vec2 u_resolution;

uniform sampler2D u_t1;

void main() {
  vec2 pos = vec2(v_pos.x * u_resolution.x/u_resolution.y, v_pos.y);
  float l = 0.2 + pos.y*0.3;
  l += pow(max(1.-distance(vec2(u_sky_sunpos_x, u_sky_sunpos_y), pos), 0.), 5.);
  vec4 t = texture2D(u_t1, pos);
  l = mix(l, t.r, t.a);
  gl_FragColor = vec4(vec3(l), 1.);
}
