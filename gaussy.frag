#version 100

precision mediump float;

varying vec4 v_pos;

uniform vec2 u_resolution;
uniform sampler2D u_f1;

#define N 9

void main() {
  float kernel[N];
  kernel[0] = 0.000229;
  kernel[1] = 0.005977;
  kernel[2] = 0.060598;
  kernel[3] = 0.241732;
  kernel[4] = 0.382928;
  kernel[5] = 0.241732;
  kernel[6] = 0.060598;
  kernel[7] = 0.005977;
  kernel[8] = 0.000229;

  float pixel = 6./u_resolution.y;
  vec2 pos = v_pos.xy * 0.5 + 0.5;
  vec3 c = vec3(0.);
  for (int i=-((N-1)/2); i < ((N-1)/2); i++) {
    c += texture2D(u_f1, vec2(pos.x, pos.y + pixel*float(i))).rgb
      * kernel[i+((N-1)/2)];
  }

  gl_FragColor = vec4(c, 1.);
}
