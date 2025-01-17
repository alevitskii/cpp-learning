#include <algorithm>
#include <iostream>
#include <string>

int main()
{
  std::cout << "How many names would you like to enter? ";
  std::size_t num{};
  std::cin >> num;
  auto* names{ new std::string[num]{} };

  for (int i{ 0 }; i < num; ++i) {
    std::cout << "Enter name #" << i << ": ";
    std::getline(std::cin >> std::ws, names[i]);
  }

  std::sort(names, names + num);

  std::cout << "Here is your sorted list:\n";
  for (int i{ 0 }; i < num; ++i) { std::cout << "Name #" << i << ": " << names[i] << '\n'; }

  delete[] names;

  return 0;
}