#pragma once

#include "window.hxx"
#include "gl_buffer.hxx"
#include <vector>

class Verts {
  public:
    Verts();

    static GLfloat const square[];
    static size_t const lenSquare;

    std::vector<GLfloat> const tunnel;
    std::vector<GLfloat> const tunnelHd;
    std::vector<GLfloat> makeTunnel(float rp, float zp);

    GlBuffer const bufSquare;
    GlBuffer const bufTunnel;
    GlBuffer const bufTunnelHd;
};
