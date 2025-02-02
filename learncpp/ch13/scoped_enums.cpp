#include <iostream>
#include <utility> // for std::to_underlying() (C++23)

// Favor scoped enumerations over unscoped enumerations unless there's a compelling reason to do otherwise.

// Scoped enums are not implicitly converted to integer, enumerators are inside the scope of enum.
enum class Color // scoped enumeration
{
  red, // red is considered part of Color's scope region
  blue,
};

enum class Fruit {
  banana, // banana is considered part of Fruit's scope region
  apple,
};

constexpr auto operator+(Color a) noexcept { return std::to_underlying(a); }

int main()
{
  using enum Fruit; // bring all Fruit enumerators into current scope (C++20)

  Color color{ Color::red }; // note: red is not directly accessible, we have to use Color::red
  Fruit fruit{ banana }; // note: banana is directly accessible because of `using enum` above
  Color pet{ 1 }; // C++17, okay (unlike in unscoped enum, no need to specify a base)
  // std::cout << color << '\n'; // error
  std::cout << +color << '\n'; // a hack to convert to int using overload of unary +

  // or use static_cast<int>(color) prior C++23
  std::cout << std::to_underlying(color) << '\n'; // convert to underlying type, will print 1 (C++23)

  return 0;
}