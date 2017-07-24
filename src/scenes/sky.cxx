#include "sky.hxx"
#include "../stb_perlin.h"
#include "../debug.hxx"

ScSky::ScSky(Demo const &demo):
  demo(demo),
  pipeline(demo),
  sky(Shader::loadFromFile(demo, "sky.frag")),
  rays(Shader::loadFromFile(demo, "rays.frag")),
  clouds(demo.getWidth()/10, demo.getHeight()/10, GL_LUMINANCE, GL_LINEAR),
  cloudbuf(new GLubyte[clouds.getWidth()*clouds.getHeight()]),
  octaves(demo.getRocketTrack("sky:ocataves")),
  lacunarity(demo.getRocketTrack("sky:lacunarity")),
  gain(demo.getRocketTrack("sky:gain")),
  mult(demo.getRocketTrack("sky:mult"))
{
  pipeline.addStage(&sky);
  pipeline.addStage(&rays);

  sky.addRocketTrack("sky:sunpos.x");
  sky.addRocketTrack("sky:sunpos.y");

  sky.addRocketTrack("sky:lcolor.r");
  sky.addRocketTrack("sky:lcolor.g");
  sky.addRocketTrack("sky:lcolor.b");

  sky.addRocketTrack("sky:hcolor.r");
  sky.addRocketTrack("sky:hcolor.g");
  sky.addRocketTrack("sky:hcolor.b");

  sky.addRocketTrack("sky:hccol.r");
  sky.addRocketTrack("sky:hccol.g");
  sky.addRocketTrack("sky:hccol.b");

  sky.addRocketTrack("sky:lccol.r");
  sky.addRocketTrack("sky:lccol.g");
  sky.addRocketTrack("sky:lccol.b");
}

ScSky::~ScSky() {
  delete[] cloudbuf;
}

void ScSky::draw() const {
  GlTexture::useUnit(2);
  clouds.bind();
  genClouds();
  pipeline.draw();
}

void ScSky::genClouds() const {
  for (int x=0; x<clouds.getWidth(); x++) {
    for (int y=0; y<clouds.getHeight(); y++) {
      float v = std::min(std::max(stb_perlin_turbulence_noise3(
              x*0.02f+demo.getTime(), y*0.05f, demo.getTime(),
              V(lacunarity), V(gain),
              V(octaves), 0, 0, 0)*V(mult), 0.f),
          255.f);
      //msg(std::to_string(v));
      cloudbuf[x + y * clouds.getWidth()] = v;
    }
  }
  clouds.setTexSubImage2D(0, 0, 0, clouds.getWidth(), clouds.getHeight(),
      GL_LUMINANCE, GL_UNSIGNED_BYTE, cloudbuf);
}
