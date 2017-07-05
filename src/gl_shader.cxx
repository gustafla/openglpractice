#include "gl_shader.hxx"
#include <iostream>

GlShader::GlShader(GLenum type):
  type(type) {
  id = glCreateShader(type);
}

GlShader::GlShader(GLenum type, GLsizei count, GLchar const *source[]):
  GlShader(type) {
  setSource(count, source);
  compile();
}

GlShader::~GlShader() {
  glDeleteShader(id);
}

void GlShader::setSource(GLsizei count, GLchar const *source[]) {
  glShaderSource(id, count, source, NULL);
}

void GlShader::compile() {
  glCompileShader(id); 
  GLint err;
  GLchar log[512];
  glGetShaderiv(id, GL_COMPILE_STATUS, &err);
  if (!err) {
    glGetShaderInfoLog(id, 512, NULL, log);
    std::cout << "Error compiling shader\n" << log << std::endl;
  }
}
