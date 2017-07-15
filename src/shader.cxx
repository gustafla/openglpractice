#include "shader.hxx"
#include "gl_shader.hxx"
#include "verts.hxx"
#include <string>

Shader Shader::loadFromFile(Demo const &demo, std::string filename) {
  return Shader(demo, GlShader::loadFromFile(filename));
}

Shader::Shader(Demo const &demo, GlShader const &fs):
  demo(demo),
  program(demo.getShaders().vs, fs),
  vaPos(
      program.getAttribLocation("a_pos"), 3, GL_FLOAT, GL_FALSE,
      3*sizeof(GLfloat), &Verts::square)
{
}

Shader::Shader(Demo const &demo, std::string const &fsSource):
  Shader(demo, GlShader(GL_FRAGMENT_SHADER, fsSource))
{
}

void Shader::draw() const {
  program.use();
  vaPos.bind();
  program.setUfm("u_time", demo.getPlayer().getTime());
  program.setUfm("u_fft_bass", demo.getPlayer().getFftBass());
  program.setUfm("u_fft_treble", demo.getPlayer().getFftTreble());
  glDrawArrays(GL_TRIANGLES, 0, Verts::lenSquare/3);
}
