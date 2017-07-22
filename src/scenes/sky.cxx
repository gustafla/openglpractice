#include "sky.hxx"

ScSky::ScSky(Demo const &demo):
  demo(demo),
  sky(Shader::loadFromFile(demo, "sky.frag"))
//  clouds(GL_TEXTURE_2D)
{
  sky.addRocketTrack("sky:sunpos.x");
  sky.addRocketTrack("sky:sunpos.y");
  //sky.addRocketTrack("test");
}

void ScSky::draw() const {
  sky.draw();
}
