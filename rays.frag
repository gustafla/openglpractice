#version 100

precision highp float;

varying vec4 v_pos;
uniform vec2 u_resolution;
uniform vec2 u_sunpos;
uniform sampler2D u_f1;

#define ITR 5

vec3 sample(vec2 pos, float m, float s) {
  return clamp(texture2D(u_f1, pos).rgb * m - s, 0., 1.);
}

void main() {
  vec3 co = texture2D(u_f1, v_pos.xy * 0.5 + 0.5).rgb;

  vec3 c = vec3(0.);
  for (int i=0; i<ITR; i++) {
    float z = float(i) * .2;
    c += sample(v_pos.xy / (2. + z) + 0.5, 1.0, 0.0);
  }
  c /= float(ITR);

  gl_FragColor = vec4(co + c, 1.);
}
