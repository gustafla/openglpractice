#include "verts.hxx"

GLfloat const Verts::square[] = {
  -1, -1, 0,
  1, -1, 0,
  -1, 1, 0,
  1, -1, 0,
  1, 1, 0,
  -1, 1, 0
};

size_t const Verts::lenSquare = sizeof(square) / sizeof(GLfloat);

Verts::Verts():
bufSquare(GL_ARRAY_BUFFER,
    sizeof(GLfloat)*Verts::lenSquare, Verts::square, GL_STATIC_DRAW)
{}
