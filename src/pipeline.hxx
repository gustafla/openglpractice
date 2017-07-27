#pragma once

#include "window.hxx"
#include "drawable.hxx"
#include <vector>
#include <memory>
#include "gl_framebuffer.hxx"
#include "demo.hxx"

class Pipeline: public Drawable {
  public:
    Pipeline(Demo const &demo);
    void addStage(Drawable const *stage);
    void draw() const;

  private:
    Demo const &demo;
    std::vector<Drawable const*> stages;
    std::vector<std::unique_ptr<GlFramebuffer>> framebuffers;

    void bindTextures(int stage) const;
};
