#pragma once

#include "window.hxx"
#include <string>

class GlTexture {
  public:
    GlTexture(GLenum const target);
    ~GlTexture();
    void bind();
    void setTexImage2D(GLint const level, GLint const internalFormat,
        GLsizei const width, GLsizei const height, GLint const border,
        GLenum const format, GLenum const type, GLvoid const *data);
    void generateMipmap();
    void setTexParameter(GLenum const pName, GLint const param);
    // do etc when needed
    GLuint getId() const;

    static GlTexture loadFromFile(std::string const &filename, GLenum const target);

  private:
    GLuint id;
    GLenum const target;
};
