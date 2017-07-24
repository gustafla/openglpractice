#pragma once

#include "window.hxx"
#include "gl_vertex_attrib.hxx"
#include "gl_program.hxx"
#include "demo.hxx"
#include "drawable.hxx"
#include <vector>
#include <map>

class Shader: public Drawable {
  public:
    Shader(Demo const &demo, GlShader const &fs);
    Shader(Demo const &demo, std::string const &fsSource);
    void draw() const;

    static Shader loadFromFile(Demo const &demo, std::string filename);
    void addRocketTrack(std::string const &name);

  private:
    Demo const &demo;
    GlProgram program;
    GlVertexAttrib vaPos;

    class RocketTrackUniform {
      public:
        RocketTrackUniform(sync_track const *track, GLint const id):
          id(id)
        {tracks.push_back(track);}
        std::vector<sync_track const*>tracks;
        GLint const id;
    };

    std::map<std::string, RocketTrackUniform> tracks;
};
