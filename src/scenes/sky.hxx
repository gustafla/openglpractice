#pragma once

#include "../window.hxx"
#include "../gl_texture.hxx"
#include "../drawable.hxx"
#include "../demo.hxx"
#include "../stb_perlin.h"
#include "../shader.hxx"

class ScSky: public Drawable {
  public:
    ScSky(Demo const &demo);
    ~ScSky();
    void draw() const;

  private:
    Demo const &demo;
    Shader sky;
    GlTexture clouds;
    GLubyte *cloudbuf;

    sync_track const *octaves;
    sync_track const *lacunarity;
    sync_track const *gain;
    sync_track const *mult;

    void genClouds() const;
};
