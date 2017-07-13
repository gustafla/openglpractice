#pragma once

#include "window.hxx"
#include "bindable.hxx"

class GlVertexAttrib: public Bindable {
  public:
    GlVertexAttrib(GLuint index, GLint size, GLenum type, GLboolean normalized,
        GLsizei stride, GLvoid const *pointer);
    void bind();

  private:
    GLuint const index;
    GLint const size;
    GLenum const type;
    GLboolean const normalized;
    GLsizei const stride;
    GLvoid const *pointer;
};
