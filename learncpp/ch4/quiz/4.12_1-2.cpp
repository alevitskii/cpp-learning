#include <iostream>

int charAsInt(char c) { return c; }

int getInt(int c) { return c; }

int main()
{
  std::cout << "Enter a single character: ";
  char c{};
  std::cin >> c;
  std::cout << "You entered '" << c << "', which has ASCII code " << static_cast<int>(c) << ".\n";

  // Other ways to convert (avoid):
  // 1. Create a variable and init with `c`: `int ascii{ c };` (implicit conversion)
  // 2. Pass through a function that does conversion on return: `charAsInt` (implicit conversion)
  // 2. Pass through a function that does conversion in params: `getInt` (implicit conversion)

  return 0;
}