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

    static GlShader loadFromFile(std::string filename, GLenum type=-1);

  private:
    GLuint id;
    GLenum type;
};
