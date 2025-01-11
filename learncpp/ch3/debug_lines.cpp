#include <iostream>

#define ENABLE_DEBUG // comment out to disable debugging

int getUserInput()
{
  // It's easier to notice debug lines when they are not indented.

  // std::cerr should be used instead of std::cout because it doesn't buffer.
  // std::clog writes to std::cerr by default but can be configured.

  // clang-format off
#ifdef ENABLE_DEBUG
std::cerr << "getUserInput() called\n";
#endif
  // clang-format on
  std::cout << "Enter a number: ";
  int x{};
  std::cin >> x;
  return x;
}

int main()
{
  // clang-format off
#ifdef ENABLE_DEBUG
std::cerr << "main() called\n";
#endif
  // clang-format on
  int x{ getUserInput() };
  std::cout << "You entered: " << x << '\n';

  return 0;
}