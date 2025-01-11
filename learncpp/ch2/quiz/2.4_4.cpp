#include <iostream>

int doubleNumber(int num) { return num * 2; }

int main() {
  int num{};
  std::cin >> num;
  std::cout << doubleNumber(num) << '\n';
  return 0;
}