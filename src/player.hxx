#pragma once

#include "window.hxx"
#include "loading_bar.hxx"
#include <string>

#define N_FFT 2048
#define LEN_BUF 2048

class Player {
  public:
    Player(std::string const &filename, Window *window=nullptr);
    ~Player();
    void play();
    void pause();
    void toggle();
    bool const isPlaying() const;

    float const getFftBass() const;
    float const getFftTreble() const;
    float const getTime() const;
    void setTime(float const time);

  private:
    int channels;
    int sampleSize;
    int sampleRate;
    uint8_t *audioData;
    uint8_t *audioPos;
    int nSamples; // in samples
    int nBytesLeft;  // in bytes
    int samplePos;
    unsigned callbackTicks;

    float *fftBassData;
    float *fftTrebleData;

    static void playerCallback(void *userData, uint8_t *stream, int len);

    int16_t *loadVorbisFile(std::string const &filename,
        LoadingBar *loadingBar=nullptr);
    void computeFft(int16_t *audioData, LoadingBar *loadingBar=nullptr);

#ifndef BUILD_RPI
    SDL_AudioDeviceID audioDevice;
#endif //BUILD_RPI
};
