#pragma once

#include "window.hxx"
#include <string>

class GlShader {
  public:
    GlShader(GLenum type);
    GlShader(GLenum type, GLsizei count, GLchar const *source[]);
    ~GlShader();
    void setSource(GLsizei count, GLchar const *source[]);
    GLint compile();
    GLuint getId();

  private:
    GLuint id;
    GLenum type;
};
