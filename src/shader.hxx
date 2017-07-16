#pragma once

#include "window.hxx"
#include "gl_vertex_attrib.hxx"
#include "gl_program.hxx"
#include "demo.hxx"
#include "drawable.hxx"
#include <vector>

class Shader: public Drawable {
  public:
    Shader(Demo const &demo, GlShader const &fs);
    Shader(Demo const &demo, std::string const &fsSource);
    void draw() const;

    static Shader loadFromFile(Demo const &demo, std::string filename);
    void addRocketTrack(std::string const &name);

  private:
    class RocketTrackUniform {
      public:
        RocketTrackUniform(sync_track const *track, GLint const id):
          track(track),
          id(id)
        {}
        sync_track const *track;
        GLint const id;
    };

    Demo const &demo;
    GlProgram program;
    GlVertexAttrib vaPos;
    std::vector<RocketTrackUniform> tracks;
};
