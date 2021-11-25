#include <fmt/core.h>
#include <functional>
#include <tuple>
#include <type_traits>
#include <utility>

// Please note: the implementation below is problematic for use with literal string arguments
//  as strings get converted into character arrays when converted to tuples from variadic
//  template arguments. To circumvent this, string literals must be passed as an indirection.
// This can be done with boost::hana (see: https://stackoverflow.com/questions/58592285/c-storing-raw-character-array-in-tuple).

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

  constexpr Curried(Function function, std::tuple<CapturedArgs...>&& args) noexcept
    : function_{function},
      captured_args_{std::move(args)} {
  }

  template<typename... ExtraArgs>
  decltype(auto) operator()(ExtraArgs&&... args) const {
    auto extra_args = copy_args(std::forward<ExtraArgs>(args)...);
    auto combined_args = std::tuple_cat(captured_args_, std::move(extra_args));

    if constexpr (std::is_invocable_v<Function, CapturedArgs..., ExtraArgs...>) {
      return std::apply(function_, combined_args);
    } else {
      return Curried<Function, CapturedArgs..., ExtraArgs...>{function_, std::move(combined_args)};
    }
  }
};

bool api(int arg1, int arg2, int arg3) {
  fmt::print("{}, {}, {}\n", arg1, arg2, arg3);
  return true;
}

int main() {
  auto api_curried = Curried{api};

  [[maybe_unused]] auto result0 = api_curried(17, 42, 56);

  auto request1 = api_curried(17);
  auto request2 = request1(42);

  [[maybe_unused]] auto result1 = request1(42, 56);
  [[maybe_unused]] auto result2 = request2(56);
}