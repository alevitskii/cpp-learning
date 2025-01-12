#include <iostream>

int solution2()
{
  int outer{ 1 };
  while (outer <= 5) {
    int inner{ 5 };
    while (inner >= 1) {
      if (inner <= outer)
        std::cout << inner << ' ';
      else
        std::cout << "  ";
      --inner;
    }
    std::cout << '\n';
    ++outer;
  }
  return 0;
}

int main()
{
  int num{ 5 };

  int outer{ 1 };
  while (outer <= num) {
    int inner{ 1 };
    while (inner <= (num - outer)) {
      std::cout << "  ";
      ++inner;
    }
    while (inner <= num) {
      std::cout << (num - inner + 1) << ' ';
      ++inner;
    }
    std::cout << '\n';
    ++outer;
  }
  return 0;
}