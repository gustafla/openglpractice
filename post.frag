#version 100

precision mediump float;

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
      texture2D(u_f1, vec2(p.x-u_post_rbs*0.1, p.y)).r,
      texture2D(u_f1, p).g,
      texture2D(u_f1, vec2(p.x+u_post_rbs*0.1, p.y)).b);
  c += texture2D(u_t1, p*6.).rgb * 0.13; // Add noise

  c -= length(v_pos.xy)*0.18; // Vignette

  gl_FragColor = vec4(
      c
      +u_post_whiteout
      +u_fft_bass*u_post_fft_bass
      +u_fft_treble*u_post_fft_treble
      , 1.);
}
