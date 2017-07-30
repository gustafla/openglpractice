#version 100

precision highp float;

varying vec4 v_pos;

uniform vec2 u_resolution;
uniform sampler2D u_f1;

void main() {
  float kernel[3];
  kernel[0] = 0.38774;
  kernel[1] = 0.24477;
  kernel[2] = 0.06136;

  float pixel = 1./u_resolution.x;
  vec2 pos = v_pos.xy * 0.5 + 0.5;
  vec3 c = vec3(0.);
  for (int i=-2; i < 2; i++) {
    c += texture2D(u_f1, vec2(pos.x + pixel*float(i), pos.y)).rgb
      * kernel[abs(i)];
  }

  gl_FragColor = vec4(c, 1.);
}
