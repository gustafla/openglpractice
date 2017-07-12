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
    void use();
    GLuint getId();

    void setUfm(std::string const &name, float value);
    void setUfm(std::string const &name, bool value);
    void setUfm(std::string const &name, int value);

    static GlProgram loadFromFiles(std::string const &vsName,
        std::string const &fsName);

  private:
    GLuint id;
    std::map<std::string, GLint> uniforms;
};
