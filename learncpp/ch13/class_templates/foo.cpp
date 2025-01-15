#include "pair.h"
#include <iostream>

void foo()
{
  Pair<int> p1{ 1, 2 };
  std::cout << max(p1) << " is larger\n";
}