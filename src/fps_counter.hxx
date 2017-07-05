#include <SDL2/SDL.h>
#include <vector>

// FpsCounter keeps a constant size log of deltatimes and handles FPS report
// printing timing
class FpsCounter {
  public:
    FpsCounter(float printInterval, int sampleSize);
    void printer(float currentTime);
    void addDeltaTime(float dt);

  private:
    std::vector<float> deltaTimeHistory;
    float lastPrintTime;
    int const SAMPLE_SIZE;
    float const PRINT_INTERVAL;
};
