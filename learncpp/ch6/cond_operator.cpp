#include <iostream>

int main()
{
  // It's better to explicitly convert operand to matching types otherwise conversion rules will be be applied
  // Cond operator has low precedence so it's better to parethesize the entire expression in complex statements and
  // condition
  std::cout << (true ? 1 : 2) << '\n'; // okay: both operands have matching type int

  std::cout << (false ? 1 : 2.2) << '\n'; // okay: int value 1 converted to double

  std::cout << (true ? -1 : 2u) << '\n'; // surprising result: -1 converted to unsigned int, result out of range

  return 0;
}