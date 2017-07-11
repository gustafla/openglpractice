#include <iostream>
#include "window.hxx"
#include "fps_counter.hxx"
#include "gl_program.hxx"
#include "gl_shader.hxx"
#include "gl_buffer.hxx"
#include "gl_vertex_array.hxx"
#include <cmath>

static const GLfloat _verts[] = {
  -0.5, -0.5, 0, 0, 0, 0,
  0, -0.5, 0, 0, 0, 0,
  -0.25, 0.25, 0, 0, 0, 0,
  0, -0.5, 0, 1, 0, 0,
  0.5, -0.5, 0, 0, 1, 0,
  0.25, 0.25, 0, 0, 0, 1
};

static const GLuint _indices[] = {
  0, 1, 2,
  3, 4, 5
};

static const GLchar *_fs2 =
"#version 330 core\n"
"out vec4 FragColor;\n"
"in vec3 o_color;\n"
"void main() {\n"
"  FragColor = vec4(o_color, 1.0);\n"
"}\n";

class Renderer {
  public:
    Renderer():
      vb(GL_ARRAY_BUFFER, sizeof(_verts), (GLvoid*)_verts, GL_STATIC_DRAW),
      eb(GL_ELEMENT_ARRAY_BUFFER, sizeof(_indices), (GLvoid*)_indices, GL_STATIC_DRAW)
    {
  
      GlShader vs = GlShader::loadFromFile("vs.vert");
      GlShader fs = GlShader::loadFromFile("fs.frag");
      GlShader fs2(GL_FRAGMENT_SHADER, 1, &_fs2);
  
      shader.attachShader(vs);
      shader.attachShader(fs);
      if (!shader.link()) {
        exit(EXIT_FAILURE);
      }

      shader_u_time = glGetUniformLocation(shader.getId(), "u_time");

      shader2.attachShader(vs);
      shader2.attachShader(fs2);
      if (!shader2.link()) {
        exit(EXIT_FAILURE);
      }
  
      va.bind();
      eb.bind();
      vb.bind();
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), (void*)0);
      glEnableVertexAttribArray(0);
      glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), (void*)(3*sizeof(GLfloat)));
      glEnableVertexAttribArray(1);
      va.unbind();
    }

    void render(float t) {
      shader.use();
      glUniform1f(shader_u_time, t);
      va.bind();
      glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
      va.unbind();

      shader2.use();
      va.bind();
      glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (GLvoid*)(3*sizeof(GLuint)));
      va.unbind();
    }

  private:
    GlBuffer vb;
    GlBuffer eb;
    GlProgram shader;
    GlProgram shader2;
    GlVertexArray va;
    GLint shader_u_time;
};

int main(int argc, char *argv[]) {
  std::cout << "OpenGL test\n";

  Window window;
  FpsCounter fpsCounter(2, 64);
  float timeLast, time, frameTime;

  Renderer r;

  //glDisable(GL_CULL_FACE);

  while (window.swapBuffers()) {
    // Approximate timings
    timeLast = time;
    time = window.getTime();
    frameTime = time - timeLast;

    // Run the FPS counter
    fpsCounter.addFrameTime(frameTime);
    fpsCounter.printer(time);

    // Clear for good luck
    glClearColor(1,0,0,1);
    glClear(GL_COLOR_BUFFER_BIT);

    // Render
    r.render(time);

    // Show window fb contents
    window.swapBuffers();
  }

  return 0;
}
