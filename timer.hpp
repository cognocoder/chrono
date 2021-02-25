
#ifndef _COGNOCODER_CHRONO_TIMER_HPP_
#define _COGNOCODER_CHRONO_TIMER_HPP_

#include <chrono>
#include <cmath>
#include <ctime>
#include <stdexcept>
#include <sstream>

#include "time.hpp"

namespace cognocoder { namespace chrono { class timer; } }

std::ostream& operator<<(std::ostream& os, const cognocoder::chrono::timer& t);

namespace cognocoder {
  namespace chrono {

    class timer {
    public:
      timer(time::nanoseconds interval, int intervals_to_unlock);

      time::nanoseconds wait(time::nanoseconds time);
      void tick(time::nanoseconds ellapsed);

      bool locked() const { return _locked; }
      bool paused() const { return _paused; }

      void pause(bool value) { _paused = value; };

      int violations() const { return _violations; }

      // Means to inspect timer state.
      friend std::ostream& (::operator<<)(std::ostream& os, const timer& t);

    private:
      const time::nanoseconds _interval;
      const int _intervals_to_unlock;

      time::nanoseconds _ellapsed { 0s };
      time::nanoseconds _remaining { 0s };

      int _intervals { 0 };
      int _violations { 0 };

      bool _locked { false };
      bool _paused { false };

      struct timespec _timespec;
    };

  }
}

#endif
