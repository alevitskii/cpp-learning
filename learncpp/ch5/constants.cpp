#include <bitset>
#include <format>
#include <iostream>
#include <print>


void printInt(const int x /*const is not needed because x is passed by value*/) { std::cout << x << '\n'; }

// you shouldn't use const when returning by value
const int getValue() { return 5; }

int five() { return 5; }

int main()
{
  std::cout << "Enter your age: ";
  int age{};
  std::cin >> age;

  // const must be initialized when defined
  const int constAge{ age }; // initialize const variable using non-const value
  // this is acceptable but unconventional
  int const constAge2{ age };

  age = 5; // ok: age is non-const, so we can change its value
  //   constAge = 6; // error: constAge is const, so we cannot change its value

  printInt(age);
  std::cout << "##############" << '\n';

  // In general, make variables constant whenever possible
  // Prefer constant variables over object-like macros with substitution text.

  // const and volatile are type qualifiers, there are only two of them in C++

  // integral literals
  std::cout << 5 << '\n'; // 5 (no suffix) is type int (by default)
  std::cout << 5L << '\n'; // 5L is type long (l works too but it may look like 1)
  std::cout << 5u << '\n'; // 5u is type unsigned int

  // C-style string literals are const objects that are created at the start of the program and are guaranteed to exist
  // for the entirety of the program.

  int x{ 012 }; // 0 before the number means this is octal
  int y{ 0xF }; // 0x before the number means this is hexadecimal (0X* works too)
  int z{ 0b1001 }; // (C++14) 0b before the number means this is binary
  // prints 10 15 9 because numbers are output in decimal by default
  std::cout << x << ' ' << y << ' ' << z << '\n';
  std::cout << "##############" << '\n';

  int a{ 12 };
  std::cout << a << '\n'; // decimal (by default)
  std::cout << std::hex << a << '\n'; // hexadecimal
  std::cout << a << '\n'; // now hexadecimal (std::hex is sticky)
  std::cout << std::oct << a << '\n'; // octal
  std::cout << std::dec << a << '\n'; // return to decimal
  std::cout << a << '\n'; // decimal
  std::cout << "##############" << '\n';

  int bin{ 0b1011'0010 }; // assign binary 1011 0010 to the variable
  long value{ 2'132'673'462 }; // much easier to read than 2132673462

  // std::bitset<8> means we want to store 8 bits
  std::bitset<8> bin1{ 0b1100'0101 }; // binary literal for binary 1100 0101
  std::bitset<8> bin2{ 0xC5 }; // hexadecimal literal for binary 1100 0101

  std::cout << bin1 << '\n' << bin2 << '\n';
  std::cout << std::bitset<4>{ 0b1010 } << '\n'; // create a temporary std::bitset and print it

  std::cout << std::format("{:b}\n", 0b1010); // C++20, {:b} formats the argument as binary digits
  std::cout << std::format("{:#b}\n", 0b1010); // C++20, {:#b} formats the argument as 0b-prefixed binary digits

  std::println("{:b} {:#b}", 0b1010, 0b1010); // C++23, format/print two arguments (same as above) and a newline

  // Only const int with constant initializer can be evaluated at compile-time (however, compiler may decide not to).
  // Constexpr must be known at compile-time and can be evaluated at runtime or compile-time and it also works for non
  // ints. Constexpr variables are implicitly const.

  constexpr double gravity{ 9.8 }; // ok: 9.8 is a constant expression
  constexpr int sum{ 4 + 5 }; // ok: 4 + 5 is a constant expression
  constexpr int something{ sum }; // ok: sum is a constant expression

  // constexpr int myAge{ age }; // compile error: age is not a constant expression
  // constexpr int f{ five() }; // compile error: return value of five() is not a constant expression

  return 0;
}