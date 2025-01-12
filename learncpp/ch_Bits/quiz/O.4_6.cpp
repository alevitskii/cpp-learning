#include <iostream>

void printBit(int n, int pow) { std::cout << (n / pow) % 2; }

int main()
{
  std::cout << "Enter a number between 0 and 255: ";
  int num{};
  std::cin >> num;

  printBit(num, 128);
  printBit(num, 64);
  printBit(num, 32);
  printBit(num, 16);
  std::cout << ' ';
  printBit(num, 8);
  printBit(num, 4);
  printBit(num, 2);
  printBit(num, 1);
  std::cout << '\n';

  return 0;
}