#pragma once

#include "../window.hxx"
#include "../gl_texture.hxx"
#include "../drawable.hxx"
#include "../demo.hxx"
#include "../stb_perlin.h"
#include "../shader.hxx"
#include "../pipeline.hxx"
#include "../gl_program.hxx"
#include "../bind_array.hxx"

class ScTunnel: public Drawable {
  public:
    ScTunnel(Demo const &demo);
    ~ScTunnel();
    void draw() const;

  private:
    Demo const &demo;

    class TunnelRenderer: public Drawable {
      public:
        TunnelRenderer(Demo const &demo);
        void draw() const;

      private:
        Demo const demo;
        GlProgram tunnelShader;
        BindArray tunnelBinds;
    };

    TunnelRenderer tunnelRenderer;

    Shader gaussx;
    Shader gaussy;
    Shader tunnelpost;
    Pipeline post;
};
