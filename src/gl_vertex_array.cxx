#include "gl_vertex_array.hxx"

GlVertexArray::GlVertexArray() {
  glGenVertexArrays(1, &id);
}

GlVertexArray::~GlVertexArray() {
  glDeleteVertexArrays(1, &id);
}

void GlVertexArray::bind() {
  glBindVertexArray(id);
}

void GlVertexArray::unbind() {
  glBindVertexArray(0);
}
