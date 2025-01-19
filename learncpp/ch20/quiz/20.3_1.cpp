#include <iostream>

int factorial(int x)
{
  if (x < 2) return x;
  return x * factorial(x - 1);
}

int sumDigits(int num)
{
  if (num < 10) return num;
  return num % 10 + sumDigits(num / 10);
}

void printBits(unsigned int num)
{
  if (num <= 0) return;
  printBits(num / 2);
  std::cout << num % 2;
}

int main()
{
  for (int count{ 0 }; count < 7; ++count) std::cout << factorial(count) << '\n';

  std::cout << sumDigits(93427) << '\n';

  printBits(static_cast<unsigned int>(148));
  std::cout << '\n';
  printBits(static_cast<unsigned int>(-148));

  return 0;
}