#include <iostream>

/*
Variables declared outside of a function are global variables.

Global variables have static duration, they are created when program starts (before main() begins execution) and
destoyed when the program ends.

Variables with static duration -- static variables.

It's useful to have prefix g or g_ for global variables to indicate that it's global and to avoid naming clashes.
It's better to avoid non-constant global variables.
*/

int g_x{}; // global variable g_x, initialized to 0
// static variables are initialized with default value
int g_y; // non-constant global variable g_y, also initialized to 0

// constant global variables must be initialized
const int g_z{ 1 };
constexpr int g_w{ 2 };

// it's better to create global variables inside namespaces
namespace Foo // Foo is defined in the global scope
{
  int g_x{}; // g_x is now inside the Foo namespace, but is still a global variable
}

void doSomething()
{
  // global variables can be seen and used everywhere in the file
  g_x = 3;
}

int main()
{
  doSomething();
  std::cout << g_x << '\n';
  std::cout << Foo::g_x << '\n';

  // global variables can be seen and used everywhere in the file
  g_x = 5;
  std::cout << g_x << '\n';
  std::cout << Foo::g_x << '\n';

  Foo::g_x = 7;
  std::cout << g_x << '\n';
  std::cout << Foo::g_x << '\n';

  return 0;
}
// g_x goes out of scope here
