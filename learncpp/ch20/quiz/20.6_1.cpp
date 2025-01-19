#include <algorithm>
#include <iostream>
#include <string_view>

struct Student
{
  std::string_view name{};
  int points{};
};

int main()
{
  std::array<Student, 8> arr{ { { "Albert", 3 },
    { "Ben", 5 },
    { "Christine", 2 },
    { "Dan", 8 }, // Dan has the most points (8).
    { "Enchilada", 4 },
    { "Francis", 1 },
    { "Greg", 3 },
    { "Hagrid", 5 } } };

  const auto best{ std::ranges::max_element(
    arr, [](const auto& s1, const auto& s2) { return s1.points < s2.points; }) };
  if (best) { std::cout << best->name << " is the best student\n"; }
  return 0;
}