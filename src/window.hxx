#pragma once

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glext.h>

class Window {
  public:
    Window();
    ~Window();
    void bind();
    void restoreViewport();
    bool swapBuffers();
    float getTime();

  private:
    void open();
    void close();

    SDL_Window *window;
    SDL_GLContext context;
    SDL_Event events;
    int width;
    int height;
};
