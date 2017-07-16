#include "test.hxx"

ScTest::ScTest(Demo const &demo):
  shader(Shader::loadFromFile(demo, "fs.frag"))
{
}

void ScTest::draw() const {
  shader.draw();
}
