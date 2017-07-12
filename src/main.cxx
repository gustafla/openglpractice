#include <iostream>
#include "window.hxx"
#include "fps_counter.hxx"
#include "player.hxx"

int main(int argc, char *argv[]) {
  std::cout << "OpenGL test\n";

  Window window;
  FpsCounter fpsCounter(2, 64);
  float timeLast, time, frameTime;

  Player player("music.ogg");
  player.start();

  while (window.swapBuffers()) {
    // Approximate timings
    timeLast = time;
    time = window.getTime();
    frameTime = time - timeLast;

    // Run the FPS counter
    fpsCounter.addFrameTime(frameTime);
    fpsCounter.printer(time);

    // Clear for good luck
    glClearColor(1,0,0,1);
    glClear(GL_COLOR_BUFFER_BIT);

    // Render

    // Show window fb contents
    window.swapBuffers();
  }

  return 0;
}
