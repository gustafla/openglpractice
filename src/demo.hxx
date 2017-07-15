#pragma once

#include "window.hxx"
#include "player.hxx"
#include "drawable.hxx"
#include "shaders.hxx"

class Demo: public Drawable {
  public:
    Demo(Window &window);
    void draw() const;
    Player const &getPlayer() const;
    Shaders const &getShaders() const;

  private:
    Window &window;
    Shaders shaders; // Automatically compile shader storage class
    Player player;
};
