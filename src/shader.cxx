#include "shader.hxx"
#include "gl_shader.hxx"
#include "verts.hxx"
#include <string>
#include <iostream>
#include <algorithm>

std::string trackNameToUniformName(std::string const &name) {
  std::string cleaned = name;
  std::replace(cleaned.begin(), cleaned.end(), ':', '_');
  std::replace(cleaned.begin(), cleaned.end(), '.', '_');
  return "u_" + cleaned;
}

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
  glUniform1f(program.getUniformLocation("u_time"),
      demo.getPlayer().getTime());
  glUniform1f(program.getUniformLocation("u_fft_bass"),
      demo.getPlayer().getFftBass());
  glUniform1f(program.getUniformLocation("u_fft_treble"),
      demo.getPlayer().getFftTreble());

  for (auto const &t: tracks) {
    glUniform1f(t.id, demo.getValue(t.track));
  }

  glDrawArrays(GL_TRIANGLES, 0, Verts::lenSquare/3);
}

void Shader::addRocketTrack(std::string const &name) {
  tracks.push_back(RocketTrackUniform(demo.getRocketTrack(name),
        program.getUniformLocation(trackNameToUniformName(name))));
}
