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

  //Look up and store all uniforms to a string keyed std::map
  int uniformCount;
  int uniformLength;
  glGetProgramiv(id, GL_ACTIVE_UNIFORMS, &uniformCount);
  glGetProgramiv(id, GL_ACTIVE_UNIFORM_MAX_LENGTH, &uniformLength);
  GLchar* ufmName = new GLchar[uniformLength];
  GLint ufmSize;
  GLenum ufmType;
  for (int i=0; i<uniformCount; i++) {
    glGetActiveUniform(id, i, uniformLength, NULL, &ufmSize, &ufmType, ufmName);
    uniforms[std::string(ufmName)] = glGetUniformLocation(id, ufmName);
  }
  delete[] ufmName;

  return succ;
}

void GlProgram::use() {
  glUseProgram(id);
}

GLuint GlProgram::getId() {
  return id;
}

void GlProgram::setUfm(std::string const &name, float value) {
  glUniform1f(uniforms[name], value);
}

void GlProgram::setUfm(std::string const &name, bool value) {
  glUniform1i(uniforms[name], value);
}

void GlProgram::setUfm(std::string const &name, int value) {
  glUniform1i(uniforms[name], value);
}
