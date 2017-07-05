#include "gl_buffer.hxx"

GlBuffer::GlBuffer(GLenum type):
  type(type) {
  glGenBuffers(1, &id);
}

GlBuffer::~GlBuffer() {
  glDeleteBuffers(1, &id);
}

void GlBuffer::bind() {
  glBindBuffer(type, id);
}

void GlBuffer::setData(GLsizeiptr size, GLvoid *data, GLenum usage) {
  glBufferData(type, size, data, usage);
}

void GlBuffer::setSubData(GLintptr offset, GLsizeiptr size, GLvoid *data) {
  glBufferSubData(type, offset, size, data);
}

