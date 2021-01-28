
#ifndef _COGNOCODER_CHRONO_TIME_HPP_
#define _COGNOCODER_CHRONO_TIME_HPP_

#include <chrono>
#include <ctime>
#include <sstream>
#include <string>
#include <stdexcept>

namespace cognocoder {
  namespace chrono {

    using namespace std::literals::chrono_literals;

    namespace time {

      using nanoseconds = std::chrono::nanoseconds;

      void validate_non_negative_time(nanoseconds time);

      // Constant given by POSIX.
      constexpr long timespec_nsec_max_value { 999999999 };

      std::string timespec_str(const struct timespec& ts);

      // Set a valid timespec. Throw std::runtime_error otherwise.
      // If the time value is invalid, ts reference is left untouched. 
      void set_timespec(struct timespec& ts, nanoseconds time);

    }

  }
}

#endif
