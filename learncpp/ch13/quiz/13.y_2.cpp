#include <iostream>
#include <string>

int main()
{
  std::string str{ "I saw a red car yesterday." };

  std::cout << str.replace(str.find("red"), 3, "blue") << '\n'; // I saw a blue car yesterday.

  return 0;
}