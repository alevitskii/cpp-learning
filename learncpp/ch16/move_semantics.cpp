#include <iostream>
#include <vector>

/*
Move semantics is an optimization that allows us, under certain circumstances, to inexpensively transfer ownership of
some data members from one object to another object (rather than making a more expensive copy).
Data members that can't be moved are copied instead.

We can return move-capable types (like std::vector and std::string) by value. Such types will inexpensively move their
values instead of making an expensive copy. Such types should still be passed by const reference.
*/

std::vector<int> doSomething(std::vector<int> v2)
{
  std::vector v3{ v2[0] + v2[0] }; // 3 -- construct value to be returned to caller
  return v3; // 4 -- actually return value
}

std::vector<int> doSomething2(std::vector<int> v2) { std::vector v3{ v2[0] }; }

int main()
{
  std::vector v1{ 5 }; // 1 -- construct value to be passed to function
  std::cout << doSomething(v1)[0] << '\n'; // 2 -- actually pass value

  /*
  Copy elision can move construction of v3 to the caller site. This would be ideal but we can't rely on copy elision
  because it's not always mandatory.
  The next best thing is to move constructed v3 to the caller (using move semantics).
  */

  std::cout << v1[0] << '\n';

  return 0;
}
