#include <iostream>

void printDigitName(int x)
{
  // `x` must be an expression of integral or enumerated type or something that's convertible to it. It's because switch
  // is sometimes implemented as jump tables for optimizations purposes. An advantage over "if" is that `x` is evaluated
  // only once
  switch (x) // x is evaluated to produce value 2
  {
    // conditions must be constant expressions and they must be unique
  case 1:
    std::cout << "One";
    return;
  case 2: // which matches the case statement here
    std::cout << "Two"; // so execution starts here
    return; // and then we return to the caller
  case 3:
    std::cout << "Three";
    // Since there is no break or return, there is going to be a fallthrough: execution will continue on the first
    // statement under next label.
    [[fallthrough]]; // (C++17) indicate intentional fallthrough to silence the compiler's warnings -- note the
                     // semicolon to indicate the null statement
  case 4:
    std::cout << "Four";
    // After break we'll jump to the first statement after switch.
    break;
  case 5:
  case 6:
    std::cout << "Five or six";
    break;
  default:
    std::cout << "Unknown";
    return;
  }

  std::cout << " Ah-Ah-Ah!";
}

void printSomething()
{
  // "case" doesn't have its own scope
  switch (1) {
    int a; // okay: definition is allowed before the case labels
    // int b{ 5 }; // illegal: initialization is not allowed before the case labels
  case 1:
    int y; // okay but bad practice: definition is allowed within a case
    y = 4; // okay: assignment is allowed
    break;
  case 2:
    // int z{ 4 }; // illegal: initialization is not allowed if subsequent cases exist
    y = 5; // okay: y was declared above, so we can use it here too
    break;
  case 3:
    break;
  }

  switch (1) {
  case 1: { // note addition of explicit block here
    int x{ 4 }; // okay, variables can be initialized inside a block inside a case
    std::cout << x;
    break;
  }
  default:
    std::cout << "default case\n";
    break;
  }
}

int main()
{
  printDigitName(2);
  std::cout << '\n';

  return 0;
}