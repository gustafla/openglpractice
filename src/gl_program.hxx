#pragma once

#include "window.hxx"
#include "gl_shader.hxx"

class GlProgram {
  public:
    GlProgram();
    GlProgram(GlShader &vs, GlShader &fs);
    ~GlProgram();
    void attachShader(GlShader &s);
    GLint link();
    void use();
    GLuint getId();

  private:
    GLuint id;
};
