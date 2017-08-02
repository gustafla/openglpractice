#include "debug.hxx"
#include <cstdlib>
#include <iostream>
#include "window.hxx"

void die(std::string const &msg) {
  std::cout << msg << std::endl;
#ifdef BUILD_RPI
  bcm_host_deinit();
#endif
  exit(EXIT_FAILURE);
}

void msg(std::string const &msg) {
#ifndef BUILD_RELEASE
  std::cout << msg << std::endl;
#endif
}

void chk(std::string const &msg) {
#ifndef BUILD_RELEASE
  switch(glGetError()) {
    default:
      die(msg + "\nUnknown OpenGL error"); break;
    case GL_OUT_OF_MEMORY:
      die(msg + "\nOpenGL out of memory"); break;
    case GL_INVALID_FRAMEBUFFER_OPERATION:
      die(msg + "\nOpenGL invalid framebuffer operation"); break;
    case GL_INVALID_OPERATION:
      die(msg + "\nOpenGL invalid operation"); break;
    case GL_INVALID_VALUE:
      die(msg + "\nOpenGL invalid value"); break;
    case GL_INVALID_ENUM:
      die(msg + "\nOpenGL invalid enum"); break;
    case GL_NO_ERROR:
      break;
  }
#endif
}

void chk(std::string const &msg1, int n) {
#ifndef BUILD_RELEASE
  chk(msg1 + " " + std::to_string(n) + ":");
#endif
}

void chk() {
#ifndef BUILD_RELEASE
  chk("");
#endif
}
