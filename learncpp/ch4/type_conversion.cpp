#include <iostream>

void print(double x)
{
  // will print 5 (not 5.0) because cout doesn't print .0 by default
  std::cout << x << '\n';
}

void printInt(int x) { std::cout << x << '\n'; }

int main()
{
  // Type conversion uses direct initialization to produce a new value of the target type from a value of a different
  // type. Implicit type conversion (not warned by the compiler)
  print(5);

  printInt(5.0); // implicit type conversion (may be warned by the compiler)
  printInt(static_cast<int>(5.5)); // explicit type conversion

  char ch{ 97 }; // 97 is ASCII code for 'a'
  // print value of variable ch as an int
  std::cout << ch << " has value " << static_cast<int>(ch) << '\n';

  int s{ -1 };
  std::cout << static_cast<unsigned int>(s) << '\n'; // prints 4294967295

  unsigned int u{ 4294967295 }; // largest 32-bit unsigned int
  // unsigned to signed conversion is implementation-defined prior to C++20, well-defined since C++20
  std::cout << static_cast<int>(u) << '\n'; // (C++20) -1

  return 0;
}