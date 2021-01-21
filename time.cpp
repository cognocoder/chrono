
#include "time.hpp"

using namespace cognocoder::chrono;
using namespace cognocoder::chrono::time;

void cognocoder::chrono::time::validate_non_negative_time(
    cognocoder::chrono::time::nanoseconds time) {
  if (time >= 0s) 
    return;

  std::ostringstream what;
  what << "Error: invalid argument negative time " 
    << "{ " << time.count() << " ns }." << std::endl;

  throw std::runtime_error { what.str() };
}

std::string cognocoder::chrono::time::timespec_str(const struct timespec& ts) {
  std::ostringstream oss;
  oss << "timespec { sec: " << ts.tv_sec << ", nsec: " << ts.tv_nsec << " }.";
  return oss.str();
}

void cognocoder::chrono::time::set_timespec(
    struct timespec& ts, cognocoder::chrono::time::nanoseconds time) {
  validate_non_negative_time(time);

  auto sec { time / 1s };
  auto nsec { (time % 1s).count() };

  if (sec >= 0 && nsec >= 0 && nsec <= timespec_nsec_max_value) {
    ts.tv_sec = sec;
    ts.tv_nsec = nsec;
    return;
  }

  struct timespec invalid;
  invalid.tv_sec = sec;
  invalid.tv_nsec = nsec;

  std::ostringstream what;
  what << "Error: invalid argument " << timespec_str(invalid) << std::endl;

  throw std::runtime_error { what.str() };
}
