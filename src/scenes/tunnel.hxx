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
        void drawMetacubes(float time) const;
        Demo const &demo;

        GlProgram tunnelShader;
        BindArray tunnelBinds;

        GlProgram cubeShader;
        BindArray cubeBinds;

        sync_track const *ball1x;
        sync_track const *ball1y;
        sync_track const *ballr;
        sync_track const *cuberx;
        sync_track const *cubery;

        GLuint const u_rotation;
        GLuint const u_translation;
        GLuint const u_df;
    };

    TunnelRenderer const tunnelRenderer;

    //Shader bright;
    //Shader gaussx;
    //Shader gaussy;
    Shader gaussxy;
    Shader tunnelpost;
    Pipeline post;
};
