#include "gl_buffer.hxx"

GlBuffer::GlBuffer(GLenum const type):
  type(type)
{
  glGenBuffers(1, &id);
}

GlBuffer::GlBuffer(GLenum const type, GLsizeiptr const size,
    GLvoid const *data, GLenum const usage):
  GlBuffer(type)
{
  setData(size, data, usage);
}

GlBuffer::~GlBuffer() {
  glDeleteBuffers(1, &id);
}

void GlBuffer::bind() {
  glBindBuffer(type, id);
}

void GlBuffer::unbind() {
  glBindBuffer(type, 0);
}

void GlBuffer::setData(GLsizeiptr const size, GLvoid const *data,
    GLenum const usage) {
  bind();
  glBufferData(type, size, data, usage);
}

void GlBuffer::setSubData(GLintptr const offset, GLsizeiptr const size,
    GLvoid const *data) {
  bind();
  glBufferSubData(type, offset, size, data);
}

