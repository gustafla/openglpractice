#include <iostream>
#include "window.hxx"
#include "fps_counter.hxx"
#include <GL/gl.h>

int main(int argc, char *argv[]) {
  std::cout << "OpenGL test\n";

  Window window;
  FpsCounter fpsCounter(4, 255);
  float timeLast, time, dTime;

  while (window.swapBuffers()) {
    // Approximate deltatime
    timeLast = time;
    time = window.getTime();
    dTime = time - timeLast;

    // Run the FPS counter
    fpsCounter.addDeltaTime(dTime);
    fpsCounter.printer(time);

    glClear(GL_COLOR_BUFFER_BIT);
  }

  return 0;
}
