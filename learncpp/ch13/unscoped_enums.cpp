#include <cstdint> // for std::int8_t
#include <ios>
#include <iostream>
#include <istream>
#include <limits>
#include <optional>
#include <ostream>
#include <string>
#include <string_view>

/*
Enumerators are implicitly constexpr.
Unnamed enumerations should be avoided.
It's ok to pass enums by value.
Unscoped enumerations will implicitly convert to integral values.
*/

// Unscoped enumeration (enumerated type). Enumerators are in the same scope as the enumeration (global in this case).
// If there are multiple enums with the same names for enumerators, name collision will result (compile error).
// Enumerators are integrals, by default starts with 0, increments by 1.
enum Color {
  // enumerators
  red, // 0
  green, // 1
  blue, // 2
  black, // 3, trailing comma is optional but recommended
};

/*
To avoid polluting the scope it's better to put enums into scoped regions (namespaces, classes or even functions).
It's possible to specify enum's underlying type (base), default is implementation defined (often int). If base is not
explicitly set the compiler gets to pick the underlying type, and it can pick any signed or unsigned type so long as the
value of all enumerators fit in that type. It is only safe to static_cast integral values that fit in the range of the
smallest number of bits that can hold the value of all enumerators:
- enum with values 2, 9, and 12 -> unsigned 4 bit integral (0..15) -> it's only safe to static cast 0..15 to enum;
- enum with values -28, 2, and 6 -> unsigned 6 bit integral (-32..31) -> it's only safe to static cast -32..31.
*/
namespace Feeling {
  enum Feeling : std::int8_t {
    happy,
    tired,
    blue, // Feeling::blue doesn't collide with Color::blue
  };
}

enum Animal {
  // providing values explicitly should generally be avoided
  cat = -3, // values can be negative
  dog, // -2
  pig = dog, // -2
  horse = 5,
  giraffe = 5, // shares same value as horse
  chicken, // 6
};

constexpr std::string_view getColorName(Color color)
{
  switch (color) {
  case black:
    return "black";
  case red:
    return "red";
  case blue:
    return "blue";
  case green:
    return "green";
  default:
    return "???";
  }
}

constexpr std::optional<Color> getColorNameFromString(std::string_view sv)
{
  if (sv == "red") return red;
  if (sv == "green") return green;
  if (sv == "blue") return blue;
  if (sv == "black") return black;
  return {};
}

std::ostream& operator<<(std::ostream& out, Color color)
{
  out << getColorName(color);
  return out;
}

std::istream& operator>>(std::istream& in, Color& color)
{
  std::string s{};
  in >> s;

  std::optional<Color> c{ getColorNameFromString(s) };
  if (c) {
    color = c.value();
    return in;
  }
  in.setstate(std::ios_base::failbit);
  // On an extraction failure, `operator>>` zero-initializes fundamental types.
  // We can do the same here
  color = {};
  return in;
}

int main()
{
  Color apple{ red };
  Color shirt{ green };
  Color cup{ Color::blue };
  std::cout << apple << '\n'; // prints red, because operator<< is overloaded

  Color ball{};
  std::cin >> ball; // operator>> is overloaded
  if (std::cin) {
    std::cout << ball << '\n';
  } else {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max()); // skip line till the end
    std::cout << "Invalid\n";
  }

  // Color socks{ white }; // error, no white

  // becase 0-init gives enum 0 value it's better to have 0 enum as a reasonable default (or something like Unknown)
  Animal a{}; // value-initialization zero-initializes `a` to value 0
  std::cout << a; // prints 0
  std::cout << Animal::cat; // prints -3

  // Color c1{ 2 }; // compile error
  Color c2{ static_cast<Color>(2) }; // static case outside the range of the base - UB
  // Color c3(2); // compile error: cannot direct-initialize with integer
  // Color c4 = 2; // compile error: cannot copy-initialize with integer
  // c1 = 3; // compile error: cannot assign with integer

  Feeling::Feeling f1{ 2 }; // C++17, allowed because base is explicitly defined
  Feeling::Feeling f2{ static_cast<Feeling::Feeling>(2) };
  // Feeling::Feeling f3(2); // compile error: cannot direct-initialize with integer
  // Feeling::Feeling f4 = 2; // compile error: cannot copy-initialize with integer
  // f1 = 3; // compile error: cannot assign with integer

  return 0;
}