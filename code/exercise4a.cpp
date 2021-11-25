#include <functional>
#include <iostream>
#include <string>
#include <utility>

template<typename T>
class Maybe {
  // TODO: Implement.
};

template<typename T>
std::ostream& operator<<(std::ostream& os, Maybe<T> m) {
  // TODO: Implement.
}

int main() {
  Maybe<std::string> input1{"Functional-style C++"};
  Maybe<std::string> input2;

  std::cout << input1 << ", "
            << input2 << '\n';
}