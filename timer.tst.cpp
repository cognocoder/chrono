
#include "time.hpp"
#include "timer.hpp"

#include <chrono>
#include <ctime>
#include <iostream>
#include <vector>

using namespace cognocoder::chrono;

using namespace std::literals::chrono_literals;

int main() {
  std::vector<time::nanoseconds> sleeps { 700ms,
    300ms, 10ms, 10ms, 10ms, 10ms, 10ms, 10ms };

  struct timespec ts;
  timer default_timer { 100ms, 4 };
  
  std::cout << "  " << default_timer;
  for (auto sleep : sleeps) {
    nanosleep(&ts, nullptr);
    default_timer.tick(sleep);
    time::set_timespec(ts, sleep);
    std::cout << default_timer;
  }
  std::cout << std::endl;

  return 0;
}
