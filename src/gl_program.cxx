#include "gl_program.hxx"
#include <iostream>

GlProgram::GlProgram() {
  id = glCreateProgram();
}

GlProgram::GlProgram(GlShader &vs, GlShader &fs):
  GlProgram() {
  use();
  attachShader(vs);
  attachShader(fs);
  link();
}

GlProgram::~GlProgram() {
  glDeleteProgram(id);
}

void GlProgram::attachShader(GlShader &s) {
  glAttachShader(id, s.getId());
}

GLint GlProgram::link() {
  glLinkProgram(id);

  GLint succ;
  GLchar log[512];
  glGetProgramiv(id, GL_LINK_STATUS, &succ);
  if (!succ) {
    glGetProgramInfoLog(id, 512, NULL, log);
    std::cout << "Error linking program\n" << log << std::endl;
  }
  return succ;
}

void GlProgram::use() {
  glUseProgram(id);
}

GLuint GlProgram::getId() {
  return id;
}
