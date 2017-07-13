#pragma once

#ifdef BUILD_RPI
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <SDL/SDL.h>
#else
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glext.h>
#endif // BUILD_RPI

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
