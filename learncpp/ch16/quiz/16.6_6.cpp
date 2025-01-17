#include <cassert>
#include <iostream>
#include <string_view>
#include <vector>

void fizzbuzz(int n, const std::vector<int>& divisors, const std::vector<std::string_view>& words)
{
  // would be better to use std::array, constexpr and static_assert
  assert(std::size(divisors) == std::size(words) && "fizzbuzz: array sizes don't match");
  for (int i{ 1 }; i <= n; ++i) {
    bool printed{ false };
    for (std::size_t j{ 0 }; j < divisors.size(); ++j) {
      if (i % divisors[j]) {
        std::cout << words[j];
        printed = true;
      }
    }
    if (!printed) { std::cout << i; }
    std::cout << '\n';
  }
}

int main()
{
  using namespace std::string_view_literals;

  std::vector divisors{ 3, 5, 7, 11, 13, 17, 19 };
  std::vector words{ "fizz"sv, "buzz"sv, "pop"sv, "bang"sv, "jazz"sv, "pow"sv, "boom"sv };
  fizzbuzz(150, divisors, words);

  return 0;
}