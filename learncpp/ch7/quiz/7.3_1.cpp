#include <iostream>

int main()
{
  std::cout << "Enter an integer: ";
  int s{};
  std::cin >> s;

  std::cout << "Enter a larger integer: ";
  int l{};
  std::cin >> l;

  if (l < s) {
    std::cout << "Swapping the values\n";

    // local variables have block scope (are visible from their point of definition to the end of the block they are
    // defined within)
    // local variables have automatic duration (the rules that govern when a variable is created and destroyed)
    int temp{ l };
    l = s;
    s = temp;
  }

  std::cout << "The smaller value is " << s << '\n';
  std::cout << "The larger value is " << l << '\n';
  return 0;
}