#include <fmt/core.h>
#include <tuple>
#include <utility>

template<typename Function, typename... CapturedArgs>
class Curried {
  Function function_;
  std::tuple<CapturedArgs...> captured_args_;

  template<typename... Args>
  static auto copy_args(Args&&... args) {
    return std::make_tuple(std::forward<Args>(args)...);
  }

public:
  constexpr Curried(Function function, CapturedArgs... args) noexcept
    : function_{function},
      captured_args_{copy_args(std::move(args)...)} {
  }
};

bool api(int arg1, int arg2, int arg3) {
  fmt::print("{}, {}, {}\n", arg1, arg2, arg3);
  return true;
}

int main() {
  auto api_curried = Curried{api};
}