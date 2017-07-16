#include "test.hxx"

ScTest::ScTest(Demo const &demo):
  shader(Shader::loadFromFile(demo, "fs.frag"))
{
  shader.addRocketTrack("test");
}

void ScTest::draw() const {
  shader.draw();
}
