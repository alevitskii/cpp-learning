#include <algorithm>
#include <cassert>
#include <cstddef>
#include <ios>
#include <iostream>
#include <iterator>
#include <limits>
#include <string>
#include <string_view>
#include <type_traits>
#include <utility>
#include <vector>

template<typename T> std::pair<std::size_t, std::size_t> findMinMax(const std::vector<T>& v)
{
  std::size_t min{ 0 };
  std::size_t max{ 0 };
  for (std::size_t i{ 1 }; i < std::size(v); ++i) {
    if (v[i] > v[max]) { max = i; }
    if (v[i] < v[min]) { min = i; }
  }
  return { min, max };
}

template<typename T> void print(const T& arr)
{
  using value_type = std::remove_reference_t<decltype(arr)>::value_type;
  std::cout << "With array ( ";
  std::copy(arr.begin(), arr.end(), std::ostream_iterator<value_type>(std::cout, ", "));
  std::cout << " ):\n";
}

template<typename T> void printArray(const std::vector<T>& v)
{
  bool comma{ false };
  std::cout << "With array ( ";
  for (const auto& e : v) {
    if (comma) std::cout << ", ";

    std::cout << e;
    comma = true;
  }
  std::cout << " ):\n";
}

std::vector<int> getNumbers()
{
  std::cout << "Enter numbers to add (use -1 to stop): ";
  int num{};
  std::vector<int> v{};
  while (true) {
    std::cin >> num;
    if (!std::cin) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      continue;
    }
    if (num == -1) {
      if (v.empty()) {
        std::cout << "Enter at least one number: ";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        continue;
      }
      return v;
    }
    v.push_back(num);
  }
}

int main()
{
  std::vector v1{ 3, 8, 2, 5, 7, 8, 3 };
  std::vector v2{ 5.5, 2.7, 3.3, 7.6, 1.2, 8.8, 6.6 };

  printArray(v1);
  auto m1{ findMinMax(v1) };
  std::cout << "The min element has index " << m1.first << " and value " << v1[m1.first] << '\n';
  std::cout << "The max element has index " << m1.second << " and value " << v1[m1.second] << '\n';

  printArray(v2);
  auto m2{ findMinMax(v2) };
  std::cout << "The min element has index " << m2.first << " and value " << v2[m2.first] << '\n';
  std::cout << "The max element has index " << m2.second << " and value " << v2[m2.second] << '\n';

  std::vector v3{ getNumbers() };
  printArray(v3);
  auto m3{ findMinMax(v3) };
  std::cout << "The min element has index " << m3.first << " and value " << v3[m3.first] << '\n';
  std::cout << "The max element has index " << m3.second << " and value " << v3[m3.second] << '\n';

  return 0;
}