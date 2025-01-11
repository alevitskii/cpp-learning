#include "io.h"
#include <iostream>

int readNumber() {
  std::cout << "Enter an integer number: ";
  int x{};
  std::cin >> x;
  return x;
}

void writeAnswer(int n) { std::cout << "The answer is " << n << '\n'; }
