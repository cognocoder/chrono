
#include "timer.hpp"

using namespace cognocoder::chrono;

timer::timer(cognocoder::chrono::time::nanoseconds interval,
    int intervals_locked)
  : _interval { interval }, 
    _intervals_locked { intervals_locked },
    _remaining { interval } {
  time::set_timespec(_timespec, interval);

  if (intervals_locked >= 0) return;

  std::stringstream what;
  what << "Error: intervals_locked { " << intervals_locked << " } "
    << " must be >= 0." << std::endl;

  throw std::runtime_error { what.str() };
}

cognocoder::chrono::time::nanoseconds timer::wait(cognocoder::chrono::time::nanoseconds time) {
  time::validate_non_negative_time(time);

  time::set_timespec(_timespec, time);
  nanosleep(&_timespec, nullptr);

  return time;
}

void timer::pause(bool value) {
  _paused = value;
  if (!_paused && _intervals >= _intervals_locked)
    _reset();
}

void timer::_reset() {
  _intervals = 0;
  _locked = false;
}

void timer::tick(cognocoder::chrono::time::nanoseconds ellapsed) {
  time::validate_non_negative_time(ellapsed);

  _locked = true;

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
    _remaining = _interval - ellapsed % _interval;
    _intervals += _violations + 1;
  }

  // If unpaused, only wait if inside cycle time window.
  if (paused() || _intervals <= _intervals_locked + 1 || !_intervals_locked)
    _ellapsed += wait(_remaining);

  // This is the always unlocked setup.
  if (!_intervals_locked) {
    _locked = false;
    return;
  }

  /*
  ** Intervals to unlock reached: unlock timer.
  **
  ** Note: _intervals may be much greater than _intervals_locked, due to at 
  ** least one interval set violation.
  */
  if (!paused() && _intervals > _intervals_locked)
    _reset();

  // The timer remains locked.
}

std::ostream& operator<<(std::ostream& os, const timer& t) {
  for (int i { 0 }; i < t._violations; i++)
    os << " ";
  if (t._locked)
    os << t._intervals;
  else
    os << "*";
  return os << std::flush;
}
