#include "pi.h" // will include a copy of pi() here
#include <iostream>

double circumference(double radius); // forward declaration

int main()
{
  std::cout << pi() << '\n';
  std::cout << constants::pi << '\n';
  std::cout << circumference(2.0) << '\n';

  return 0;
}
