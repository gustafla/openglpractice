#include <iostream>
#include "window.hxx"
#include "fps_counter.hxx"
#include "player.hxx"

#include "gl_program.hxx"
#include "gl_vertex_attrib.hxx"

void tri(float t) {
  static const float verts[] = {
    -1, -1, 0,
    1, -1, 0,
    -1, 1, 0,
    1, -1, 0,
    1, 1, 0,
    -1, 1, 0
  };

  static const GlProgram shader =
    GlProgram::loadFromFiles("vs.vert", "fs.frag");

  static const GlVertexAttrib attrib(0, 3, GL_FLOAT, GL_FALSE,
      3*sizeof(GLfloat), &verts);

  shader.use();
  attrib.bind();
  shader.setUfm("u_time", t);
  glDrawArrays(GL_TRIANGLES, 0, 6);
}

int main(int argc, char *argv[]) {
  std::cout << "OpenGL test" << std::endl << "Platform: " <<
#ifdef BUILD_RPI
    "Raspberry Pi"
#else
    "Linux PC"
#endif
    << std::endl;

  Window window;
  FpsCounter fpsCounter(2, 64);
  float timeLast, time, frameTime;

  Player player("music.ogg");
  player.start();

  glClearColor(1,0,0,1);

  while (window.swapBuffers()) {
    // Approximate timings
    timeLast = time;
    time = window.getTime();
    frameTime = time - timeLast;

    // Run the FPS counter
    fpsCounter.addFrameTime(frameTime);
    fpsCounter.printer(time);

    // Clear for good luck
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Render
    tri(time);
  }

  return 0;
}
