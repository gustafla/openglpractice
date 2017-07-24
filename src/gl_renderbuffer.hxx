#pragma once

#include "window.hxx"
#include "bindable.hxx"

class GlRenderbuffer: public Bindable {
  public:
    GlRenderbuffer(GLsizei width, GLsizei height,
        GLenum format=GL_DEPTH_COMPONENT16);
    ~GlRenderbuffer();
    GLuint getId() const;
    void bind() const;
    void unbind() const;

  private:
    GLuint id;
};
