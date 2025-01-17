#include <cassert>
#include <cstddef>
#include <iostream>
#include <iterator>
#include <string_view>
#include <vector>


namespace Items {
  enum Type { health_potion, torch, arrow, max_item };
}

std::string_view getItemString(Items::Type i, int cnt)
{
  switch (i) {
  case Items::health_potion:
    if (cnt > 1)
      return "health potions";
    else
      return "health potion";
  case Items::torch:
    if (cnt > 1)
      return "torches";
    else
      return "torch";
  case Items::arrow:
    if (cnt > 1)
      return "arrows";
    else
      return "arrow";
  default:
    return "???";
  }
}

int main()
{
  std::vector items{ 1, 5, 10 };

  assert(std::ssize(items) == Items::max_item);

  int sum{ 0 };
  for (auto i{ 0Z }; i < std::ssize(items); ++i) {
    std::cout << "You have " << items.data()[i] << ' ' << getItemString(static_cast<Items::Type>(i), items.data()[i])
              << '\n';
    sum += items.data()[i];
  }

  std::cout << "You have " << sum << " total items\n";

  return 0;
}