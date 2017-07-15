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
