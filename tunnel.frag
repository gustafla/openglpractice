#version 100

precision highp float;

varying vec4 v_pos;
uniform float u_tunnel_alpha;

void main() {
  gl_FragColor = vec4(vec3(1.), clamp(2.-v_pos.z/5., 0., 1.)*u_tunnel_alpha);
}
