#version 100

precision highp float;

varying vec4 v_pos;
uniform float u_tunnel_alpha;

void main() {
  /*if (mod(gl_FragCoord.y, 2.) > 0.5 || mod(gl_FragCoord.x, 2.) > 0.5) {
    discard;
  }*/
  gl_FragColor = vec4(vec3(1.), clamp((18.+v_pos.z)/10., 0., 1.)*u_tunnel_alpha
      * mod(gl_FragCoord.x/2., 2.) * mod(gl_FragCoord.y/2., 2.));
}
