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
  idTime(program.getUniformLocation("u_time")),
  idFftBass(program.getUniformLocation("u_fft_bass")),
  idFftTreble(program.getUniformLocation("u_fft_treble")),
  vaPos(
      program.getAttribLocation("a_pos"), 3, GL_FLOAT, GL_FALSE,
      3*sizeof(GLfloat), &Verts::square)
{
  msg("Shader::Shader(Demo const &demo, GlShader const &fs)");
  program.use();
  glUniform2f(program.getUniformLocation("u_resolution"),
      demo.getWidth(), demo.getHeight());

  // Set up sampler ufms
  for (int i=0; i<DEMO_N_PREV_FBO; ++i) {
    glUniform1i(program.getUniformLocation("u_f" + std::to_string(i+1)), i);
  }
  glUniform1i(program.getUniformLocation("u_t1"), DEMO_N_PREV_FBO+0);
  glUniform1i(program.getUniformLocation("u_t2"), DEMO_N_PREV_FBO+1);
  glUniform1i(program.getUniformLocation("u_t3"), DEMO_N_PREV_FBO+2);
  glUniform1i(program.getUniformLocation("u_t4"), DEMO_N_PREV_FBO+3);
}

Shader::Shader(Demo const &demo, std::string const &fsSource):
  Shader(demo, GlShader(GL_FRAGMENT_SHADER, fsSource))
{
}

void Shader::draw() const {
  program.use();
  vaPos.bind();
  glUniform1f(idTime, demo.getTime());
  glUniform1f(idFftBass, demo.getFftBass());
  glUniform1f(idFftTreble, demo.getFftTreble());

  int track=1;
  for (auto const &t: tracks) {
    switch(t.second.nTracks) {
      default:
        die("Shader's rocket track " + t.first + " has incorrect size!"); break;
      case 1:
        glUniform1f(t.second.id, V(t.second.tracks[0])); break;
      case 2:
        glUniform2f(t.second.id, V(t.second.tracks[0]),
            V(t.second.tracks[1])); break;
      case 3:
        glUniform3f(t.second.id, V(t.second.tracks[0]),
            V(t.second.tracks[1]), V(t.second.tracks[2])); break;
      case 4:
        glUniform4f(t.second.id, V(t.second.tracks[0]),
            V(t.second.tracks[1]), V(t.second.tracks[2]),
            V(t.second.tracks[3])); break;
    }
    chk(__FILE__ + std::string(" track=") + std::to_string(track)
        + " (total=" + std::to_string(tracks.size()) + ")", __LINE__);
    track++;
  }

  glDrawArrays(GL_TRIANGLES, 0, Verts::lenSquare/3);
}

void Shader::addRocketTrack(std::string const &name) {
  std::string base = trackNameToBaseName(name);
  std::string ufm = trackNameToUniformName(base);
  msg("Rocket uniform " + std::string(ufm));
  if (tracks.count(base)) {
    msg("preexisiting " + base);
    RocketTrackUniform &t = tracks.at(base);
    if (t.nTracks < 4) {
      t.tracks[t.nTracks] = demo.getRocketTrack(name);
      t.nTracks++;
    } else {
      die("Shader: RocketTrackUniform too many tracks per uniform.");
    }
  } else {
    GLint id = program.getUniformLocation(ufm);
    msg("id: " + std::to_string(id));
    tracks.insert(std::pair<std::string, RocketTrackUniform>(base,
          RocketTrackUniform(demo.getRocketTrack(name), id)));
  }
}

void Shader::setUniform(GLuint id, int n, float const v[]) const {
  GLint previousProgram;
  glGetIntegerv(GL_CURRENT_PROGRAM, &previousProgram);
  program.use();
  switch(n) {
    case 1:
      glUniform1f(id, v[0]); break;
    case 2:
      glUniform2f(id, v[0], v[1]); break;
    case 3:
      glUniform3f(id, v[0], v[1], v[2]); break;
    case 4:
      glUniform4f(id, v[0], v[1], v[2], v[3]); break;
    default:
      die("Shader::setUniform (float) invalid size");
  }
  glUseProgram(previousProgram);
}

void Shader::setUniform(GLuint id, int n, int const v[]) const {
  GLint previousProgram;
  glGetIntegerv(GL_CURRENT_PROGRAM, &previousProgram);
  program.use();
  switch(n) {
    case 1:
      glUniform1i(id, v[0]); break;
    case 2:
      glUniform2i(id, v[0], v[1]); break;
    case 3:
      glUniform3i(id, v[0], v[1], v[2]); break;
    case 4:
      glUniform4i(id, v[0], v[1], v[2], v[3]); break;
    default:
      die("Shader::setUniform (int) invalid size");
  }
  glUseProgram(previousProgram);
}

void Shader::setUniform(std::string const &name, int n, float const v[]) const {
  setUniform(program.getUniformLocation(name), n, v);
}

void Shader::setUniform(std::string const &name, int n, int const v[]) const {
  setUniform(program.getUniformLocation(name), n, v);
}
