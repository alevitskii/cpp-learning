#include <cassert>
#include <iostream>
#include <vector>

namespace Animal {
  enum Name { chicken, dog, cat, elephant, duck, snake, max_animals };
  const std::vector legs{ 2, 4, 4, 4, 2, 0 };
} // namespace Animal

int main()
{
  assert(std::size(Animal::legs) == Animal::max_animals);

  std::cout << Animal::legs[Animal::elephant] << '\n';

  return 0;
}