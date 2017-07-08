#pragma once

#include "window.hxx"

class GlVertexArray {
  public:
    GlVertexArray();
    ~GlVertexArray();
    void bind();
    
  private:
    GLuint id;
};
