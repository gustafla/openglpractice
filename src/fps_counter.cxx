#include "fps_counter.hxx"
#include <iostream>

FpsCounter::FpsCounter(float printInterval, int sampleSize):
  frameTimeHistory(sampleSize), // Initialize dt history buf
  SAMPLE_SIZE(sampleSize), PRINT_INTERVAL(printInterval),
  lastPrintTime(0.f)
{
}

void FpsCounter::printer(float currentTime) {
  // Only print when it's time for that
  if (currentTime > lastPrintTime + PRINT_INTERVAL) {
    // Calculate average and print a report
    float avg = 0.;
    for (auto const &f: frameTimeHistory) {
      avg += f;
    }
    avg /= static_cast<float>(SAMPLE_SIZE);
    std::cout << "Avg FPS: " << 1./avg << std::endl;
    lastPrintTime = currentTime;
  }
}

void FpsCounter::addFrameTime(float dt) {
  // Tracking a circular buffer for delta time data
  static int i = 0;
  frameTimeHistory[i++ % SAMPLE_SIZE] = dt;
}
