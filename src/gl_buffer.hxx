#pragma once

#include "window.hxx"
#include "bindable.hxx"

class GlBuffer: public Bindable {
  public:
    GlBuffer(GLenum const type);
    GlBuffer(GLenum const type, GLsizeiptr const size, GLvoid const *data,
        GLenum const usage);
    ~GlBuffer();
    void bind() const;
    void unbind() const;
    void setData(GLsizeiptr const size, GLvoid const *data, GLenum const usage);
    void setSubData(GLintptr const offset, GLsizeiptr const size,
        GLvoid const *data);

  private:
    GLuint id;
    GLenum type;
};
