#include <iostream>

// Shadowing should be avoided.

int value{ 5 }; // global variable

int main()
{
  int apples{ 5 };
  {
    std::cout << apples << '\n';
    // apples in the nested block shadows apples from the outer block.
    // There is no way to access shadowed variable inside the nested block.
    int apples{};
    apples = 10;
    std::cout << apples << '\n';
  }
  std::cout << apples << '\n';

  int value{ 7 }; // hides
  ++value; // increments local

  --::value; // decrements global value

  std::cout << "local variable value: " << value << '\n';
  std::cout << "global variable value: " << ::value << '\n';
  return 0;
}