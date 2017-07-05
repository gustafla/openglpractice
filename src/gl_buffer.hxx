#pragma once

#include "window.hxx"

class GlBuffer {
  public:
    GlBuffer(GLenum type);
    ~GlBuffer();
    void bind();
    void setData(GLsizeiptr size, GLvoid *data, GLenum usage);
    void setSubData(GLintptr offset, GLsizeiptr size, GLvoid *data);

  private:
    GLuint id;
    GLenum type;
};
