#pragma once

#ifdef BUILD_RPI
#include <bcm_host.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>
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

    int const width;
    int const height;

  private:
    void open();
    void close();

#ifdef BUILD_RPI
    EGL_DISPMANX_WINDOW_T nativeWindow;
    EGLDisplay display;
    EGLSurface buffer;
#else
    SDL_Window *window;
    SDL_GLContext context;
#endif

    SDL_Event events;
};
