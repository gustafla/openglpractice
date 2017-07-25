#include "window.hxx"
#include "debug.hxx"
#include <cstdlib>
#include <iostream>

Window::Window():
  width(960),
  height(540)
{
  open();
  restoreViewport();
  bind();
  glClearColor(0,0,0,1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
  chk(__FILE__, __LINE__);
}

Window::~Window() {
  close();
}

#ifdef BUILD_RPI
void Window::open() {
  // Initialize SDL for audio, input and time
  SDL_Init(SDL_INIT_EVERYTHING);
  SDL_SetVideoMode(0, 0, 0, SDL_SWSURFACE|SDL_FULLSCREEN);
  SDL_ShowCursor(0);

  // Start videocore rendering and query current screen resolution
  bcm_host_init();
  if (graphics_get_display_size(0, (uint32_t*)&nativeWindow.width,
        (uint32_t*)&nativeWindow.height) < 0) {
    die("Failed to get display size.");
  }

  // Dispmanx variables and config
  DISPMANX_DISPLAY_HANDLE_T dispmanDisplay;
  DISPMANX_UPDATE_HANDLE_T dispmanUpdate;
  VC_RECT_T src = {0, 0, width << 16, height << 16};
  VC_RECT_T dst = {0, 0, nativeWindow.width, nativeWindow.height};
  VC_DISPMANX_ALPHA_T alpha = {
    DISPMANX_FLAGS_ALPHA_FIXED_ALL_PIXELS, 255, 0
  };

  // Open a videocore display and set up updating
  dispmanDisplay = vc_dispmanx_display_open(0);
  dispmanUpdate = vc_dispmanx_update_start(0);

  // Add the display element
  nativeWindow.element = vc_dispmanx_element_add(
      dispmanUpdate, dispmanDisplay, 0, &dst, 0, &src,
      DISPMANX_PROTECTION_NONE, &alpha, 0, (DISPMANX_TRANSFORM_T)0);

  // Start updating the display I guess?
  vc_dispmanx_update_submit_sync(dispmanUpdate);

  // Temporary variables and config for EGL
  EGLint numConfigs, majorVersion, minorVersion;
  EGLConfig eglConfig;
  EGLint contextAttribs[] = {EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE};
  EGLint attribList[] = {
    EGL_RED_SIZE,       5,
    EGL_GREEN_SIZE,     6,
    EGL_BLUE_SIZE,      5,
    EGL_ALPHA_SIZE,     8,
    EGL_DEPTH_SIZE,     8,
    EGL_STENCIL_SIZE,   8,
    EGL_SAMPLE_BUFFERS, 0,
    EGL_NONE
  };

  display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
  if (display == EGL_NO_DISPLAY) {
    die("Failed to get EGL display.");
  }

  if (!eglInitialize(display, &majorVersion, &minorVersion)) {
    die("Failed to initialize EGL.");
  }

  if (!eglChooseConfig(display, attribList, &eglConfig, 1, &numConfigs)) {
    die("eglChooseConfig failed.");
  }

  buffer = eglCreateWindowSurface(
      display, eglConfig, (EGLNativeWindowType)&nativeWindow, nullptr);

  if (buffer == EGL_NO_SURFACE) {
    die("Failed to get EGL back buffer.");
  }

  context = eglCreateContext(
      display, eglConfig, EGL_NO_CONTEXT, contextAttribs);

  if (context == EGL_NO_CONTEXT) {
    die("eglCreateContext failed.");
  }

  if (!eglMakeCurrent(display, buffer, buffer, context)) {
    die("eglMakeCurrent failed.");
  }
}
#else
void Window::open() {
  SDL_Init(SDL_INIT_EVERYTHING);

  SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_FRAMEBUFFER_SRGB_CAPABLE, 1);

  window = SDL_CreateWindow("",
      SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
      width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

  context = SDL_GL_CreateContext(window);

  /*glewExperimental = GL_TRUE;
  glewInit();*/

  SDL_GL_SetSwapInterval(1);
  SDL_ShowCursor(0);
}
#endif // BUILD_RPI

bool Window::swapBuffers() const {
  chk(__FILE__, __LINE__);

#ifdef BUILD_RPI
  eglSwapBuffers(display, buffer);
#else
  SDL_GL_SwapWindow(window);
#endif

  SDL_PollEvent((SDL_Event* const)&events);

  if (events.type == SDL_QUIT)
    return false;
  else if (events.type == SDL_KEYDOWN)
    if (events.key.keysym.sym == SDLK_ESCAPE)
      return false;

  return true;
}

void Window::close() {
#ifdef BUILD_RPI
  bcm_host_deinit();
#else
  SDL_DestroyWindow(window);
#endif
  SDL_Quit();
}

void Window::bind() const {
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Window::restoreViewport() const {
  glViewport(0, 0, width, height);
}

SDL_Event const &Window::getEvents() const {
  return events;
}

int const Window::getWidth() const {
  return width;
}

int const Window::getHeight() const {
  return height;
}
