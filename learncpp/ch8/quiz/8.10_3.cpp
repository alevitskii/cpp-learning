#include <iostream>

void fizzbuzz2(int num)
{
  for (int i{ 1 }; i <= num; ++i) {
    bool printed{ false };
    if (i % 3 == 0) {
      std::cout << "fizz";
      printed = true;
    }
    if (i % 5 == 0) {
      std::cout << "buzz";
      printed = true;
    }
    if (i % 7 == 0) {
      std::cout << "pop";
      printed = true;
    }
    if (!printed) std::cout << i;
    std::cout << '\n';
  }
}

void fizzbuzz(int num)
{
  for (int i{ 1 }; i <= num; ++i) {
    int rem3{ i % 3 };
    int rem5{ i % 5 };
    int rem7{ i % 7 };
    if (rem3 && rem5 && rem7) { std::cout << i; }
    if (!rem3) { std::cout << "fizz"; }
    if (!rem5) { std::cout << "buzz"; }
    if (!rem7) { std::cout << "pop"; }
    std::cout << '\n';
  }
}

int main()
{
  fizzbuzz(150);
  return 0;
}