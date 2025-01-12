#include <iostream>

int main()
{
  constexpr double gravity{ 9.8 };

  // this piece of code will be replaced by std::cout << "Gravity is normal.\n";
  if constexpr (gravity == 9.8) // now using constexpr if
    std::cout << "Gravity is normal.\n";
  else
    std::cout << "We are not on Earth.\n";

  // Modern compilers can evaluate non constexpr "if" even if conditions is not constexpr but they are not required to
  // do so so it's better to write constexpr

  return 0;
}