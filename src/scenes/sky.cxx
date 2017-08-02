#include "sky.hxx"
#include "../stb_perlin.h"
#include "../debug.hxx"

ScSky::ScSky(Demo const &demo):
  demo(demo),
  pipeline(demo),
  sky(Shader::loadFromFile(demo, "sky.frag")),
  rays(Shader::loadFromFile(demo, "rays.frag")),
  clouds(demo.getWidth()/10, demo.getHeight()/10, GL_LUMINANCE, GL_LINEAR),
  cloudbuf(new GLubyte[clouds.getWidth()*clouds.getHeight()]),
  gain(demo.getRocketTrack("sky:gain")),
  mult(demo.getRocketTrack("sky:mult")),
  clouds_x(demo.getRocketTrack("sky:clouds.x")),
  clouds_z(demo.getRocketTrack("sky:clouds.z")),
  tunnel_alpha(demo.getRocketTrack("sky:tunnel.a")),
  tunnelShader(GlProgram::loadFromFiles("tunnel.vert", "tunnel.frag"))/*,
  showtex(Shader::loadFromFile(demo, "showtex.frag")),
  cred(GlTexture::loadFromFile("cred.png"))*/
{
  pipeline.addStage(&sky);
  pipeline.addStage(&rays);

  sky.addRocketTrack("sky:sunpos.x");
  sky.addRocketTrack("sky:sunpos.y");
  //rays.addRocketTrack("sky:sunpos.x");
  //rays.addRocketTrack("sky:sunpos.y");

  sky.addRocketTrack("sky:lcolor.r");
  sky.addRocketTrack("sky:lcolor.g");
  sky.addRocketTrack("sky:lcolor.b");

  sky.addRocketTrack("sky:hcolor.r");
  sky.addRocketTrack("sky:hcolor.g");
  sky.addRocketTrack("sky:hcolor.b");

  sky.addRocketTrack("sky:hccol.r");
  sky.addRocketTrack("sky:hccol.g");
  sky.addRocketTrack("sky:hccol.b");

  sky.addRocketTrack("sky:lccol.r");
  sky.addRocketTrack("sky:lccol.g");
  sky.addRocketTrack("sky:lccol.b");

  // Setup tunnel rendering
  tunnelShader.use();
  glUniformMatrix4fv(tunnelShader.getUniformLocation("u_projection"),
      1, GL_FALSE, &demo.getProjectionMatrix()[0][0]);
  tunnelBinds.recordBind(std::shared_ptr<Bindable const>(
        &demo.getVerts().bufTunnel));
  tunnelBinds.recordBind(std::shared_ptr<Bindable const>(
        new GlVertexAttrib(tunnelShader.getAttribLocation("a_pos"), 3,
          GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), nullptr)));
}

ScSky::~ScSky() {
  delete[] cloudbuf;
}

void ScSky::draw() const {
  glDisable(GL_BLEND);
  glDisable(GL_DEPTH_TEST);

  GlTexture::useUnit(DEMO_N_PREV_FBO + 0);
  clouds.bind();
  genClouds();
  pipeline.draw();

  glEnable(GL_BLEND);

  // Draw tunnel
  float a = V(tunnel_alpha);
  if (a > 0.01f) {
    glLineWidth(5);
    tunnelShader.use();
    glUniform1f(tunnelShader.getUniformLocation("u_time"), demo.getTime());
    glUniform1f(tunnelShader.getUniformLocation("u_fft_bass"),
        demo.getFftBass());
    glUniform1f(tunnelShader.getUniformLocation("u_fft_treble"),
        demo.getFftTreble());
    glUniform1f(tunnelShader.getUniformLocation("u_tunnel_alpha"), a);
    tunnelBinds.bind();
    glDrawArrays(GL_LINES, 0, demo.getVerts().tunnel.size()/3);
    tunnelBinds.unbind();
  }

  /*if (demo.getTime() > 1792.f/8.f) {
    GlTexture::useUnit(DEMO_N_PREV_FBO+0);
    cred.bind();
    showtex.draw();
  }*/
}

void ScSky::genClouds() const {
  for (int x=0; x<clouds.getWidth(); x++) {
    for (int y=0; y<clouds.getHeight(); y++) {
      float v = std::min(std::max(stb_perlin_turbulence_noise3(
              x*0.02f+V(clouds_x)*demo.getTime(), y*0.05f,
              V(clouds_z)*demo.getTime(),
              2., V(gain),
              5, 0, 0, 0)*V(mult), 0.f),
          255.f);
      //msg(std::to_string(v));
      cloudbuf[x + y * clouds.getWidth()] = v;
    }
  }
  clouds.setTexSubImage2D(0, 0, 0, clouds.getWidth(), clouds.getHeight(),
      GL_LUMINANCE, GL_UNSIGNED_BYTE, cloudbuf);
}
