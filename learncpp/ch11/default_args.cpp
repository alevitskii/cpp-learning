#include <iostream>

// must use `=`
void print(int x = 10, int y = 20, int z = 30) { std::cout << "Values: " << x << " " << y << " " << z << '\n'; }

void print2(int x, int y = 4); // forward declaration

// Redefinition of default args is not allowed, it must be either in forward decl or in definition.
// The default argument must also be declared in the translation unit before it can be used.
// If a function has a forward decl, the best practice is to place default args in forward decl (somewhere in a header
// file). If it doesn't then in the definition.
void print2(int x, int y) // if "int y = 4" compile error: redefinition of default argument
{
  std::cout << "x: " << x << '\n';
  std::cout << "y: " << y << '\n';
}

void print3(std::string_view s) { std::cout << s << '\n'; }

void print3(char c = ' ') { std::cout << c << '\n'; }

// Default values are not part of a function's signature, so these function declarations are differentiated overloads.
void print4(int x); // signature print(int)
void print4(int x, int y = 10); // signature print(int, int)
void print4(int x, double y = 20.5); // signature print(int, double)

int main()
{
  // Arguments with defaults cannot be skipped, explicit arguments must be leftmost, defaults that are often provided
  // explicitly should be leftmost (after explicit ones)
  // If a parameter is given a default argument, all subsequent parameters (to the right) must also be given default
  // arguments.
  print(1, 2, 3); // all explicit arguments
  // Default arguments are inserted by the compiler at the site of the function call.
  print(1, 2); // rightmost argument defaulted
  print(1); // two rightmost arguments defaulted
  print(); // all arguments defaulted

  print3("Hello, world");
  print3('a');
  print3();

  print4(1, 2); // will resolve to print(int, int)
  print4(1, 2.5); // will resolve to print(int, double)
  // print4(1); // error, ambiguous function call

  // Default arguments don't work for functions called through function pointers. It can be used as a workaround for
  // otherwise ambiguous calls

  return 0;
}