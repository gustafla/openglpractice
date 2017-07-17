#include "debug.hxx"
#include "loading_bar.hxx"
#include "verts.hxx"
#include "gl_shader.hxx"

static std::string const _vs = 
"#version 100\n"
"precision highp float;\n"
"attribute vec3 a_pos;\n"
"uniform float u_xscale;\n"
"uniform float u_yscale;\n"
"void main() {\n"
"  gl_Position = vec4(a_pos.x*u_xscale, a_pos.y*u_yscale, a_pos.z, 1.);\n"
"}\n";

static std::string const _fs =
"#version 100\n"
"precision highp float;\n"
"uniform float u_bright;\n"
"void main() {\n"
"   gl_FragColor = vec4(vec3(u_bright), 1.);\n"
"}\n";

LoadingBar::LoadingBar(Window &window):
  state(0.f),
  shader(GlShader(GL_VERTEX_SHADER, _vs), GlShader(GL_FRAGMENT_SHADER, _fs)),
  vertexAttrib(shader.getAttribLocation("a_pos"), 3, GL_FLOAT, GL_FALSE,
      3*sizeof(GLfloat), &Verts::square),
  window(window)
{
  chk(__FILE__, __LINE__);
  draw();
}

void LoadingBar::setState(float state) {
  this->state = state;
  draw();
}

void LoadingBar::draw() const {
  chk(__FILE__, __LINE__);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  shader.use();
  chk(__FILE__, __LINE__);
  vertexAttrib.bind();
  chk(__FILE__, __LINE__);

  // Draw base
  glUniform1f(shader.getUniformLocation("u_bright"), 1.0f);
  glUniform1f(shader.getUniformLocation("u_xscale"), 0.9f);
  glUniform1f(shader.getUniformLocation("u_yscale"), 0.15f);
  chk(__FILE__, __LINE__);
  glDrawArrays(GL_TRIANGLES, 0, 6);
  chk(__FILE__, __LINE__);

  glClear(GL_DEPTH_BUFFER_BIT);
  chk(__FILE__, __LINE__);

  // Draw unfill
  glUniform1f(shader.getUniformLocation("u_bright"), 0.0f);
  glUniform1f(shader.getUniformLocation("u_xscale"), 0.88f);
  glUniform1f(shader.getUniformLocation("u_yscale"), 0.12f);
  chk(__FILE__, __LINE__);
  glDrawArrays(GL_TRIANGLES, 0, 6);
  chk(__FILE__, __LINE__);

  glClear(GL_DEPTH_BUFFER_BIT);
  chk(__FILE__, __LINE__);

  // Draw fill
  glUniform1f(shader.getUniformLocation("u_bright"), 1.0f);
  glUniform1f(shader.getUniformLocation("u_xscale"), 0.88f*state);
  glUniform1f(shader.getUniformLocation("u_yscale"), 0.12f);
  chk(__FILE__, __LINE__);
  glDrawArrays(GL_TRIANGLES, 0, 6);
  chk(__FILE__, __LINE__);

  glClear(GL_DEPTH_BUFFER_BIT);
  chk(__FILE__, __LINE__);

  window.swapBuffers();
  chk(__FILE__, __LINE__);
}
