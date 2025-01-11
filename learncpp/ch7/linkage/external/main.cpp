#include <iostream>

// External linkage allows identifiers to be seen from other translation units.
int g_a{ 2 }; // non-constant globals are external by default (no need to use extern)

extern const int g_b{ 3 }; // const globals can be defined as extern, making them external
extern constexpr int g_c{
  3
}; // constexpr globals can be defined as extern, making them external (but this is pretty useless)

// In order to use external variable from other file you need to forward declare it with extern keyword.
extern int g_x; // this extern is a forward declaration of a variable named g_x that is defined somewhere else
extern const int
  g_y; // this extern is a forward declaration of a const variable named g_y that is defined somewhere else
extern const int g_z;

int main()
{
  std::cout << g_x << ' ' << g_y << ' ' << g_z << '\n'; // prints 2 3 3

  return 0;
}