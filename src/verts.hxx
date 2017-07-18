#pragma once

#include "window.hxx"
#include "gl_buffer.hxx"

class Verts {
  public:
    Verts();

    static GLfloat const square[];
    static size_t const lenSquare;

    GlBuffer const bufSquare;
};
