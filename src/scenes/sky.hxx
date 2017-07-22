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
    virtual void draw() const;

  private:
    Demo const &demo;
    Shader sky;
    //GlTexture clouds;
};
