#include "gl_shader.hxx"
#include "debug.hxx"
#include <iostream>
#include <vector>
#include <fstream>

GlShader GlShader::loadFromFile(std::string const &filename,
    GLenum const type) {
  msg("GlShader::loadFromFile(std::string const &filename=\"" + filename
      + "\", GLenum const type)");
  std::ifstream file(filename);
  if (file.fail()) {
    die("Failed to open file " + filename);
  }

  std::string filetext((std::istreambuf_iterator<char>(file)),
      std::istreambuf_iterator<char>()); // Read file to std::string

  GLenum realtype;
  if (type != -1) { // if parameter defines a seemingly valid type
    realtype = type;
  } else { // otherwise guess based on the filename
    switch(filename.c_str()[filename.find_last_of(".") + 1]) {
      case 'f': case 'F': default:
        realtype = GL_FRAGMENT_SHADER;
        break;
      case 'v': case 'V':
        realtype = GL_VERTEX_SHADER;
        break;
      /*case 'g': case 'G':
        realtype = GL_GEOMETRY_SHADER;
        break;
      case 'c': case 'C':
        realtype = GL_COMPUTE_SHADER;*/ // These are not usable in ES2
    }
  }

  //const char* filetextptr = filetext.c_str(); //BAD, but it's alright for this
  //return GlShader(realtype, 1, &filetextptr);
  return GlShader(realtype, filetext);
}

GlShader::GlShader(GLenum const type):
  type(type)
{
  id = glCreateShader(type);
  chk(__FILE__, __LINE__);
}

GlShader::GlShader(GLenum const type, GLsizei const count,
    GLchar const *sources[]):
  GlShader(type)
{
  setSource(count, sources);
  compile(std::string(sources[0]));
}

GlShader::GlShader(GLenum const type, std::string const &source):
  GlShader(type)
{
  msg("GlShader::GlShader(GLenum const type, std::string const &source)");
  GLchar const *ptr = source.c_str();
  setSource(1, &ptr);
  compile(source);
}

GlShader::~GlShader() {
  msg("GlShader destroyed!");
  glDeleteShader(id);
}

void GlShader::setSource(GLsizei const count, GLchar const *sources[]) {
  std::vector<GLint> lens(count, -1);
  glShaderSource(id, count, sources, &lens[0]);
  chk(__FILE__, __LINE__);
}

GLint GlShader::compile(std::string const &extra) {
  msg("GlShader::compile:\n"+extra);
  glCompileShader(id); 
  chk(__FILE__, __LINE__);
  GLint succ;
  GLchar log[512];
  glGetShaderiv(id, GL_COMPILE_STATUS, &succ);
  chk(__FILE__, __LINE__);
  if (!succ) {
    glGetShaderInfoLog(id, 512, NULL, log);
    die("Error compiling shader:\n" + std::string(extra) + "\n"
        + std::string(log));
  }
  msg("shader compiled with status " + std::to_string(succ));
  return succ;
}

GLuint GlShader::getId() const {
  return id;
}
