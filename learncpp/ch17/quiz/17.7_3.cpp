#include <iostream>
#include <limits>

constexpr int perfect[]{ 0, 1, 4, 9 };

int main()
{
  int n{};
  while (true) {
    std::cout << "Enter a single digit integer, or -1 to quit: ";
    std::cin >> n;
    if (!std::cin) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      continue;
    }
    if (n == -1) { break; }
    int found{ false };
    for (const auto s : perfect) {
      if (n == s) { found = true; }
    }
    std::cout << n << " is " << (found ? "" : "not ") << "a perfect square.\n";
  }
  return 0;
}