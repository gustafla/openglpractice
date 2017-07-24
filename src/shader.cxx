#include "shader.hxx"
#include "debug.hxx"
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

std::string trackNameToBaseName(std::string const &name) {
  return name.substr(0, name.find_last_of("."));
}

Shader Shader::loadFromFile(Demo const &demo, std::string filename) {
  msg("Shader::loadFromFile " + filename);
  return Shader(demo, GlShader::loadFromFile(filename));
}

Shader::Shader(Demo const &demo, GlShader const &fs):
  demo(demo),
  program(demo.getShaders().vs, fs),
  vaPos(
      program.getAttribLocation("a_pos"), 3, GL_FLOAT, GL_FALSE,
      3*sizeof(GLfloat), &Verts::square)
{
  msg("Shader::Shader(Demo const &demo, GlShader const &fs)");
  program.use();
  glUniform2f(program.getUniformLocation("u_resolution"),
      demo.getWidth(), demo.getHeight());
}

Shader::Shader(Demo const &demo, std::string const &fsSource):
  Shader(demo, GlShader(GL_FRAGMENT_SHADER, fsSource))
{
}

void Shader::draw() const {
  program.use();
  vaPos.bind();
  glUniform1f(program.getUniformLocation("u_time"), demo.getTime());
  glUniform1f(program.getUniformLocation("u_fft_bass"), demo.getFftBass());
  glUniform1f(program.getUniformLocation("u_fft_treble"), demo.getFftTreble());

  int ntrack=1;
  for (std::pair<std::string, RocketTrackUniform> const &t: tracks) {
    switch(t.second.tracks.size()) {
      default:
        die("Shader's rocket track " + t.first + " has incorrect size!"); break;
      case 1:
        msg("id now: " + std::to_string(t.second.id));
        glUniform1f(t.second.id, V(t.second.tracks.at(0))); break;
      case 2:
        glUniform2f(t.second.id, V(t.second.tracks.at(0)),
            V(t.second.tracks.at(1))); break;
      case 3:
        glUniform3f(t.second.id, V(t.second.tracks.at(0)),
            V(t.second.tracks.at(1)), V(t.second.tracks.at(2))); break;
      case 4:
        glUniform4f(t.second.id, V(t.second.tracks.at(0)),
            V(t.second.tracks.at(1)), V(t.second.tracks.at(2)),
            V(t.second.tracks.at(3))); break;
    }
    chk(__FILE__ + std::string(" track=") + std::to_string(ntrack)
        + " (total=" + std::to_string(tracks.size()) + ")", __LINE__);
    ntrack++;
  }

  glDrawArrays(GL_TRIANGLES, 0, Verts::lenSquare/3);
}

void Shader::addRocketTrack(std::string const &name) {
  std::string base = trackNameToBaseName(name);
  std::string ufm = trackNameToUniformName(base);
  msg("Rocket uniform " + std::string(ufm));
  if (tracks.count(base)) {
    msg("preexisiting " + base);
    tracks.at(base).tracks.push_back(demo.getRocketTrack(name));
  } else {
    GLint id = program.getUniformLocation(ufm);
    msg("id: " + std::to_string(id));
    tracks.insert(std::pair<std::string, RocketTrackUniform>(base,
          RocketTrackUniform(demo.getRocketTrack(name), id)));
  }
}
