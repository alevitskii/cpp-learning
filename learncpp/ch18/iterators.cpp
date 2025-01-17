#include <algorithm>
#include <array> // includes <iterator>
#include <iostream>

/*
std::begin and std::end for C-style arrays are in <iterator>.
std::begin and std::end for C++ arrays are in respective headers.
*/

int main()
{
  std::array array{ 1, 2, 3 };

  // Use std::begin and std::end to get the begin and end points.
  auto begin{ array.begin() };
  auto end{ std::end(array) };

  // note !=, not <. Not all iterators support <
  for (auto p{ begin }; p != end; ++p) // ++ to move to next element
  {
    std::cout << *p << ' '; // Indirection to get value of current element
  }
  std::cout << '\n';

  // all types that can be used with std::begin() and std::end() (or have member funcs) can be used in range-for
  for (int i : array) { std::cout << i << ' '; }
  std::cout << '\n';

  /*
  Iterators can be left dangling if the elements being iterated over change address or are destroyed - iter becomes
  invalidated. Accessing it is UB. Beware when use std::vector for example.
  Before using a particular algorithm, make sure performance and execution order guarantees work for your particular use
  case.
  */

  std::array arr{ 1, 2, 3, 4 };

  std::for_each(arr.begin(), arr.end(), [](int& x) { x *= 2; });
  for (int i : arr) { std::cout << i << ' '; }
  std::cout << '\n';

  // C++20
  std::ranges::for_each(arr, [](int& x) { x *= 2; });
  for (int i : arr) { std::cout << i << ' '; }
  std::cout << '\n';

  return 0;
}