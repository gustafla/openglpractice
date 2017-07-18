#include "gl_vertex_attrib.hxx"
#include "debug.hxx"

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

void GlVertexAttrib::bind() const {
  chk(__FILE__, __LINE__);
  glVertexAttribPointer(index, size, type, normalized, stride, pointer);
  chk(__FILE__, __LINE__);
  glEnableVertexAttribArray(index);
  chk(__FILE__, __LINE__);
}
