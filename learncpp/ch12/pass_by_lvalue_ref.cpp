#include <iostream>

/*
As a rule of thumb, pass fundamental types by value and class types by const reference.
If you aren’t sure what to do, pass by const reference, as you’re less likely to encounter UB.

The following are often passed by value (because it is more efficient):
- Enumerated types (unscoped and scoped enumerations);
- Views and spans (e.g. std::string_view, std::span);
- Types that mimic references or (non-owning) pointers (e.g. iterators, std::reference_wrapper);
- Cheap-to-copy class types that have value semantics (e.g. std::pair with elements of fundamental types,
std::optional, std::expected).

Pass by reference should be used for the following:
- Arguments that need to be modified by the function;
- Types that aren’t copyable (such as std::ostream);
- Types where copying has ownership implications that we want to avoid (e.g. std::unique_ptr, std::shared_ptr);
- Types that have virtual functions or are likely to be inherited from (due to object slicing concerns).
*/

void addOne(int& y) // y is bound to the actual object x
{
  ++y; // this modifies the actual object x
}

void printRef(const int& y) // y is a const reference
{
  std::cout << y << '\n';
}

int main()
{
  int x{ 5 };
  std::cout << "value = " << x << '\n';
  addOne(x);
  std::cout << "value = " << x << '\n'; // x has been modified

  // It's recommended to use const ref instead of ref where possible.
  // Note that when we pass by const ref and the types of the ref and object differ, conversion will occur which can be
  // suboptimal. So make sure types match.
  int xx{ 5 };
  printRef(xx); // ok: xx is a modifiable lvalue, y binds to xx
  const int z{ 5 };
  printRef(z); // ok: z is a non-modifiable lvalue, y binds to z
  printRef(5); // ok: 5 is rvalue literal, y binds to temporary int object

  return 0;
}