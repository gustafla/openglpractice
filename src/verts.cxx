#include "verts.hxx"
#include <cmath>

GLfloat const Verts::square[] = {
  -1, -1, 0,
  1, -1, 0,
  -1, 1, 0,
  1, -1, 0,
  1, 1, 0,
  -1, 1, 0
};
GLsizei const Verts::lenSquare = sizeof(Verts::square) / sizeof(GLfloat);

GLfloat const Verts::cube[] = {
  -1, -1, -1,
  -1, 1, -1,
  1, 1, -1,
  1, 1, -1,
  1, -1, -1,
  -1, -1, -1,

  -1, -1, 1,
  1, 1, 1,
  1, -1, 1,
  -1, -1, 1,
  -1, 1, 1,
  1, 1, 1,

  1, 1, -1,
  1, -1, -1,
  1, 1, 1,
  1, 1, 1,
  1, -1, -1,
  1, -1, 1,

  -1, 1, -1,
  1, 1, -1,
  -1, 1, 1,
  -1, 1, 1,
  1, 1, -1,
  1, 1, 1,

  -1, -1, -1,
  1, -1, -1,
  -1, -1, 1,
  1, -1, -1,
  -1, -1, 1,
  1, -1, 1,

  -1, -1, -1,
  -1, 1, -1,
  -1, 1, 1,
  -1, -1, -1,
  -1, 1, 1,
  -1, -1, 1
}; // Advanced procedural mesh generation
GLsizei const Verts::lenCube = sizeof(Verts::cube) / sizeof(GLfloat);

Verts::Verts():
  bufSquare(GL_ARRAY_BUFFER,
      sizeof(GLfloat)*Verts::lenSquare, Verts::square, GL_STATIC_DRAW),
  tunnel(makeTunnel(12.f, 1.f, 10.)),
  tunnelHd(makeTunnel(23., 0.8, -10.)),
  bufTunnel(GL_ARRAY_BUFFER,
      sizeof(GLfloat)*tunnel.size(), &tunnel[0], GL_STATIC_DRAW),
  bufTunnelHd(GL_ARRAY_BUFFER,
      sizeof(GLfloat)*tunnelHd.size(), &tunnelHd[0], GL_STATIC_DRAW),
  bufCube(GL_ARRAY_BUFFER,
      sizeof(GLfloat)*Verts::lenCube, Verts::cube, GL_STATIC_DRAW)
{}

std::vector<GLfloat> Verts::makeTunnel(float rp, float zp, float end) {
  std::vector<GLfloat> mesh;

  float const SIZ = (M_PI*2.f)/rp;
  for (float u=-end; u<20.; u+=zp) {
    for (float v=0.0f; v<2.f*M_PI-0.01; v+=SIZ) {
      // Tri 1
      mesh.push_back(std::cos(v));
      mesh.push_back(std::sin(v));
      mesh.push_back(u);

      mesh.push_back(std::cos(v+SIZ));
      mesh.push_back(std::sin(v+SIZ));
      mesh.push_back(u);

      mesh.push_back(std::cos(v));
      mesh.push_back(std::sin(v));
      mesh.push_back(u+1.);
      // Tri 2
      mesh.push_back(std::cos(v+SIZ));
      mesh.push_back(std::sin(v+SIZ));
      mesh.push_back(u);

      mesh.push_back(std::cos(v+SIZ));
      mesh.push_back(std::sin(v+SIZ));
      mesh.push_back(u+1.);

      mesh.push_back(std::cos(v));
      mesh.push_back(std::sin(v));
      mesh.push_back(u+1.);
    }
  }

  return mesh;
}

