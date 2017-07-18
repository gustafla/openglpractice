#pragma once

#include "window.hxx"
#include "gl_vertex_attrib.hxx"
#include "gl_program.hxx"
#include "drawable.hxx"
#include <string>

class LoadingBar: public Drawable {
  public:
    LoadingBar(Window &window);
    void setState(float state);

  private:
    void draw() const;

    float state;
    GlProgram program;
    GlVertexAttrib vertexAttrib;

    Window &window;
};
