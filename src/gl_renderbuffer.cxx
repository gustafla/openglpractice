#include "gl_renderbuffer.hxx"

GlRenderbuffer::GlRenderbuffer(GLsizei width, GLsizei height, GLenum format) {
  glGenRenderbuffers(1, &id);
  bind();
  glRenderbufferStorage(GL_RENDERBUFFER, format, width, height);
}

GlRenderbuffer::~GlRenderbuffer() {
  glDeleteRenderbuffers(1, &id);
}

GLuint GlRenderbuffer::getId() const {
  return id;
}

void GlRenderbuffer::bind() const {
  glBindRenderbuffer(GL_RENDERBUFFER, id);
}

void GlRenderbuffer::unbind() const {
  glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

