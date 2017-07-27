#include "pipeline.hxx"
#include "debug.hxx"

Pipeline::Pipeline(Demo const &demo):
  demo(demo)
{}

void Pipeline::addStage(Drawable const *stage) {
  stages.push_back(stage);

  // Last stage has no FBO
  if (stages.size() > 1) {
    framebuffers.push_back(std::unique_ptr<GlFramebuffer>(
          new GlFramebuffer(demo.getWidth(), demo.getHeight())));
  }
}

void Pipeline::bindTextures(int stage) const {
  for (int i=0; i < std::min(DEMO_N_PREV_FBO, stage); ++i) {
    GlTexture::useUnit(i);
    framebuffers[stage-i-1]->getTexture().bind();
  }
}

void Pipeline::draw() const {
  if (stages.size() < 1) {
    return;
  }

  // Query current FBO to bind for the last stage
  GLint prevFramebufferId = 0;
  glGetIntegerv(GL_FRAMEBUFFER_BINDING, &prevFramebufferId);
  chk(__FILE__, __LINE__);

  for(int i=0; i<stages.size()-1; ++i) {
    framebuffers[i]->bind();
    chk(__FILE__ + std::string(" i=") + std::to_string(i), __LINE__);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    chk(__FILE__ + std::string(" i=") + std::to_string(i), __LINE__);

    bindTextures(i);
    chk(__FILE__ + std::string(" i=") + std::to_string(i), __LINE__);

    stages[i]->draw();
    chk(__FILE__ + std::string(" i=") + std::to_string(i), __LINE__);
  }

  // Output stage
  glBindFramebuffer(GL_FRAMEBUFFER, prevFramebufferId);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  bindTextures(stages.size()-1);
  stages[stages.size()-1]->draw();
}
