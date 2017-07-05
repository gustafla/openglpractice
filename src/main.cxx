#include <iostream>
#include "window.hxx"
#include <GL/gl.h>

int main(int argc, char *argv[]) {
  std::cout << "OpenGL test\n";

  Window window;

  while (window.swapBuffers()) {
    glClear(GL_COLOR_BUFFER_BIT);
  }
}
