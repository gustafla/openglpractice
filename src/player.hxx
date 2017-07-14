#pragma once

#include "window.hxx"
#include <string>

class Player {
  public:
    Player(std::string const &filename);
    ~Player();
    void start();

  private:
    uint8_t *audioData;
    int currentLen;
    uint8_t *audioPos;
    static void playerCallback(void *userData, uint8_t *stream, int len);

#ifndef BUILD_RPI
    SDL_AudioDeviceID audioDevice;
#endif //BUILD_RPI
};
