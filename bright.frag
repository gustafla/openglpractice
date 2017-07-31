#version 100

precision highp float;

varying vec4 v_pos;

uniform sampler2D u_f1;

void main() {
  vec3 c = texture2D(u_f1, v_pos.xy*0.5+0.5).rgb;
  float b = max(c.r, max(c.g, c.b));
  if (b<0.8) {
    discard;
  }
  //gl_FragColor = vec4(clamp((b - 0.8)*10000., 0., 1.) * c, 1.0);
  gl_FragColor = vec4(c, 1.0);
}
