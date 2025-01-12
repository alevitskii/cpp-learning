#include <iostream>

int calculate(int x, int y, char oper)
{
  switch (oper) {
  case '+':
    return x + y;
  case '-':
    return x - y;
  case '*':
    return x * y;
  case '/':
    return x / y;
  case '%':
    return x % y;
  default:
    std::cerr << "Unknown operator " << oper << '\n';
    return 0;
  }
}

int main()
{
  int ret = calculate(5, 10, '+');
  std::cout << ret;
  return 0;
}