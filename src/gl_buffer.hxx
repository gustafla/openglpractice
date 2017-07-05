#pragma once

#include "window.hxx"

class GlBuffer {
  public:
    GlBuffer(GLenum type);
    GlBuffer(GLenum type, GLsizeiptr size, GLvoid *data, GLenum usage);
    ~GlBuffer();
    void bind();
    void setData(GLsizeiptr size, GLvoid *data, GLenum usage);
    void setSubData(GLintptr offset, GLsizeiptr size, GLvoid *data);

  private:
    GLuint id;
    GLenum type;
};
