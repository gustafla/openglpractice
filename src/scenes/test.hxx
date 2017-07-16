#pragma once

#include "../window.hxx"
#include "../drawable.hxx"
#include "../demo.hxx"
#include "../shader.hxx"

class ScTest: public Drawable {
  public:
    ScTest(Demo const &demo);
    void draw() const;

  private:
    Shader shader;
};
