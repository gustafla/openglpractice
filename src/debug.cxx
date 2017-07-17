#include "debug.hxx"
#include <GLES2/gl2.h>
#include <cstdlib>
#include <iostream>

void die(std::string const &msg) {
  std::cout << msg << std::endl;
  exit(EXIT_FAILURE);
}

void msg(std::string const &msg) {
#ifndef SYNC_PLAYER
  std::cout << msg << std::endl;
#endif
}

void chk(std::string const &msg) {
#ifndef SYNC_PLAYER
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
  chk(msg1 + " " + std::to_string(n) + ":");
}

void chk() {
  chk("");
}
