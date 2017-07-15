#pragma once

#include "window.hxx"
#include <string>

class GlShader {
  public:
    GlShader(GLenum const type);
    GlShader(GLenum const type, GLsizei const count, GLchar const *source[]);
    GlShader(GLenum const type, std::string const &source);
    ~GlShader();
    void setSource(GLsizei const count, GLchar const *source[]);
    GLint compile();
    GLuint getId() const;

    static GlShader loadFromFile(std::string const &filename,
        GLenum const type=-1);

  private:
    GLuint id;
    GLenum type;
};
