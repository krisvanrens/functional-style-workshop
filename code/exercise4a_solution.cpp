#include <iostream>
#include <string>
#include <utility>

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

int main() {
  Maybe<std::string> input1{"Functional-style C++"};
  Maybe<std::string> input2;

  std::cout << input1 << ", "
            << input2 << '\n';;
}