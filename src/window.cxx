#include "window.hxx"
#include <cstdlib>

Window::Window():
  width(1280), height(720)
{
  open();
}

Window::~Window() {
  close();
}

float Window::getTime() {
  return static_cast<float>(SDL_GetTicks())/1000.f;
}

#ifdef BUILD_RPI
void Window::open() {
  SDL_Init(SDL_INIT_EVERYTHING);
  SDL_SetVideoMode(0, 0, 0, SDL_SWSURFACE | SDL_FULLSCREEN);
  SDL_ShowCursor(0);

  bcm_host_init();

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

  static EGL_DISPMANX_WINDOW_T nativewindow;

  DISPMANX_ELEMENT_HANDLE_T dispman_element;
  DISPMANX_DISPLAY_HANDLE_T dispman_display;
  DISPMANX_UPDATE_HANDLE_T dispman_update;
  VC_RECT_T dst_rect;
  VC_RECT_T src_rect;

  uint32_t screenWidth, screenHeight;
  if (graphics_get_display_size(0, &screenWidth, &screenHeight) < 0) {
    exit(EXIT_FAILURE);
  }

  dst_rect.x = 0;
  dst_rect.y = 0;
  dst_rect.width = screenWidth;
  dst_rect.height = screenHeight;

  src_rect.x = 0;
  src_rect.y = 0;
  src_rect.width = width<<16;
  src_rect.height = height<<16;

  dispman_display = vc_dispmanx_display_open(0);
  dispman_update = vc_dispmanx_update_start(0);

  VC_DISPMANX_ALPHA_T dispmanAlpha = {
    DISPMANX_FLAGS_ALPHA_FIXED_ALL_PIXELS, 255, 0
  };

  dispman_element = vc_dispmanx_element_add(
      dispman_update, dispman_display, 0, &dst_rect, 0, &src_rect,
      DISPMANX_PROTECTION_NONE, &dispmanAlpha, 0, (DISPMANX_TRANSFORM_T)0
  );

  nativewindow.element = dispman_element;
  nativewindow.width = width;
  nativewindow.height = height;
  vc_dispmanx_update_submit_sync(dispman_update);

  window = &nativewindow;

  EGLint numConfigs;
  EGLint majorVersion;
  EGLint minorVersion;
  EGLDisplay eglDisplay;
  EGLContext eglContext;
  EGLSurface eglBuffer;
  EGLConfig config;

  EGLint contextAttribs[] = {EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE};

  eglDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
  if (eglDisplay == EGL_NO_DISPLAY) {
    exit(EXIT_FAILURE);
  }

  if (!eglInitialize(eglDisplay, &majorVersion, &minorVersion)) {
    exit(EXIT_FAILURE);
  }

  if (!eglChooseConfig(eglDisplay, attribList, &config, 1, &numConfigs)) {
    exit(EXIT_FAILURE);
  }

  eglBuffer = eglCreateWindowSurface(
    eglDisplay, config, (EGLNativeWindowType)window, NULL
  );

  if (eglBuffer == EGL_NO_SURFACE) {
    exit(EXIT_FAILURE);
  }

  eglContext = eglCreateContext(
    eglDisplay, config, EGL_NO_CONTEXT, contextAttribs
  );

  if (eglContext == EGL_NO_CONTEXT) {
    exit(EXIT_FAILURE);
  }

  if (!eglMakeCurrent(eglDisplay, eglBuffer, eglBuffer, eglContext)) {
    exit(EXIT_FAILURE);
  }

  display = eglDisplay;
  buffer = eglBuffer;
  context = eglContext;

  restoreViewport();
  bind();
}
#else
void Window::open() {
  SDL_Init(SDL_INIT_EVERYTHING);

  SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
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
#endif // BUILD_RPI

bool Window::swapBuffers() {
#ifdef BUILD_RPI
  eglSwapBuffers(display, buffer);
#else
  SDL_GL_SwapWindow(window);
#endif

  SDL_PollEvent(&events);

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

void Window::bind() {
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Window::restoreViewport() {
  glViewport(0, 0, width, height);
}

