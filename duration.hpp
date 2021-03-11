
#ifndef _COGNOCODER_CHRONO_DURATION_HPP_
#define _COGNOCODER_CHRONO_DURATION_HPP_

#include <chrono>
#include <functional>

namespace cognocoder {
  namespace chrono {

    // Under creative commons by Nikos Athanasiou and Howard Hinnant.
    template<typename T = std::chrono::nanoseconds>
    struct measure
    {
      template<typename F, typename ...Args>
      static auto duration(F&& fn, Args&&... args)
      {
        using namespace std;
        using namespace std::chrono;

        auto start = steady_clock::now();
        invoke(forward<decltype(fn)>(fn), forward<Args>(args)...);
        return duration_cast<T>(steady_clock::now() - start);
      }
    };

  }
}

#endif
