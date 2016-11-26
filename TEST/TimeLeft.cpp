#include "TimeLeft.h"

TimeLeft::TimeLeft(int remainingTime) : SFMLText{"Time left: " + std::to_string(remainingTime), 0, 0}
{
  remTime = remainingTime;
  start_time = std::chrono::high_resolution_clock::now();
}

void TimeLeft::decreaseTime()
{
  using namespace std::chrono;
  high_resolution_clock::time_point now = high_resolution_clock::now();
  duration<double> time_span = duration_cast<duration<double>>( now - start_time);

  if(time_span.count() > 1)
  {
    start_time = high_resolution_clock::now();
    remTime -= 1;
  }
}
