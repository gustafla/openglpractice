#include "sky.hxx"

ScSky::ScSky(Demo const &demo):
  demo(demo),
  sky(Shader::loadFromFile(demo, "sky.frag")),
  clouds(GlTexture::loadFromFile("test.png"))
{
  sky.addRocketTrack("sky:sunpos.x");
  sky.addRocketTrack("sky:sunpos.y");
  //sky.addRocketTrack("test");
}

void ScSky::draw() const {
  GlTexture::useUnit(0);
  clouds.bind();
  sky.draw();
}
