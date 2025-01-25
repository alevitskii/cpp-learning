#include <iostream>
#include <string>
#include <utility> // for std::move

/*
std::move can be used whenever we want to treat an l-value like an r-value for the purpose of invoking move semantics
instead of copy semantics.

std::move() gives a hint to the compiler that the programmer doesn't need the value of an object any more. Only use
std::move() on persistent objects whose value you want to move, and do not make any assumptions about the value of the
object beyond that point. It is okay to give a moved-from object a new value (e.g. using operator=) after the current
value has been moved.
*/

template<typename T> void mySwapMove(T& a, T& b)
{
  T tmp{ std::move(a) }; // invokes move constructor
  // between these lines `a` is in a valid but unspecified state
  a = std::move(b); // invokes move assignment
  b = std::move(tmp); // invokes move assignment
}

int main()
{
  std::string x{ "abc" };
  std::string y{ "de" };

  std::cout << "x: " << x << '\n';
  std::cout << "y: " << y << '\n';

  mySwapMove(x, y);

  std::cout << "x: " << x << '\n';
  std::cout << "y: " << y << '\n';

  return 0;
}