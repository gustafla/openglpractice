#include "gl_vertex_attrib.hxx"

GlVertexAttrib::GlVertexAttrib(GLuint index, GLint size, GLenum type,
    GLboolean normalized, GLsizei stride, GLvoid const *pointer):
  index(index),
  size(size),
  type(type),
  normalized(normalized),
  stride(stride),
  pointer(pointer)
{
}

void GlVertexAttrib::bind() {
  glVertexAttribPointer(index, size, type, normalized, stride, pointer);
  glEnableVertexAttribArray(index);
}
