#include "tunnel.hxx"
#include "../debug.hxx"

ScTunnel::ScTunnel(Demo const &demo):
  demo(demo),
  bright(Shader::loadFromFile(demo, "bright.frag")),
  gaussx(Shader::loadFromFile(demo, "gaussx.frag")),
  gaussy(Shader::loadFromFile(demo, "gaussy.frag")),
  tunnelpost(Shader::loadFromFile(demo, "tunnelpost.frag")),
  post(demo),
  tunnelRenderer(demo)
{
  post.addStage(&tunnelRenderer);
  post.addStage(&bright);
  post.addStage(&gaussx);
  post.addStage(&gaussy);
  post.addStage(&tunnelpost);
}

void ScTunnel::draw() const {
  post.draw();
}

// ---------------- TunnelRenderer ---------------------------------------------

ScTunnel::TunnelRenderer::TunnelRenderer(Demo const &demo):
  demo(demo),
  tunnelShader(GlProgram::loadFromFiles("tunnel2.vert", "tunnel2.frag"))
{
  tunnelShader.use();
  glUniformMatrix4fv(tunnelShader.getUniformLocation("u_projection"),
      1, GL_FALSE, &demo.getProjectionMatrix()[0][0]);
  tunnelBinds.recordBind(std::shared_ptr<Bindable const>(
        &demo.getVerts().bufTunnelHd));
  tunnelBinds.recordBind(std::shared_ptr<Bindable const>(
        new GlVertexAttrib(tunnelShader.getAttribLocation("a_pos"), 3,
          GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), nullptr)));
}

void ScTunnel::TunnelRenderer::draw() const {
  tunnelShader.use();

  glUniform1f(tunnelShader.getUniformLocation("u_time"), demo.getTime());
  glUniform1f(tunnelShader.getUniformLocation("u_fft_bass"),
      demo.getFftBass());
  glUniform1f(tunnelShader.getUniformLocation("u_fft_treble"),
      demo.getFftTreble());

  tunnelBinds.bind();
  glDrawArrays(GL_TRIANGLES, 0, demo.getVerts().tunnelHd.size()/3);
  tunnelBinds.unbind();
}
