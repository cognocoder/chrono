
#include "time.hpp"

#include <ctime>
#include <iostream>
#include <stdexcept>
#include <vector>

using namespace cognocoder::chrono;
using namespace cognocoder::chrono::time;

int main() {
  std::vector<nanoseconds> times { -1s, 0s, 1s, 999999999ns, 1000000000ns,
    nanoseconds::max(), nanoseconds::max() + 1ns };
  struct timespec timespec;

  for (auto time : times) {
    try {
      set_timespec(timespec, time);
      std::cout << "  " << timespec_str(timespec) << std::endl;
    }
    catch (std::runtime_error &e) {
      std::cout << "  " << e.what();
    }
  }

  return 0;
}
