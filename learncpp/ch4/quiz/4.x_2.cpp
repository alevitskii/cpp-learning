#include <iostream>


int main()
{
  std::cout << "Enter a floating point number: ";
  double a{};
  std::cin >> a;
  std::cout << "Enter a floating point number: ";
  double b{};
  std::cin >> b;

  std::cout << "Enter +, -, *, or /: ";
  char sign{};
  std::cin >> sign;
  double ans{};
  if (sign == '+')
    ans = a + b;
  else if (sign == '-')
    ans = a - b;
  else if (sign == '*')
    ans = a * b;
  else if (sign == '/')
    ans = a / b;
  else
    return 0;

  std::cout << a << " " << sign << " " << b << " is " << ans << '\n';

  return 0;
}