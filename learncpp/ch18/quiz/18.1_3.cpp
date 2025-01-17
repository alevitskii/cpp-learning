#include <iostream>
#include <iterator>
#include <utility>

// bubble sort

int main()
{
  int array[]{ 6, 3, 2, 9, 7, 1, 5, 4, 8 };
  constexpr int length{ std::size(array) };

  bool swapped{};
  for (int i{ 0 }; i < length - 1; ++i) {
    swapped = false;
    for (int j{ 0 }; j < length - i - 1; ++j) {
      if (array[j] > array[j + 1]) {
        std::swap(array[j], array[j + 1]);
        swapped = true;
      }
    }
    if (!swapped) {
      std::cout << "Early termination on iteration " << i + 1 << '\n';
      break;
    }
  }

  for (int i{ 0 }; i < length; ++i) { std::cout << array[i] << ' '; }
  std::cout << '\n';
  return 0;
}