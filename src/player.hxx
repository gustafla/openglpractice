#pragma once

#include "window.hxx"
#include <string>

#define N_FFT 2048

class Player {
  public:
    Player(std::string const &filename);
    ~Player();
    void play();
    void pause();
    void toggle();

    float getFftBass();
    float getFftTreble();
    float getTime();

  private:
    int channels;
    int sampleSize;
    int sampleRate;
    uint8_t *audioData;
    uint8_t *audioPos;
    int nSamples; // in samples
    int nBytesLeft;  // in bytes
    unsigned lastQueriedTicks;
    unsigned lastCallbackDelay; // in ticks

    static void playerCallback(void *userData, uint8_t *stream, int len);
    int getCurrentSamplePos();

    void computeFft(int16_t *audioData);
    float *fftBassData;
    float *fftTrebleData;

#ifndef BUILD_RPI
    SDL_AudioDeviceID audioDevice;
#endif //BUILD_RPI
};
