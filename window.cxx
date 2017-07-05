#include "window.hxx"
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <cstdlib>
#include <GL/gl.h>

Window::Window():
width(1280), height(720) {
  open();
}

Window::~Window() {
  close();
}

void Window::open() {
  SDL_Init(SDL_INIT_EVERYTHING);
  
  SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);

  window = SDL_CreateWindow("",
      SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
      width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN
  );

  context = SDL_GL_CreateContext(window);

  glewExperimental = GL_TRUE;
  glewInit();

  SDL_GL_SetSwapInterval(1);
  SDL_ShowCursor(0);
  restoreViewport();
  bind();
}

bool Window::swapBuffers() {
  SDL_GL_SwapWindow(window);
  SDL_PollEvent(&events);

  if (events.type == SDL_QUIT)
    return false;
  else if (events.type == SDL_KEYDOWN)
    if (events.key.keysym.sym == SDLK_ESCAPE)
      return false;

  return true;
}


void Window::close() {
  SDL_DestroyWindow(window);
  SDL_Quit();
}

void Window::bind() {
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Window::restoreViewport() {
  glViewport(0, 0, width, height);
}

