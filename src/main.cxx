#include "debug.hxx"
#include <iostream>
#include <string>
#include "window.hxx"
#include "fps_counter.hxx"
#include "demo.hxx"

#include "scenes/test.hxx"
#include "scenes/sky.hxx"

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

  ScSky testScene(demo);

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
    testScene.draw();
  }

  return 0;
}
