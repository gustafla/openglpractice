#include "player.hxx"
#include "stb_vorbis.h"
#include "debug.hxx"
#include "kissfft/kiss_fft.h"
#include <iostream>
#include <limits>
#include <cmath>

Player::Player(std::string const &filename, Window *window):
  callbackTicks(SDL_GetTicks()), samplePos(0)
{
  LoadingBar *loadingBar = nullptr;
  if (window != nullptr) {
    loadingBar = new LoadingBar(*window);
    loadingBar->setState(0.1);
  }

  int16_t *buffer = loadVorbisFile(filename, loadingBar);

  // Compute FFT
  computeFft(buffer, loadingBar);

  // Print info
  msg("Music: " + std::to_string(((sampleSize*nSamples)/1024.f)/1024.f) + "MB");
  msg("FFT: "
      + std::to_string(((sizeof(float)*(nSamples/N_FFT)*2)/1024.f)/1024.f)
      + "MB");

  if (loadingBar != nullptr) {
    delete loadingBar;
  }
}

Player::~Player() {
#ifdef BUILD_RPI
  SDL_CloseAudio();
#else
  SDL_CloseAudioDevice(audioDevice);
#endif
  delete[] audioData;
  delete[] fftBassData;
  delete[] fftTrebleData;
}

void Player::play() {
#ifdef BUILD_RPI
  SDL_PauseAudio(0);
#else
  SDL_PauseAudioDevice(audioDevice, 0);
#endif
}

void Player::pause() {
#ifdef BUILD_RPI
  SDL_PauseAudio(1);
#else
  SDL_PauseAudioDevice(audioDevice, 1);
#endif
}

void Player::toggle() {
#ifdef BUILD_RPI
  switch (SDL_GetAudioStatus()) {
#else
  switch (SDL_GetAudioDeviceStatus(audioDevice)) {
#endif
    default:
    case SDL_AUDIO_PAUSED:
    case SDL_AUDIO_STOPPED: play(); break;
    case SDL_AUDIO_PLAYING: pause(); break;
  }
}

bool const Player::isPlaying() const {
#ifdef BUILD_RPI
  return (SDL_GetAudioStatus() == SDL_AUDIO_PLAYING);
#else
  return (SDL_GetAudioDeviceStatus(audioDevice) == SDL_AUDIO_PLAYING);
#endif
}

void Player::playerCallback(void *userData, uint8_t *stream, int len) {
  Player *player = (Player*)userData;

  // Prep with silence (copying doesn't always happen)
  SDL_memset(stream, 0, len);

  // Don't play if empty
  if (player->nBytesLeft == 0) {
    player->pause();
    return;
  }

  // Limit reading to buffer bounds
  len = (len > player->nBytesLeft ? player->nBytesLeft : len);

  // Copy audio buffer to player
  SDL_memcpy(stream, player->audioPos, len);

  // Move to next block
  player->audioPos += len;

  // Keep track of data left in the buffer
  player->nBytesLeft -= len;

  // Update pos
  player->samplePos = player->nSamples - player->nBytesLeft
    / player->sampleSize;

  // Get time
  player->callbackTicks = SDL_GetTicks();
}

float const Player::getFftBass() const {
  return fftBassData[samplePos/N_FFT];
}

float const Player::getFftTreble() const {
  return fftTrebleData[samplePos/N_FFT];
}

void Player::computeFft(int16_t *audioData, LoadingBar *loadingBar) {
  fftBassData = new float[nSamples/N_FFT]; // Number of samples in music divided by 
  fftTrebleData = new float[nSamples/N_FFT]; // Number of samples in music divided by 
  // fft frame size

  kiss_fft_cfg cfg = kiss_fft_alloc(N_FFT, 0, nullptr, nullptr);

  kiss_fft_cpx in[N_FFT];
  kiss_fft_cpx out[N_FFT];
  for (int i=0; i<(nSamples/N_FFT)-1; i++) { // i is FFT frame
    for (int s=0; s<N_FFT; s++) { // s is sample within frame
      int16_t sample = audioData[i*N_FFT*channels + s*channels]; // Get left channel
      in[s].r = in[s].i = static_cast<float>(sample)
        / (std::numeric_limits<int16_t>::max()-1);
    }

    kiss_fft(cfg, in, out);

    int const BASS_RANGE = 8;
    float avgBass = 0.f, avgTreble=0.f;
    for (int b=0; b<N_FFT/BASS_RANGE; b++) { // b is output bin
      avgBass += out[b].r;
    }
    fftBassData[i] = avgBass / (N_FFT/BASS_RANGE);
    for (int b=N_FFT/BASS_RANGE; b<N_FFT; b++) {
      avgTreble += out[b].r;
    }
    fftTrebleData[i] = avgTreble / (N_FFT-(N_FFT/BASS_RANGE));

    if (loadingBar != nullptr && i%100 == 0) {
      float state = 0.5 + (0.5f * (i/static_cast<float>(nSamples/N_FFT)));
      loadingBar->setState(state);
    }
  }

  free(cfg);
}

int16_t *Player::loadVorbisFile(std::string const &filename,
    LoadingBar *loadingBar) {
  // Load a vorbis file
  int16_t *buffer;
  nSamples = stb_vorbis_decode_filename(filename.c_str(), &channels,
      &sampleRate, &buffer);

  if (loadingBar != nullptr) {
    loadingBar->setState(0.4);
  }

  // Initialize an SDL audio device
  SDL_AudioSpec want, have;

  want.freq = sampleRate;
  want.format = AUDIO_S16LSB;
  want.channels = channels;
  want.samples = LEN_BUF;
  want.callback = playerCallback;
  want.userdata = (void*)this;

#ifdef BUILD_RPI
  if(SDL_OpenAudio(&want, nullptr) < 0) {
    die("Failed to get required audio format!");
  }
#else
  audioDevice = SDL_OpenAudioDevice(nullptr, 0, &want, &have,
      SDL_AUDIO_ALLOW_FORMAT_CHANGE);

  if (want.format != have.format) {
    die("Failed to get required audio format!");
  }
#endif //BUILD_RPI

  // Prep player class members to play from previously loaded audio buffer
  sampleSize = sizeof(int16_t) * channels;
  nBytesLeft = nSamples * sampleSize;
  audioPos = audioData = (uint8_t*)buffer;

  if (loadingBar != nullptr) {
    loadingBar->setState(0.5);
  }

  return buffer;
}

float const Player::getTime() const {
  float extra = static_cast<float>(SDL_GetTicks() - callbackTicks) / 1000.f;
  return static_cast<float>(samplePos) / static_cast<float>(sampleRate)
    + std::min(extra,
        static_cast<float>(LEN_BUF)/static_cast<float>(sampleRate));
}

void Player::setTime(float const time) {
  int offsetSamples = sampleRate*time;
  int offsetBytes = std::min(offsetSamples*sampleSize, nSamples*sampleSize);
  audioPos = audioData + offsetBytes;
  nBytesLeft = nSamples*sampleSize - offsetBytes;
}
