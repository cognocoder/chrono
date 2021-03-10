
#include "duration.hpp"
#include "time.hpp"
#include "timer.hpp"

#include <chrono>
#include <ctime>
#include <iostream>
#include <vector>

using namespace cognocoder::chrono;

using namespace std::literals::chrono_literals;

int main() {
  std::vector<time::nanoseconds> sleeps { 
    480ms, 480ms, 480ms, 480ms,
    480ms,        980ms, 480ms,
           980ms, 480ms, 480ms,
    480ms, 480ms,        980ms,
    480ms,              1480ms,
    1480ms,              480ms,
    1980ms,
    2480ms,
  };

  struct timespec ts;
  timer default_timer { 500ms, 4 };
  
  std::cout << "  " << default_timer;
  for (auto sleep : sleeps) {
    time::set_timespec(ts, sleep);
    default_timer.tick(measure<>::duration(nanosleep, &ts, nullptr));
    std::cout << default_timer;
  }
  std::cout << std::endl;

  return 0;
}
