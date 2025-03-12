#include <string>
#include <type_traits>


template<typename T> constexpr T viscosity = 0.4;

template<typename T, typename T2> constexpr bool Assignable = std::is_assignable<T&, T2>::value;

template<typename T> void testing()
{
  static_assert(Assignable<T&, double>, "can't assign a double to a T");
  static_assert(Assignable<T&, std::string>, "can't assign a string to a T");
}

int main() { auto vis2 = 2 * viscosity<double>; }
