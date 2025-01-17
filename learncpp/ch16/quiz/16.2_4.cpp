#include <iostream>
#include <vector>

int main()
{
  std::vector<int> vec(3);
  std::cout << "Enter 3 integers: ";
  std::cin >> vec[0] >> vec[1] >> vec[2];

  std::cout << "The sum is: " << vec[0] + vec[1] + vec[2] << '\n';
  std::cout << "The produce is: " << vec[0] * vec[1] * vec[2] << '\n';

  return 0;
}