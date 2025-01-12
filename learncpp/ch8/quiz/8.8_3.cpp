#include <iostream>

int main()
{
  int num{ 5 };

  int outer{ num };
  while (outer > 0) {
    int inner{ 1 };
    while (inner <= outer) {
      std::cout << (num - inner + 1) << ' ';
      ++inner;
    }
    std::cout << '\n';
    --outer;
  }
  return 0;
}