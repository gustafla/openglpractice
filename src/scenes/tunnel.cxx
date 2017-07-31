#include "tunnel.hxx"
#include "../debug.hxx"

ScTunnel::ScTunnel(Demo const &demo):
  demo(demo),
  //bright(Shader::loadFromFile(demo, "bright.frag")),
  //gaussx(Shader::loadFromFile(demo, "gaussx.frag")),
  //gaussy(Shader::loadFromFile(demo, "gaussy.frag")),
  gaussxy(Shader::loadFromFile(demo, "gaussxy.frag")),
  tunnelpost(Shader::loadFromFile(demo, "tunnelpost.frag")),
  post(demo),
  tunnelRenderer(demo)
{
  post.addStage(&tunnelRenderer);
  //post.addStage(&bright);
  post.addStage(&gaussxy);
  //post.addStage(&gaussy);
  post.addStage(&tunnelpost);
}

void ScTunnel::draw() const {
  post.draw();
}

// ---------------- TunnelRenderer ---------------------------------------------

ScTunnel::TunnelRenderer::TunnelRenderer(Demo const &demo):
  demo(demo),
  cuberx(demo.getRocketTrack("tunnel:cube_rot.x")),
  cubery(demo.getRocketTrack("tunnel:cube_rot.y")),
  ball1x(demo.getRocketTrack("tunnel:ball1.x")),
  ball1y(demo.getRocketTrack("tunnel:ball1.y")),
  ballr(demo.getRocketTrack("tunnel:ball.r")),
  tunnelShader(GlProgram::loadFromFiles("tunnel2.vert", "tunnel2.frag")),
  cubeShader(GlProgram::loadFromFiles("cube.vert", "cube.frag")),
  u_rotation(cubeShader.getUniformLocation("u_rotation")),
  u_translation(cubeShader.getUniformLocation("u_translation")),
  u_df(cubeShader.getUniformLocation("u_df"))
{
  tunnelShader.use();
  glUniformMatrix4fv(tunnelShader.getUniformLocation("u_projection"),
      1, GL_FALSE, &demo.getProjectionMatrix()[0][0]);
  tunnelBinds.recordBind(std::shared_ptr<Bindable const>(
        &demo.getVerts().bufTunnelHd));
  tunnelBinds.recordBind(std::shared_ptr<Bindable const>(
        new GlVertexAttrib(tunnelShader.getAttribLocation("a_pos"), 3,
          GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), nullptr)));

  cubeShader.use();
  glUniformMatrix4fv(cubeShader.getUniformLocation("u_projection"),
      1, GL_FALSE, &demo.getProjectionMatrix()[0][0]);
  cubeBinds.recordBind(std::shared_ptr<Bindable const>(
        &demo.getVerts().bufCube));
  cubeBinds.recordBind(std::shared_ptr<Bindable const>(
        new GlVertexAttrib(cubeShader.getAttribLocation("a_pos"), 3,
          GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), nullptr)));
}

float ball(glm::vec3 p, float r) {
  return glm::length(p);
}

void ScTunnel::TunnelRenderer::drawMetacubes(float time) const {
  cubeShader.use();

  glm::mat4 ir = glm::rotate(glm::mat4(1.), V(cubery),
      glm::vec3(0, 1, 0));
  ir = glm::rotate(ir, V(cuberx), glm::vec3(1, 0, 0));
  glUniformMatrix4fv(u_rotation ,1, GL_FALSE, &ir[0][0]);


  for (float x=-5; x<6; x+=1.1f) {
    for (float y=-5; y<6; y+=1.1f) {
      for (float z=0; z<6; z+=1.1f) {
        glm::vec3 p = glm::vec3(x, y, z);
        float d =
          /*(*/ball(p-glm::vec3(V(ball1x), V(ball1y), 0.7), 4.)
           //+ ball(p-glm::vec3(V(ball2x), V(ball2y), 0.), 2.))/2.
          + demo.getFftTreble() - V(ballr);

        // Outside the volume
        if (d > 0.) {
          continue;
        }

        glm::mat4 tr = glm::translate(glm::mat4(1.),
            glm::vec3(p.x, p.y, p.z-16.f));
        glUniformMatrix4fv(u_translation, 1, GL_FALSE, &tr[0][0]);
        glUniform1f(u_df, d);

        cubeBinds.bind();
        glDrawArrays(GL_TRIANGLES, 0, demo.getVerts().lenCube/3);
        cubeBinds.unbind();
      }
    }
  }
}

void ScTunnel::TunnelRenderer::draw() const {
  glDisable(GL_BLEND);
  glDisable(GL_DEPTH_TEST);
  glDisable(GL_CULL_FACE);

  tunnelShader.use();
  glUniform1f(tunnelShader.getUniformLocation("u_time"), demo.getTime());
  glUniform1f(tunnelShader.getUniformLocation("u_fft_bass"),
      demo.getFftBass());
  glUniform1f(tunnelShader.getUniformLocation("u_fft_treble"),
      demo.getFftTreble());
  tunnelBinds.bind();
  glDrawArrays(GL_TRIANGLES, 0, demo.getVerts().tunnelHd.size()/3);
  tunnelBinds.unbind();

  glClear(GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);
  //glEnable(GL_CULL_FACE);
  drawMetacubes(demo.getTime());
}
