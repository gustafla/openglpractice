#include "player.hxx"
#include "stb_vorbis.h"
#include <iostream>

Player::Player(std::string const &filename) {
  // Load a vorbis file
  int channels, len, sampleRate;
  int16_t *buffer;
  len = stb_vorbis_decode_filename(filename.c_str(), &channels, &sampleRate, 
      &buffer);

  // Initialize an SDL audio device
  SDL_AudioSpec want, have;

  want.freq = sampleRate;
  want.format = AUDIO_S16LSB;
  want.channels = channels;
  want.samples = 4096;
  want.callback = playerCallback;
  want.userdata = (void*)this;

  audioDevice = SDL_OpenAudioDevice(NULL, 0, &want, &have,
      SDL_AUDIO_ALLOW_FORMAT_CHANGE);

  if (want.format != have.format) {
    std::cout << "Player failed to get required audio format!" << std::endl;
  }

  // Prep player class members to play from previously loaded audio buffer
  currentLen = len * sizeof(uint16_t) * channels;
  audioPos = audioData = (uint8_t*)buffer;
}

Player::~Player() {
  delete[] audioData;
}

void Player::start() {
  SDL_PauseAudioDevice(audioDevice, 0);
}

void Player::playerCallback(void *userData, uint8_t *stream, int len) {
  Player *player = (Player*)userData;

  // Prep with silence (copying doesn't always happen)
  SDL_memset(stream, 0, len);

  // Don't play if empty
  if (player->currentLen == 0) {
    return;
  }

  // Limit reading to buffer bounds
  len = (len > player->currentLen ? player->currentLen : len);

  // Copy audio buffer to player
  SDL_memcpy(stream, player->audioPos, len);

  // Move to next block
  player->audioPos += len;

  // Keep track of data left in the buffer
  player->currentLen -= len;
}
