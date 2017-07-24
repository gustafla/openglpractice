#pragma once

#include "window.hxx"
#include <string>

class GlTexture {
  public:
    GlTexture(GLenum target=GL_TEXTURE_2D);
    GlTexture(GLsizei width, GLsizei height, GLenum format=GL_RGB,
        GLint filter=GL_NEAREST, GLint wrap=GL_REPEAT,
        GLenum target=GL_TEXTURE_2D);
    ~GlTexture();
    void bind() const;
    void setTexImage2D(GLint level, GLint internalFormat, GLsizei width,
        GLsizei height, GLint border, GLenum format, GLenum type,
        GLvoid const *data);
    void setTexSubImage2D(GLint level, GLint xoffset, GLint yoffset,
        GLsizei width, GLsizei heigh, GLenum format, GLenum type,
        GLvoid const *data) const;
    void generateMipmap();
    void setTexParameter(GLenum pName, GLint param);
    // do etc when needed
    GLuint getId() const;
    GLsizei getWidth() const;
    GLsizei getHeight() const;

    static GlTexture loadFromFile(std::string const &filename,
        GLenum target=GL_TEXTURE_2D);
    static void useUnit(unsigned int offset);

  private:
    GLuint id;
    GLsizei width;
    GLsizei height;
    GLenum const target;
};
