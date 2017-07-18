#include "sky.hxx"

ScSky::ScSky(Demo const &demo):
  demo(demo),
  sky(Shader::loadFromFile(demo, "sky.frag"))
//  clouds(GL_TEXTURE_2D)
{
  sky.addRocketTrack("sunpos.x");
  sky.addRocketTrack("sunpos.y");
  //sky.addRocketTrack("test");
}

void ScSky::draw() const {
  sky.draw();
}
