#include <iostream>

void printValue(int value) { std::cout << value << '\n'; }

void a() { std::cout << "a() called\n"; }

void b()
{
  std::cout << "b() called\n";
  a();
}

int main()
{
  int x{ 1 };
  std::cout << x << ' ';

  x = x + 2;
  std::cout << x << ' ';

  x = x + 3;
  std::cout << x << ' ';

  printValue(5);

  a();
  b();

  return 0;
}