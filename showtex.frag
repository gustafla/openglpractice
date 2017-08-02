#version 100

precision mediump float;

varying vec4 v_pos;

uniform sampler2D u_t1;
uniform float u_tex_a;

void main() {
  vec4 t = texture2D(u_t1, v_pos.xy*0.5+0.5);
  gl_FragColor = t;//vec4(t.rgb, u_tex_a);
}
