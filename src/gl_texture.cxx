#include "gl_texture.hxx"
#include "stb_image.h"
#include "debug.hxx"
#include <iostream>

#define PREF_FORMAT GL_UNSIGNED_BYTE

// These are pretty much the only ones allowed by ES2.0
static const GLenum _FORMAT_LUT[] = {
  GL_NONE, GL_LUMINANCE, GL_LUMINANCE_ALPHA, GL_RGB, GL_RGBA
};

GlTexture GlTexture::loadFromFile(std::string const &filename, GLenum target) {
  GlTexture texture(target);
  texture.setTexParameter(GL_TEXTURE_WRAP_S, GL_REPEAT);
  texture.setTexParameter(GL_TEXTURE_WRAP_T, GL_REPEAT);
  texture.setTexParameter(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  texture.setTexParameter(GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  // set loader param
  stbi_set_flip_vertically_on_load(true);

  // load the image
  int width, height, nChannels;
  unsigned char *data = stbi_load(filename.c_str(), &width, &height,
      &nChannels, 0);
  if (data) { // set it into the texture object
    texture.setTexImage2D(0, _FORMAT_LUT[nChannels], width, height, 0,
        _FORMAT_LUT[nChannels], PREF_FORMAT, data);
    // ES2.0 spec needs internal format and format to be the same
  } else {
    die("Failed to load texture " + filename);
  }
  stbi_image_free(data);
  return texture;
}

void GlTexture::useUnit(unsigned int const offset) {
  glActiveTexture(GL_TEXTURE0 + offset);
}

GlTexture::GlTexture(GLenum target):
  target(target), width(0), height(0)
{
  glGenTextures(1, &id);
}

GlTexture::GlTexture(GLsizei width, GLsizei height, GLenum format, GLint filter,
    GLint wrap, GLenum target):
  GlTexture(target)
{
  setTexImage2D(0, format, width, height, 0, format, PREF_FORMAT, nullptr);
  setTexParameter(GL_TEXTURE_WRAP_S, wrap);
  setTexParameter(GL_TEXTURE_WRAP_T, wrap);
  setTexParameter(GL_TEXTURE_MIN_FILTER, filter);
  setTexParameter(GL_TEXTURE_MAG_FILTER, filter);
}

GlTexture::~GlTexture() {
  glDeleteTextures(1, &id);
}

void GlTexture::bind() const {
  glBindTexture(target, id);
}

void GlTexture::setTexImage2D(GLint level, GLint internalFormat,
    GLsizei width, GLsizei height, GLint border,
    GLenum format, GLenum type, GLvoid const *data) {
  bind();
  glTexImage2D(target, level, internalFormat, width, height, border, format,
      type, data);
  this->width = width;
  this->height = height;
}

void GlTexture::setTexSubImage2D(GLint level, GLint xoffset, GLint yoffset,
    GLsizei width, GLsizei heigh, GLenum format, GLenum type,
    GLvoid const *data) const {
  bind();
  glTexSubImage2D(target, level, xoffset, yoffset, width, height, format, type,
      data);
}

void GlTexture::generateMipmap() {
  bind();
  glGenerateMipmap(target);
}

void GlTexture::setTexParameter(GLenum pName, GLint param) {
  bind();
  glTexParameteri(target, pName, param);
}

GLuint GlTexture::getId() const {
  return id;
}

GLsizei GlTexture::getWidth() const {
  return width;
}

GLsizei GlTexture::getHeight() const {
  return height;
}
