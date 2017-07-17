#include "gl_program.hxx"
#include "debug.hxx"
#include <iostream>

GlProgram GlProgram::loadFromFiles(std::string const &vsName,
    std::string const &fsName) {
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
    msg("Error linking program\n" + std::string(log));
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
    msg("GlProgram has uniform " + std::string(ufmName));
    uniforms[std::string(ufmName)] = glGetUniformLocation(id, ufmName)+1;
  }
  delete[] ufmName;

  //Look up and store all attributes to a string keyed std::map
  int attribCount;
  int attribLength;
  glGetProgramiv(id, GL_ACTIVE_ATTRIBUTES, &attribCount);
  glGetProgramiv(id, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &attribLength);
  GLchar* atrName = new GLchar[attribLength];
  GLint atrSize;
  GLenum atrType;
  for (int i=0; i<attribCount; i++) {
    glGetActiveAttrib(id, i, attribLength, NULL, &atrSize, &atrType,
        atrName);
    attributes[std::string(atrName)] = glGetAttribLocation(id, atrName)+1;
  }
  delete[] atrName;

  return succ;
}

void GlProgram::use() const {
  glUseProgram(id);
}

GLuint GlProgram::getId() {
  return id;
}

GLint GlProgram::getAttribLocation(std::string const &name) const {
  return attributes.at(name)-1;
}

GLint GlProgram::getUniformLocation(std::string const &name) const {
  return uniforms.at(name)-1;
}
