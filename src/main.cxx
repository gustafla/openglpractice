#include <iostream>
#include "window.hxx"
#include "fps_counter.hxx"
#include "player.hxx"

#include "gl_program.hxx"
#include "gl_vertex_attrib.hxx"

void tri() {
  static const float verts[] = {
    -0.5, -0.5, 0.0,
    0.5, -0.5, 0.0,
    0.0, 0.5, 0.0
  };

  static const GlProgram shader =
    GlProgram::loadFromFiles("vs.vert", "fs.frag");

  static const GlVertexAttrib attrib(0, 3, GL_FLOAT, GL_FALSE,
      3*sizeof(GLfloat), &verts);

  shader.use();
  attrib.bind();
  glDrawArrays(GL_TRIANGLES, 0, 3);
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
    glClear(GL_COLOR_BUFFER_BIT);

    // Render
    tri();

    // Show window fb contents
    window.swapBuffers();
  }

  return 0;
}
