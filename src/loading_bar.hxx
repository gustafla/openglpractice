#pragma once

#include "window.hxx"
#include "gl_vertex_attrib.hxx"
#include "gl_program.hxx"
#include <string>

class LoadingBar {
  public:
    LoadingBar(Window &window);
    void setState(float state);

  private:
    void draw();

    float state;
    GlProgram shader;
    GlVertexAttrib vertexAttrib;

    Window &window;
};
