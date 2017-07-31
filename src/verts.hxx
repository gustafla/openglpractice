#pragma once

#include "window.hxx"
#include "gl_buffer.hxx"
#include <vector>

class Verts {
  public:
    Verts();

    static GLfloat const square[];
    static GLsizei const lenSquare;

    std::vector<GLfloat> const tunnel;
    std::vector<GLfloat> const tunnelHd;
    std::vector<GLfloat> makeTunnel(float rp, float zp, float end);

    static GLfloat const cube[];
    static GLsizei const lenCube;

    GlBuffer const bufSquare;
    GlBuffer const bufTunnel;
    GlBuffer const bufTunnelHd;
    GlBuffer const bufCube;
};
