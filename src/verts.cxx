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
    for (float v=0.0f; v<2.f*M_PI; v+=SIZ) {
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

/*
void fillCircularMesh(Mesh& mesh, bool up, const float STRIP_W, float y, float radius) {
    vec3 a, b, c;
    for (float r=0.0; r<PI2; r+=STRIP_W) {
        if (up) {
            a = vec3(0.0f, y, 0.0f);
            b = vec3(std::cos(r+STRIP_W)*radius, y, std::sin(r+STRIP_W)*radius);
            c = vec3(std::cos(r)*radius, y, std::sin(r)*radius);
            mesh.pushTexcoord(vec2(0.5, 0.5));
            mesh.pushTexcoord(vec2(std::cos(r+STRIP_W)/2+1, std::sin(r+STRIP_W)/2+1));
            mesh.pushTexcoord(vec2(std::cos(r)/2+1, std::sin(r)/2+1));
        } else {
            a = vec3(0.0f, y, 0.0f);
            c = vec3(std::sin(r)*radius, y, std::cos(r)*radius);
            b = vec3(std::sin(r+STRIP_W)*radius, y, std::cos(r+STRIP_W)*radius);
            mesh.pushTexcoord(vec2(0.5, 0.5));
            mesh.pushTexcoord(vec2(std::cos(r)/2+1, std::sin(r)/2+1));
            mesh.pushTexcoord(vec2(std::cos(r+STRIP_W)/2+1, std::sin(r+STRIP_W)/2+1));
        }
        pushTrianglePositionNormal(mesh, a, b, c);
    }
}
*/
