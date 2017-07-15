#pragma once

#include "window.hxx"
#include "player.hxx"
#include "drawable.hxx"

class Demo: public Drawable {
  public:
    Demo(Window &window);
    void draw() const;
    Player const &getPlayer() const;

  private:
    Player player;
    Window &window;
};
