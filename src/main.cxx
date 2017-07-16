#include <iostream>
#include "window.hxx"
#include "fps_counter.hxx"
#include "demo.hxx"

#include "scenes/test.hxx"

int main(int argc, char *argv[]) {
  std::cout << "OpenGL test" << std::endl << "Platform: " <<
#ifdef BUILD_RPI
    "Raspberry Pi"
#else
    "Linux PC"
#endif
    << std::endl;

  Window window;
  Demo demo(window);

  ScTest testScene(demo);

  FpsCounter fpsCounter(2, 64);
  float timeLast, time, frameTime;

  while (window.swapBuffers()) {
    // Approximate timings
    timeLast = time;
    time = demo.getPlayer().getTime();
    std::cout << time << std::endl;
    frameTime = time - timeLast;

    // Run the FPS counter
    fpsCounter.addFrameTime(frameTime);
    fpsCounter.printer(time);

    // Bind window FB
    window.bind();

    // Clear for good luck
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Render
    testScene.draw();
  }

  return 0;
}
