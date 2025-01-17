#include <cstddef>
#include <iostream>
#include <limits>
#include <optional>
#include <vector>

template<typename T> void printArray(const std::vector<T>& arr)
{
  for (std::size_t i{ 0 }; i < std::size(arr); ++i) { std::cout << arr[i] << ' '; }
  if (std::size(arr) > 0) { std::cout << '\n'; }
}

template<typename T> T getNumber(T min, T max)
{
  T n{};
  do {
    std::cout << "Enter a number between " << min << " and " << max << ": ";
    std::cin >> n;
    if (!std::cin) { std::cin.clear(); }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  } while (n < min || n > max);
  return n;
}

template<typename T> std::optional<std::size_t> findIndex(const std::vector<T>& arr, T val)
{
  for (std::size_t i{ 0 }; i < std::size(arr); ++i) {
    if (arr[i] == val) { return i; }
  }
  return {};
}

int main()
{
  std::vector arr{ 4.4, 6.6, 7.7, 3.3, 8.8, 2.2, 1.1, 9.9 };
  auto n{ getNumber(1.0, 9.0) };
  printArray(arr);
  auto idx{ findIndex(arr, n) };

  if (idx) {
    std::cout << "The number " << n << " has index " << idx.value() << '\n';
  } else {
    std::cout << "The number " << n << " was not found\n";
  }
  return 0;
}