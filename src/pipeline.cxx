#include "pipeline.hxx"
#include "debug.hxx"

Pipeline::Pipeline(Demo const &demo):
  demo(demo)
{}

void Pipeline::addStage(Drawable const *stage) {
  stages.push_back(stage);

  // Last stage has no FBO
  if (stages.size() > 1) {
    framebuffers.push_back(GlFramebuffer(demo.getWidth(), demo.getHeight()));
  }
}

void Pipeline::draw() const {
  // Query current FBO to bind for the last stage
  GLint prevFramebufferId = 0;
  glGetIntegerv(GL_FRAMEBUFFER_BINDING, &prevFramebufferId);
  chk(__FILE__, __LINE__);

  for(int i=0; i<stages.size(); ++i) {
    chk(__FILE__ + std::string(" i=") + std::to_string(i), __LINE__);
    // If internal FBO op, not last
    if(i<stages.size()-1) {
      framebuffers[i].bind();
    } else { // If last bind the FBO bound at the beginning of call
      glBindFramebuffer(GL_FRAMEBUFFER, prevFramebufferId);
    }
    chk(__FILE__ + std::string(" i=") + std::to_string(i), __LINE__);

    // If not first bind -1 fbo tex
    if (i>0) {
      GlTexture::useUnit(0);
      framebuffers[i-1].getTexture().bind();
    }

    // If not second bind -2 fbo tex
    if (i>1) {
      GlTexture::useUnit(1);
      framebuffers[i-2].getTexture().bind();
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    stages[i]->draw();
    chk(__FILE__ + std::string(" i=") + std::to_string(i), __LINE__);
  }
}
