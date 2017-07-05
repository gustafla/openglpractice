#pragma once

#include "window.hxx"
#include <string>

class GlShader {
  public:
    GlShader(GLenum type);
    GlShader(GLenum type, GLsizei count, GLchar const *source[]);
    ~GlShader();
    void setSource(GLsizei count, GLchar const *source[]);
    void compile();

  private:
    GLuint id;
    GLenum type;
};
