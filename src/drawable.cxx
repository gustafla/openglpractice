#include "drawable.hxx"
#include "debug.hxx"

void Drawable::draw() const {
#ifndef BUILD_RELEASE
  die("Drawable::draw()");
#endif
}
