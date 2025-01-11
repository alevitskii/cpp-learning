#include <iostream>

bool isPrimeOr(int x) { return x == 2 || x == 3 || x == 5 || x == 7; }


bool isPrimeSwitch(int x)
{
  switch (x) {
  case 2:
  case 3:
  case 5:
  case 7:
    return true;
  }
  return false;
}


int main()
{
  std::cout << "Enter an integer number (0-9): ";
  int x{};
  std::cin >> x;

  if (isPrimeOr(x))
    std::cout << "You entered a prime number\n";
  else
    std::cout << "You entered a non-prime number\n";
}