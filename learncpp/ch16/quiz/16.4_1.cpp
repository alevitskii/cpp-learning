#include <iostream>
#include <iterator>
#include <vector>

template<typename T> void printElement(const std::vector<T>& v, int i)
{
  if (i < 0 || i >= std::ssize(v)) {
    std::cout << "Invalid index\n";
  } else {
    std::cout << "The element has value " << v[static_cast<std::size_t>(i)] << '\n';
  }
}

int main()
{
  std::vector v1{ 0, 1, 2, 3, 4 };
  printElement(v1, 2);
  printElement(v1, 5);

  std::vector v2{ 1.1, 2.2, 3.3 };
  printElement(v2, 0);
  printElement(v2, -1);

  return 0;
}