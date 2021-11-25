#include <fmt/core.h>
#include <utility>

class Curried {
  // TODO: Implement!
};

bool api(int arg1, int arg2, int arg3) {
  fmt::print("{}, {}, {}\n", arg1, arg2, arg3);
  return true;
}

int main() {
  auto api_curried = Curried{api};
}