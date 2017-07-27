#include "debug.hxx"
#include <iostream>
#include <string>
#include <memory>
#include <random>
#include "window.hxx"
#include "fps_counter.hxx"
#include "demo.hxx"
#include "mixer.hxx"
#include "shader.hxx"

#include "scenes/test.hxx"
#include "scenes/sky.hxx"

#define NOISE_SIZE 128

uint32_t g_seed = 20; 
inline uint32_t fastrand() { 
  g_seed = (214013*g_seed+2531011); 
  return (g_seed>>16)&0x7FFF; 
}

void generateNoise(GlTexture &texture) {
  static GLubyte buf[NOISE_SIZE * NOISE_SIZE * 3];
  for (int i=0; i<NOISE_SIZE*NOISE_SIZE*3; ++i) {
    buf[i] = fastrand()%255;
  }
  texture.setTexSubImage2D(0, 0, 0, NOISE_SIZE, NOISE_SIZE, GL_RGB,
      GL_UNSIGNED_BYTE, buf);
}

std::vector<std::unique_ptr<Drawable>> _scenes;

void initScenes(Demo &d) {
  _scenes.clear();
  _scenes.push_back(std::unique_ptr<Drawable>(new ScSky(d)));
}

int main(int argc, char *argv[]) {
  std::cout <<
#ifdef BUILD_NAME
    STRING(BUILD_NAME) 
#else
    "OpenGL test"
#endif
    << std::endl << "Platform: " <<
#ifdef BUILD_RPI
    "Raspberry Pi"
#else
    "Linux PC"
#endif
    << std::endl;

  Window window;
  Demo demo(window);

  // Post processing
  GlFramebuffer postBuf(demo.getWidth(), demo.getHeight());
  Shader post(demo, GlShader::loadFromFile("post.frag"));
  post.addRocketTrack("post:whiteout");
  post.addRocketTrack("post:fft_bass");
  post.addRocketTrack("post:fft_treble");
  post.addRocketTrack("post:rbs");
  GlTexture noise(NOISE_SIZE, NOISE_SIZE, GL_RGB, GL_LINEAR);
  generateNoise(noise);

  sync_track const *scn = demo.getRocketTrack("scene");
  initScenes(demo);

  // Free some memory
#ifdef BUILD_RELEASE
  glReleaseShaderCompiler();
#endif

  FpsCounter fpsCounter(2, 64);
  float timeLast, time, frameTime;

  while (window.swapBuffers()) {
    // Approximate timings
    timeLast = time;
    time = demo.getTime();
    frameTime = time - timeLast;

    // Run the FPS counter
    fpsCounter.addFrameTime(frameTime);
    fpsCounter.printer(time);

    // Update demo data
    demo.update();

    // Bind window FB
    window.bind();

    // Render
    postBuf.storeCurrent();
    postBuf.bind();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    _scenes[static_cast<int>(demo.getValue(scn))]->draw();
    postBuf.unbind();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    GlTexture::useUnit(0);
    postBuf.getTexture().bind();
    GlTexture::useUnit(2);
    noise.bind();
    generateNoise(noise);
    post.draw();

    // Press R to reload !!!
#ifndef BUILD_RELEASE
    if (window.getEvents().type == SDL_KEYDOWN) {
      if (window.getEvents().key.keysym.sym == SDLK_r) {
        initScenes(demo);
        // Reload post shader
        post.~Shader();
        new(&post) Shader(demo, GlShader::loadFromFile("post.frag"));
      }
    }
#endif
  }

  return 0;
}
