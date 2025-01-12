#include <iostream>

int main()
{
  int x{ 10 };
  int y{ 4 };

  // Casts return a temporary object, just like a function that returns by value.

  // C-style casts can perform everything that named casts can (static_cast, const_cast, dynamic_cast, reinterpret_cast)
  // The only thing named casts can't do that C-style can is conversion of derived class object to base type that is
  // inaccessible (e.g. if derived is inhereted privatly)

  // C-style casts should be avoided
  double d{ (double)x / y }; // convert x to a double so we get floating point division
  std::cout << d << '\n'; // prints 2.5

  // static_cast is ok to use, it also checks if convertions can happen.
  // int x{ static_cast<int>("Hello") }; // invalid: will produce compilation error

  // static_cast `x` to a double so we get floating point division
  double d2{ static_cast<double>(x) / y };
  std::cout << d2 << '\n'; // prints 2.5

  // static_cast can be used for narrowing conversions
  int i{ 100 };
  i = static_cast<int>(i / 2.5);

  return 0;
}