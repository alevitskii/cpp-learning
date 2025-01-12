#include "max.h" // import template definition for max<T>(T, T)
#include <iostream>

void foo(); // forward declaration for function foo

/*
If instead of including max.h we put max template declaration `template<typename T> T max(T x, T y);` here
and define a template in max.cpp:
1. the compiler will assume that the function is defined somewhere else when compiling main.cpp;
2. the compiler won't instantiate the template in max.cpp because there will be no usage of it in that file;
3. the linker will fail to find the definitions.
*/

int main()
{
  std::cout << max(3, 5) << '\n';
  foo();

  return 0;
}
