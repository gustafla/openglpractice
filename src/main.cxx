#include <iostream>
#include "window.hxx"
#include "fps_counter.hxx"
#include "player.hxx"

#include "gl_program.hxx"
#include "gl_vertex_attrib.hxx"
#include "loading_bar.hxx"
#include "verts.hxx"

void tri(float t, float fftBass, float fftTreble) {
  static const GlProgram shader =
    GlProgram::loadFromFiles("vs.vert", "fs.frag");

  static const GlVertexAttrib attrib(shader.getAttribLocation("a_pos"), 3,
      GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), &Verts::square);

  shader.use();
  attrib.bind();
  shader.setUfm("u_time", t);
  shader.setUfm("u_fft_bass", fftBass/7.f);
  shader.setUfm("u_fft_treble", fftTreble/2.f);
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
  glClearColor(0,0,0,1);

  FpsCounter fpsCounter(2, 64);
  float timeLast, time, frameTime;

  Player player("music.ogg", window); // Passing window for loading bar
  player.play();

  while (window.swapBuffers()) {
    // Approximate timings
    timeLast = time;
    time = player.getTime();
    frameTime = time - timeLast;

    // Run the FPS counter
    fpsCounter.addFrameTime(frameTime);
    fpsCounter.printer(time);

    // Clear for good luck
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Render
    tri(time, player.getFftBass(), player.getFftTreble());

    // Extra inputs
    if (window.getEvents().type == SDL_KEYDOWN)
      if (window.getEvents().key.keysym.sym == SDLK_SPACE)
        player.toggle();
  }

  return 0;
}
