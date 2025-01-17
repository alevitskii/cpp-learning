#include <iostream>
#include <iterator>
#include <vector>
int main()
{
  std::vector v{ 'h', 'e', 'l', 'l', 'o' };
  std::cout << "The array has " << std::size(v) << " elements.\n";
  std::cout << v[1] << v.at(1) << '\n';
  return 0;
}