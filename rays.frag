#version 100

precision highp float;

varying vec4 v_pos;
uniform vec2 u_resolution;

uniform sampler2D u_f1;

void main() {
  gl_FragColor = texture2D(u_f1, gl_FragCoord.xy/u_resolution);
}
