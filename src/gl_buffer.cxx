#include "gl_buffer.hxx"

GlBuffer::GlBuffer(GLenum type):
  type(type) {
  glGenBuffers(1, &id);
}

GlBuffer::GlBuffer(GLenum type, GLsizeiptr size, GLvoid *data, GLenum usage):
  GlBuffer(type) {
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

void GlBuffer::setData(GLsizeiptr size, GLvoid *data, GLenum usage) {
  bind();
  glBufferData(type, size, data, usage);
}

void GlBuffer::setSubData(GLintptr offset, GLsizeiptr size, GLvoid *data) {
  bind();
  glBufferSubData(type, offset, size, data);
}

