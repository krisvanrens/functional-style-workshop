#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

template<typename T>
class Maybe {
  bool is_valid_ = false;
  T value_;

public:
  Maybe() = default;

  explicit Maybe(T&& value)
    : is_valid_{true},
      value_{std::move(value)} {
  }

  bool is_just() const {
    return is_valid_;
  }

  bool is_nothing() const {
    return !is_valid_;
  }

  const T& value() const {
    if (!is_valid_) {
      throw "Trying to get value of NOTHING";
    }

    return value_;
  }
};

template<typename T>
std::ostream& operator<<(std::ostream& os, Maybe<T> m) {
  if (m.is_just()) {
    return os << "Just(" << m.value() << ")";
  } else {
    return os << "Nothing";
  }
}

std::function<std::string(std::string)> to_upper = [](std::string x) {
  std::transform(x.begin(), x.end(), x.begin(), ::toupper);
  return x;
};

std::function<int(std::string)> length = [](std::string x) {
  return x.length();
};

std::function<bool(int)> is_even = [](int x) {
  return (x % 2) == 0;
};

std::function<std::string(bool)> to_string = [](bool x) {
  return (x ? "true" : "false");
};

template<typename A, typename B>
Maybe<B> map(std::function<B(A)> f, Maybe<A> x) {
  return (x.is_just() ? Maybe<B>(f(x.value())) // Just(f(x)).
                      : Maybe<B>{});           // Nothing.
}

int main() {
  Maybe<std::string> input1{"Functional-style C++"};
  Maybe<std::string> input2;

  std::cout << input1 << ", "
            << input2 << '\n';

  std::cout << map(to_upper, input1) << ", "
            << map(to_upper, input2) << '\n';

  std::cout << map(length, input1) << ", "
            << map(length, input2) << '\n';

  std::cout << map(is_even, map(length, input1)) << ", "
            << map(is_even, map(length, input2)) << '\n';

  std::cout << map(to_string, map(is_even, map(length, input1))) << ", "
            << map(to_string, map(is_even, map(length, input2))) << '\n';
}