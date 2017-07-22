#include "debug.hxx"
#include <iostream>
#include <string>
#include "window.hxx"
#include "fps_counter.hxx"
#include "demo.hxx"

#include "scenes/test.hxx"
#include "scenes/sky.hxx"

std::vector<Drawable> _scenes;

void initScenes(Demo &d) {
  _scenes = {ScSky(d), ScTest(d)};
}

int main(int argc, char *argv[]) {
  std::cout <<
#ifdef BUILD_NAME
    STRING(BUILD_NAME) 
#else
    "OpenGL test"
#endif
    << std::endl << "Platform: " <<
#ifdef BUILD_RPI
    "Raspberry Pi"
#else
    "Linux PC"
#endif
    << std::endl;

  Window window;
  Demo demo(window);

  sync_track const *scn = demo.getRocketTrack("scene");
  initScenes(demo);
  ScSky lol(demo);

  FpsCounter fpsCounter(2, 64);
  float timeLast, time, frameTime;

  while (window.swapBuffers()) {
    // Approximate timings
    timeLast = time;
    time = demo.getTime();
    frameTime = time - timeLast;

    // Run the FPS counter
    fpsCounter.addFrameTime(frameTime);
    fpsCounter.printer(time);

    // Update demo data
    demo.update();

    // Bind window FB
    window.bind();

    // Clear for good luck
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Render
    //_scenes[static_cast<int>(demo.getValue(scn))].draw();
    //_scenes[0].draw();
    lol.draw();

    // Pressed R to reload
#ifndef SYNC_PLAYER
    if (window.getEvents().type == SDL_KEYDOWN) {
      if (window.getEvents().key.keysym.sym == SDLK_r) {
        initScenes(demo);
      }
    }
#endif
  }

  return 0;
}
