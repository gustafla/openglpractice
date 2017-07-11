#include "gl_shader.hxx"
#include <iostream>
#include <vector>
#include <fstream>

GlShader GlShader::loadFromFile(std::string const &filename, GLenum const type) {
  std::ifstream file(filename);
  if (file.fail()) {
    std::cout << "Failed to open file " << filename << std::endl;
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
      case 'g': case 'G':
        realtype = GL_GEOMETRY_SHADER;
        break;
      case 'c': case 'C':
        realtype = GL_COMPUTE_SHADER;
    }
  }

  const char* filetextptr = filetext.c_str(); //BAD, but it's alright for this
  return GlShader(realtype, 1, &filetextptr);
}

GlShader::GlShader(GLenum const type):
  type(type)
{
  id = glCreateShader(type);
}

GlShader::GlShader(GLenum const type, GLsizei const count, GLchar const *sources[]):
  GlShader(type)
{
  setSource(count, sources);
  compile();
}

GlShader::~GlShader() {
  glDeleteShader(id);
}

void GlShader::setSource(GLsizei const count, GLchar const *sources[]) {
  std::vector<GLint> lens(count, -1);
  glShaderSource(id, count, sources, &lens[0]);
}

GLint GlShader::compile() {
  glCompileShader(id); 
  GLint succ;
  GLchar log[512];
  glGetShaderiv(id, GL_COMPILE_STATUS, &succ);
  if (!succ) {
    glGetShaderInfoLog(id, 512, NULL, log);
    std::cout << "Error compiling shader\n" << log << std::endl;
  }
  return succ;
}

GLuint GlShader::getId() const {
  return id;
}
