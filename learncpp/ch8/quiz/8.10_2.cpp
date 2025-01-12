#include <iostream>

int sumTo(int value)
{
  int sum{};
  for (int i{ 1 }; i <= value; ++i) sum += i;
  return sum;
}

int main()
{
  std::cout << sumTo(5) << ' ';
  return 0;
}