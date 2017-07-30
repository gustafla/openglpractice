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

size_t const Verts::lenSquare = sizeof(square) / sizeof(GLfloat);

Verts::Verts():
  bufSquare(GL_ARRAY_BUFFER,
      sizeof(GLfloat)*Verts::lenSquare, Verts::square, GL_STATIC_DRAW),
  tunnel(makeTunnel()),
  bufTunnel(GL_ARRAY_BUFFER,
      sizeof(GLfloat)*tunnel.size(), &tunnel[0], GL_STATIC_DRAW)
{}

std::vector<GLfloat> Verts::makeTunnel() {
  std::vector<GLfloat> mesh;

  float const SIZ = (M_PI*2.f)/12.f;
  for (float u=-20.f; u<20.f; u+=1.f) {
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
