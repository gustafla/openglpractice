#pragma once

#include "drawable.hxx"
#include <vector>
#include "demo.hxx"

class Mixer {
  public:
    Mixer();
    void draw(Drawable const &a, Drawable const &b, float r=0.f) const;
  private:
};
