#include <iostream>

int main()
{
  [[maybe_unused]] int a; // default initialization, uninitialized in this case (bad)
  a = 5; // copy assignment

  // Traditional initialization forms:
  [[maybe_unused]] int b = 5; // copy-initialization (initial value after equals sign)
  [[maybe_unused]] int c(6); // direct-initialization (initial value in parenthesis)

  // Modern initialization forms (preferred):
  [[maybe_unused]] int d{ 7 }; // direct-list-initialization (initial value in braces)
  [[maybe_unused]] int e{}; // value-initialization (empty braces)

  [[maybe_unused]] int f = { 6 }; // copy-list-initialization of initial value 6 into variable
                                  // height (rarely used)

  // An integer can only hold non-fractional values
  // int g { 4.5 }; // compile error: list init does not allow narrowing
  // conversion of 4.5 to 4

  [[maybe_unused]] int h = 4.5; // compiles: copy-init initializes width with 4
  [[maybe_unused]] int i(4.5); // compiles: direct-init initializes width with 4

  [[maybe_unused]] int j{}; // value-initialization / zero-initialization to value 0

  [[maybe_unused]] int k = 5, l = 6; // copy-initialization
  [[maybe_unused]] int m(7), n(8); // direct-initialization
  [[maybe_unused]] int o{ 9 }, p{ 10 }; // direct-list-initialization
  [[maybe_unused]] int q{}, r{}; // value-initialization

  double pi{ 3.14159 }; // Don't complain if pi is unused
  [[maybe_unused]] double gravity{ 9.8 }; // Don't complain if gravity is unused
  double phi{ 1.61803 }; // Don't complain if phi is unused

  std::cout << pi << '\n';
  std::cout << phi << '\n';
  // The compiler will no longer warn about gravity not being used

  return 0;
}