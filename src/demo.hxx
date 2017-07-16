#pragma once

#include "window.hxx"
#include "player.hxx"
#include "shaders.hxx"

class Demo {
  public:
    Demo(Window &window);
    Player const &getPlayer() const;
    Shaders const &getShaders() const;

  private:
    Window &window;
    Shaders shaders; // Automatically compile shader storage class
    Player player;
};
