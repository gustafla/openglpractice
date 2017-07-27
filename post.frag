#version 100

precision highp float;

varying vec4 v_pos;

uniform float u_time;
uniform float u_fft_bass;
uniform vec2 u_resolution;

uniform sampler2D u_f1;
uniform sampler2D u_t1;

void main() {
  vec2 p = gl_FragCoord.xy / u_resolution;
  float b = 0.006;
  vec3 c = vec3(
      texture2D(u_f1, vec2(p.x-b, p.y)).r,
      texture2D(u_f1, p).g,
      texture2D(u_f1, vec2(p.x+b, p.y)).b);
  c += texture2D(u_t1, p).rgb * 0.2; // Add noise

  c -= length(v_pos.xy)*0.18; // Vignette
  
  gl_FragColor = vec4(c, 1.);
}
