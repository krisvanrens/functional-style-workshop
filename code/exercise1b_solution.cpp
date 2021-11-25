#include <chrono>
#include <functional>
#include <thread>
#include <utility>

#include <fmt/core.h>

class AutoTimer final {
  using Clock = std::chrono::steady_clock;

  const Clock::time_point time_start_;

public:
  AutoTimer() noexcept
    : time_start_{Clock::now()} {
  }

  void print(const std::string& message) const {
    fmt::print("Time elapsed since start ({}): {} ms\n",
               message, std::chrono::duration_cast<std::chrono::milliseconds>(Clock::now() - time_start_).count());
  }

  ~AutoTimer() {
    print("end");
  }
};

template<typename Computation>
class Lazy final {
  Computation computation_;

public:
  constexpr Lazy(Computation&& computation) noexcept
    : computation_{std::forward<Computation>(computation)} {
  }

  operator const decltype(computation_()) () const {
    return std::invoke(computation_);
  }
};

static float calculate(int input) noexcept {
  std::this_thread::sleep_for(std::chrono::milliseconds(100));
  return static_cast<float>(input) / 2;
}

int main() {
  int input = 42;

  {
    AutoTimer t;

    const auto& value = Lazy{[&input]{ return calculate(input); }};

    t.print("before first use");

    fmt::print("Value = {:f}\n", value);

    t.print("before second use");

    fmt::print("Value = {:f}\n", value);
  }
}