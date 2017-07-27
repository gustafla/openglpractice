#pragma once

#include "../window.hxx"
#include "../gl_texture.hxx"
#include "../drawable.hxx"
#include "../demo.hxx"
#include "../stb_perlin.h"
#include "../shader.hxx"
#include "../pipeline.hxx"

class ScSky: public Drawable {
  public:
    ScSky(Demo const &demo);
    ~ScSky();
    void draw() const;

  private:
    Demo const &demo;
    Shader sky;
    Shader rays;
    GlTexture clouds;
    GLubyte *cloudbuf;
    Pipeline pipeline;

    sync_track const *octaves;
    sync_track const *lacunarity;
    sync_track const *gain;
    sync_track const *mult;
    sync_track const *clouds_x;
    sync_track const *clouds_z;

    GlFramebuffer fbTest;

    void genClouds() const;
};
