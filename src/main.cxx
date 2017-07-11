#include <iostream>
#include "window.hxx"
#include "fps_counter.hxx"
#include "gl_program.hxx"
#include "gl_shader.hxx"
#include "gl_buffer.hxx"
#include "gl_vertex_array.hxx"
#include <cmath>

static const GLfloat _verts[] = {
  -0.5, -0.5, 0,
  0, -0.5, 0,
  -0.25, 0.25, 0,
  0, -0.5, 0,
  0.5, -0.5, 0,
  0.25, 0.25, 0
};

static const GLuint _indices[] = {
  0, 1, 2,
  3, 4, 5
};

static const GLchar *_vs = 
"#version 330 core\n"
"layout (location=0) in vec3 aPos;\n"
"void main() {\n"
"  gl_Position = vec4(aPos, 1.0);\n"
"}\n";

static const GLchar *_fs =
"#version 330 core\n"
"out vec4 FragColor;\n"
"void main() {\n"
"  FragColor = vec4(0.0, 0.2, 1.0, 1.0);\n"
"}\n";

class Renderer {
  public:
    Renderer():
      vb(GL_ARRAY_BUFFER, sizeof(_verts), (GLvoid*)_verts, GL_STATIC_DRAW),
      eb(GL_ELEMENT_ARRAY_BUFFER, sizeof(_indices), (GLvoid*)_indices, GL_STATIC_DRAW)
    {
  
      GlShader vs(GL_VERTEX_SHADER, 1, &_vs);
      GlShader fs(GL_FRAGMENT_SHADER, 1, &_fs);
  
      shader.attachShader(vs);
      shader.attachShader(fs);
  
      if (!shader.link()) {
        exit(EXIT_FAILURE);
      }
  
      va.bind();
      eb.bind();
      vb.bind();
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), (void*)0);
      glEnableVertexAttribArray(0);
      va.unbind();
      vb.unbind();
      eb.unbind();
    }

    void render(float t) {
      va.bind();
      shader.use();
      //glDrawArrays(GL_TRIANGLES, 0, 6);
      glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
      va.unbind();
    }

  private:
    GlBuffer vb;
    GlBuffer eb;
    GlProgram shader;
    GlVertexArray va;
};

int main(int argc, char *argv[]) {
  std::cout << "OpenGL test\n";

  Window window;
  FpsCounter fpsCounter(4, 255);
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
