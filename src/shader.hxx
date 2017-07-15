#pragma once

#include "window.hxx"
#include "gl_vertex_attrib.hxx"
#include "gl_program.hxx"
#include "demo.hxx"
#include "drawable.hxx"

class Shader: public Drawable {
  public:
    Shader(Demo const &demo, GlShader const &fs);
    Shader(Demo const &demo, std::string const &fsSource);
    void draw() const;

    static Shader loadFromFile(Demo const &demo, std::string filename);

  private:
    Demo const &demo;
    GlProgram program;
    GlVertexAttrib vaPos;
};
