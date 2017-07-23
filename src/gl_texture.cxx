#include "gl_texture.hxx"
#include "stb_image.h"
#include <iostream>

static const GLenum FORMAT_LUT[] = {
  GL_NONE, GL_LUMINANCE, GL_LUMINANCE_ALPHA, GL_RGB, GL_RGBA
};

GlTexture GlTexture::loadFromFile(std::string const &filename,
    GLenum const target) {
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
    texture.setTexImage2D(0, FORMAT_LUT[nChannels], width, height, 0,
        FORMAT_LUT[nChannels], GL_UNSIGNED_BYTE, data);
  } else {
    std::cout << "Failed to load texture " << filename << std::endl;
  }
  stbi_image_free(data);
  return texture;
}

void GlTexture::useUnit(unsigned int const offset) {
  glActiveTexture(GL_TEXTURE0 + offset);
}

GlTexture::GlTexture(GLenum const target):
  target(target)
{
  glGenTextures(1, &id);
}

GlTexture::~GlTexture() {
  glDeleteTextures(1, &id);
}

void GlTexture::bind() const {
  glBindTexture(target, id);
}

void GlTexture::setTexImage2D(GLint const level, GLint const internalFormat,
    GLsizei const width, GLsizei const height, GLint const border,
    GLenum const format, GLenum const type, GLvoid const *data) {
  bind();
  glTexImage2D(target, level, internalFormat, width, height, border, format,
      type, data);
}

void GlTexture::generateMipmap() {
  bind();
  glGenerateMipmap(target);
}

void GlTexture::setTexParameter(GLenum const pName, GLint const param) {
  bind();
  glTexParameteri(target, pName, param);
}

GLuint GlTexture::getId() const {
  return id;
}
