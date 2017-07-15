#include "demo.hxx"

Demo::Demo(Window &window):
  window(window),
  player("music.ogg", window)
{
  player.play();
}

void Demo::draw() const {

}

Player const &Demo::getPlayer() const {
  return player;
}

Shaders const &Demo::getShaders() const {
  return shaders;
}
