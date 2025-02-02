#include <cassert>
#include <iostream>
#include <iterator>
#include <utility> // for std::as_const


class IntList
{
private:
  int m_list[10]{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }; // give this class some initial state for this example

public:
  // int& operator[](int index) { return m_list[index]; }
  // When code is simple, it's better to have redundancy like above than something like below.
  int& operator[](int index)
  {
    // Use std::as_const to get a const version of `this` (as a reference) so we can call the const version of
    // operator[]. Then const_cast to discard the const on the returned reference.
    return const_cast<int&>(std::as_const(*this)[index]);
  }
  // parameter doesn't have to be int, can be any type
  const int& operator[](int index) const
  {
    assert(index >= 0 && static_cast<std::size_t>(index) < std::size(m_list));
    return m_list[index];
  }

  /* C++23
  // Use an explicit object parameter (self) and auto&& to differentiate const vs non-const
  auto&& operator[](this auto&& self, int index)
  {
    // Complex code goes here
    return self.m_list[index];
  }
  */
};
int main()
{
  IntList list{};
  list[2] = 3; // okay: calls non-const version of operator[]
  std::cout << list[2] << '\n';

  const IntList clist{};
  // clist[2] = 3; // compile error: clist[2] returns const reference, which we can't assign to
  std::cout << clist[2] << '\n';

  IntList* list2{ new IntList{} };
  // list2[2] = 3; // make sure you're not trying to call an overloaded operator[] on a pointer to an object (may result
  // in UB)
  (*list2)[2] = 3; // get our IntList object, then call overloaded operator[], ugly but ok
  delete list2;

  return 0;
}