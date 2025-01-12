/*
Functions are differentiated by:
1. number of parameters;
2. type of parameters (excluding typedefs/aliases, const qualifier of value params. Including ellipsis)
Not differentiated by return type.

Member functions are also diffed by:
1. function const and volatile qualifiers;
2. ref-qualifier.

Function's type signature:
1. function name;
2. number of parameters;
3. parameters type;
4. function-level qualifiers.

If a function is not properly diffed, the compiler will issue an error.

Overload resolutions steps:
1. the complier tries to find exact match:
1.1. without trivial conversions (that modify types but don't modify values - lvalue to rvalue, non-const to const
qualifier e.g., non-ref to ref);
1.2. with trivial conversion.
2. with numeric promotions;
3. with numeric conversions;
4. user-defined conversions (defined in user types). If needed after user-defined conversion compiler will convert
further (e.g. X -> char -> int if there is f(int)). The constructor of a class also acts as a user-defined conversion
from other types to that class type, it can also be used;
5. matching conversions that use ellipsis;
6. issue a compiler error.

Ambiguous match occures when there is more than 1 match in the same step.
To resolve ambiguity we may:
- modify the function signature;
- use static_cast;
- use literal suffix.
*/

#include <iostream>

void print(char, int) { std::cout << 'a' << '\n'; }

void print(char, double) { std::cout << 'b' << '\n'; }

void print(char, float) { std::cout << 'c' << '\n'; }

void printInt(int x) { std::cout << x << '\n'; }

void printInt(char) = delete; // calls to this function will halt compilation

// This function template will take precedence for arguments of other types.
// Since this function template is deleted, calls to it will halt compilation.
// This is the way to forbid all except defined exactly.
// template<typename T> void printInt(T x) = delete;

int main()
{
  // 'a' is promoted in print(char, int), in other cases it's converted. So char, int is the best match
  print('x', 'a');

  printInt(97); // okay

  // =delete tells the compiler that a version of a function is forbidden, not that it doesn't exist.
  // Deleted functions participate in every step of function overload resolution.
  // If a deleted function is selected, then a compilation error results.
  // printInt('a'); // compile error: function deleted

  // this one issues ambiguous match, despite the fact that `char` one is deleted
  // printInt(5.0); // compile error: ambiguous match

  return 0;
}