#include <cassert>
#include <iostream>


// operator() is often used to access elements of a multidimensional array (prior C++23, since C++23 operator[] can take
// multiple params) or to produce functors (function objects)
class Accumulator
{
private:
  int m_counter{ 0 };

public:
  // can take any number of params
  int operator()(int i) { return (m_counter += i); }

  void reset() { m_counter = 0; } // optional
};

int main()
{
  Accumulator acc{};
  std::cout << acc(1) << '\n'; // prints 1
  std::cout << acc(3) << '\n'; // prints 4

  Accumulator acc2{};
  std::cout << acc2(10) << '\n'; // prints 10
  std::cout << acc2(20) << '\n'; // prints 30

  return 0;
}