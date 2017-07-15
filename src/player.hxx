#pragma once

#include "window.hxx"
#include "loading_bar.hxx"
#include <string>

#define N_FFT 2048

class Player {
  public:
    Player(std::string const &filename);
    Player(std::string const &filename, Window &window);
    ~Player();
    void play();
    void pause();
    void toggle();

    float getFftBass();
    float getFftTreble();
    float const getTime() const;

  private:
    int channels;
    int sampleSize;
    int sampleRate;
    uint8_t *audioData;
    uint8_t *audioPos;
    int nSamples; // in samples
    int nBytesLeft;  // in bytes
    int samplePos;
    unsigned lastQueriedTicks;
    unsigned lastCallbackDelay; // in ticks

    float *fftBassData;
    float *fftTrebleData;

    static void playerCallback(void *userData, uint8_t *stream, int len);

    int16_t *loadVorbisFile(std::string const &filename,
        LoadingBar *loadingBar=NULL);
    void computeFft(int16_t *audioData, LoadingBar *loadingBar=NULL);

#ifndef BUILD_RPI
    SDL_AudioDeviceID audioDevice;
#endif //BUILD_RPI
};
