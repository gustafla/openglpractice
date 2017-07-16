#include "shaders.hxx"
#include <string>

static const std::string _vs =
"#version 100\n"
"precision highp float;\n"
"attribute vec3 a_pos;\n"
"varying vec4 v_pos;\n"
"void main() {\n"
"  gl_Position = v_pos = vec4(a_pos, 1.0);\n"
"}\n";

Shaders::Shaders():
  vs(GL_VERTEX_SHADER, _vs)
{}
