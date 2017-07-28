#version 100

precision highp float;

varying vec4 v_pos;

uniform float u_time;
uniform float u_fft_bass;
uniform float u_fft_treble;
uniform vec2 u_resolution;

uniform float u_post_whiteout;
uniform float u_post_fft_bass;
uniform float u_post_fft_treble;
uniform float u_post_rbs;

uniform sampler2D u_f1;
uniform sampler2D u_t1;

void main() {
  vec2 p = gl_FragCoord.xy / u_resolution;
  vec3 c = vec3(
      texture2D(u_f1, vec2(p.x-u_post_rbs, p.y)).r,
      texture2D(u_f1, p).g,
      texture2D(u_f1, vec2(p.x+u_post_rbs, p.y)).b);
  c += texture2D(u_t1, p*8.).rgb * 0.2; // Add noise

  c -= length(v_pos.xy)*0.18; // Vignette

  gl_FragColor = vec4(
      c
      +u_post_whiteout
      +u_fft_bass*u_post_fft_bass
      +u_fft_treble*u_post_fft_treble
      , 1.);
}
