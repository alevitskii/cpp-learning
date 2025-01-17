#include <iostream>
#include <ranges> // C++20
#include <string>
#include <vector>

int main()
{
  std::vector<std::string> words{ "peter", "likes", "frozen", "yogurt" };

  /*
  Range-based for loops work with a many array types.
  Don't work with decayed C-style array (range for must know array's length) and enumerations.

  For range-based for loops, prefer to define the element type as:
  - auto when you want to modify copies of the elements;
  - auto& when you want to modify the original elements;
  - const auto& otherwise (when you just need to view the original elements).
  */
  for (const auto& word : words) std::cout << word << ' ';

  // C++20
  for (const auto& word : std::views::reverse(words)) std::cout << word << ' ';

  std::cout << '\n';

  return 0;
}