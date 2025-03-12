#include <iostream>
#include <ranges>


/*
A view offers an interface that's very similar to that of a range, so in most cases we can use a view wherever we can
use a range and in the same way. The key difference is that a view doesn't own its elements; it is not responsible for
deleting the elements of its underlying range - that's the range's responsibility. On the other hand, a view must not
outlive its range.

Views are supposed to be cheap to copy, so we pass them by value.
*/

void user(std::ranges::forward_range auto& r)
{
  std::ranges::filter_view v{ r, [](int x) { return x % 2; } }; // view (only) odd numbers in r
  std::cout << "odd numbers: ";
  for (int x : std::ranges::take_view{ v, 3 }) std::cout << x << ' ';
}

void user2(std::ranges::forward_range auto& r)
{
  auto odd = [](int x) { return x % 2; };
  for (int x : r | std::views::filter(odd) | std::views::take(3)) std::cout << x << ' ';
}


int main() {}