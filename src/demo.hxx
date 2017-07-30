#pragma once

#include "window.hxx"
#include "player.hxx"
#include "shaders.hxx"
#include "rocket/sync.h"
#include "verts.hxx"
#include <map>

#define GLM_FORCE_RADIANS
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective

#define V(x) demo.getValue(x)
#define DEMO_N_PREV_FBO 4

class Demo {
  public:
    Demo(Window &window);
    ~Demo();
    Player const &getPlayer() const;
    Shaders const &getShaders() const;
    Verts const &getVerts() const;
    void update();
    sync_track const *getRocketTrack(std::string const &name) const;
    float getValue(sync_track const *track) const;
    float getTime() const;
    float getFftBass() const;
    float getFftTreble() const;
    int getWidth() const;
    int getHeight() const;
    glm::mat4 const &getProjectionMatrix() const;

    static float const BPM;
    static int const RPB;
    static double const ROW_RATE;

  private:
    Window &window;
    Shaders shaders; // Automatically compile shader storage class
    Verts verts; // Automatically load buffer storage class
    Player player;
    sync_device *rocket;

    float time;
    float fftBass;
    float fftTreble;
    sync_track const *fftBassMult;
    sync_track const *fftTrebleMult;

    int const width;
    int const height;

    glm::mat4 projectionMatrix;
};
