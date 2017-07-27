#include "gl_framebuffer.hxx"
#include "debug.hxx"

GlFramebuffer::GlFramebuffer(GLsizei width, GLsizei height):
  prevId(0),
  texture(width, height, GL_RGBA),
  depth(width, height)
{
  glGenFramebuffers(1, &id);
  bind();
  chk(__FILE__, __LINE__);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
      texture.getId(), 0);
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
      GL_RENDERBUFFER, depth.getId());

  switch(glCheckFramebufferStatus(GL_FRAMEBUFFER)) {
    case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
      die("GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT"); break;
    case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS:
      die("GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS"); break;
    case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
      die("GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT"); break;
    case GL_FRAMEBUFFER_UNSUPPORTED:
      die("GL_FRAMEBUFFER_UNSUPPORTED"); break;
    default:
      msg("Unknown framebuffer status!!"); break;
    case GL_FRAMEBUFFER_COMPLETE:
      msg("Framebuffer complete."); break;
  }
}

GlFramebuffer::~GlFramebuffer() {
  glDeleteFramebuffers(1, &id);
  msg("Framebuffer deleted.");
}

void GlFramebuffer::storeCurrent() {
  glGetIntegerv(GL_FRAMEBUFFER_BINDING, &prevId);
}

void GlFramebuffer::bind() const {
  glBindFramebuffer(GL_FRAMEBUFFER, id);
}

void GlFramebuffer::unbind() const {
  glBindFramebuffer(GL_FRAMEBUFFER, prevId);
}

GlTexture const &GlFramebuffer::getTexture() const {
  return texture;
};
