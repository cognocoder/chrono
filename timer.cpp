
#include "timer.hpp"

using namespace cognocoder::chrono;

timer::timer(cognocoder::chrono::time::nanoseconds interval,
    int intervals_to_unlock)
  : _interval { interval }, 
    _intervals_to_unlock { intervals_to_unlock },
    _remaining { interval } {
  time::set_timespec(_timespec, interval);

  if (intervals_to_unlock >= 0) return;

  std::stringstream what;
  what << "Error: intervals_to_unlock { " << intervals_to_unlock << " } "
    << " must be >= 0." << std::endl;

  throw std::runtime_error { what.str() };
}

void timer::wait(cognocoder::chrono::time::nanoseconds time) {
  time::validate_non_negative_time(time);

  time::set_timespec(_timespec, time);
  _ellapsed += time;
}

void timer::tick(cognocoder::chrono::time::nanoseconds ellapsed) {
  time::validate_non_negative_time(ellapsed);

  _remaining = _interval - ellapsed;
  _ellapsed += ellapsed;

  // Wait remaining time in the interval.
  if (_remaining >= 0s) {
    _violations = 0;
    _intervals++;
  }
  // wait remaining time in the interval after violated ones.
  else {
    _violations = ellapsed / _interval;
    _remaining = ellapsed % _interval;
    _intervals += _violations + 1;
  }

  wait(_remaining);

  // Don't tick and change further the timer state if it is paused.
  if (paused()) return;

  // This is the always unlocked setup.
  if (_intervals_to_unlock == 0) {
    _locked = false;
    return;
  }

  // Always lock after a unlocked tick.
  if (!_locked) {
    _locked = true;
    _intervals = _violations;
  }

  /*
  ** Intervals to unlock reached: unlock timer.
  **
  ** Note: _intervals may be much greater than _intervals_to_unlock, due to at 
  ** least one interval set violation.
  */
  if (_intervals >= _intervals_to_unlock) {
    _intervals = 0;
    _locked = false;
    return;
  }

  // The timer remains locked.
}

std::ostream& operator<<(std::ostream& os, const timer& t) {
  for (int i { 0 }; i < t._violations; i++)
    os << "#";
  os << (t._locked ? "·" : "*");
  return os << std::flush;
}
