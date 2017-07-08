#pragma once

#include "window.hxx"

class GlVertexArray {
  public:
    GlVertexArray();
    ~GlVertexArray();
    void bind();
    void unbind();

  private:
    GLuint id;
};
