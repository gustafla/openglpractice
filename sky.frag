#version 100

precision mediump float;

varying vec4 v_pos;

uniform float u_time;
uniform float u_fft_bass;
uniform float u_fft_treble;
uniform vec2 u_sky_sunpos;
uniform vec2 u_resolution;

uniform vec3 u_sky_lcolor;
uniform vec3 u_sky_hcolor;

uniform vec3 u_sky_hccol;
uniform vec3 u_sky_lccol;

uniform sampler2D u_t1;

void main() {
  vec2 pos = vec2(v_pos.x * u_resolution.x/u_resolution.y, v_pos.y);

  vec3 c = mix(u_sky_lcolor, u_sky_hcolor, 0.2 + pos.y*0.3); // Sky grad
  c += pow(max(1.-distance(u_sky_sunpos, pos), 0.), 5.); // Sun
  vec3 t = texture2D(u_t1, gl_FragCoord.xy/u_resolution).rgb; // Sample cloud tex
  float a = t.r;
  t = mix(u_sky_hccol, u_sky_lccol, a);
  c = mix(c, t, max(a-0.28, 0.)); // Mix clouds
  gl_FragColor = vec4(c, 1.);
}
