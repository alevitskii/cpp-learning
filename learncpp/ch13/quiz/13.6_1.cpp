#include <iostream>
#include <string_view>

enum class Animal {
  pig,
  chicken,
  goat,
  cat,
  dog,
  duck,
};

constexpr std::string_view getAnimalName(Animal a)
{
  using enum Animal;
  switch (a) {
  case pig:
    return "pig";
  case chicken:
    return "chicken";
  case goat:
    return "goat";
  case cat:
    return "cat";
  case dog:
    return "dog";
  case duck:
    return "duck";
  default:
    std::cout << "Unknown animal\n";
    return "unknown";
  }
}

void printNumberOfLegs(Animal a)
{
  using enum Animal;
  int legs{};
  switch (a) {
  case pig:
  case goat:
  case cat:
  case dog:
    legs = 4;
    break;
  case chicken:
  case duck:
    legs = 2;
    break;
  default:
    std::cout << "Unknown animal\n";
    return;
  }
  std::cout << "A " << getAnimalName(a) << " has " << legs << " legs.\n";
}

int main()
{
  printNumberOfLegs(Animal::cat);
  printNumberOfLegs(Animal::chicken);
  return 0;
}