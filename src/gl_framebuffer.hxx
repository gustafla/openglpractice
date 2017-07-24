#pragma once

#include "window.hxx"
#include "bindable.hxx"
#include "gl_texture.hxx"
#include "gl_renderbuffer.hxx"

class GlFramebuffer: public Bindable {
  public:
    GlFramebuffer(GLsizei width, GLsizei height);
    ~GlFramebuffer();
    GlTexture const &getTexture() const;
    void bind() const;
    void unbind() const;

  private:
    GlTexture texture;
    GlRenderbuffer depth;
    GLuint id;
};
