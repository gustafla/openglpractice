#pragma once

#include "window.hxx"
#include "gl_shader.hxx"
#include <map>

class GlProgram {
  public:
    GlProgram();
    GlProgram(GlShader const &vs, GlShader const &fs);
    ~GlProgram();
    void attachShader(GlShader const &s);
    GLint link();
    void use() const;
    GLuint getId();

    void setUfm(std::string const &name, float value) const;
    void setUfm(std::string const &name, bool value) const;
    void setUfm(std::string const &name, int value) const;

    static GlProgram loadFromFiles(std::string const &vsName,
        std::string const &fsName);

  private:
    GLuint id;
    std::map<std::string, GLint> uniforms;
};
