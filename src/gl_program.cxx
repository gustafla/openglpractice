#include "gl_program.hxx"
#include <iostream>

GlProgram GlProgram::loadFromFiles(std::string const &vsName, std::string const &fsName) {
  GlShader vs = GlShader::loadFromFile(vsName, GL_VERTEX_SHADER);
  GlShader fs = GlShader::loadFromFile(fsName, GL_FRAGMENT_SHADER);
  return GlProgram(vs, fs);
}

GlProgram::GlProgram() {
  id = glCreateProgram();
}

GlProgram::GlProgram(GlShader const &vs, GlShader const &fs):
  GlProgram()
{
  use();
  attachShader(vs);
  attachShader(fs);
  link();
}

GlProgram::~GlProgram() {
  glDeleteProgram(id);
}

void GlProgram::attachShader(GlShader const &s) {
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

void setUfm(std::string const &name, float value) {

}

void setUfm(std::string const &name, bool value) {

}

void setUfm(std::string const &name, int value) {

}
