#include <utility>

template<typename T = int, typename U = int> // default T and U to type int
struct Pair
{
  T first{};
  U second{};
};

struct Foo
{
  std::pair<int, int> p1{ 1, 2 }; // ok, template arguments explicitly specified
  // std::pair p2{ 1, 2 }; // compile error, CTAD can't be used in this context (non-static struct member)
};

// C++20 added the ability for the compiler to automatically generate deduction guides for aggregates.
// std::pair (and other standard library template types) come with pre-defined deduction guides.

// Here's a deduction guide for our Pair (needed in C++17 only).
// Pair objects initialized with arguments of type T and U should deduce to Pair<T, U>.
template<typename T, typename U> Pair(T, U) -> Pair<T, U>;

/*
void print(std::pair p) // compile error, CTAD can't be used here
{
  std::cout << p.first << ' ' << p.second << '\n';
}
*/

// Alias templates must be defined in global scope (as all templates)
template<typename T> using Coord = Pair<T>; // Coord is an alias for Pair<T>

int main()
{
  Pair<int, int> p1{ 1, 2 }; // explicitly specify class template Pair<int, int> (C++11 onward)
  Pair p2{ 1, 2 }; // CTAD used to deduce Pair<int, int> from the initializers (C++17)

  Pair p3; // uses default Pair<int, int>

  std::pair p4{ 1, 2 }; // ok, CTAD can be used here

  using Point = Pair<int>; // create normal type alias
  Point p5{ 1, 2 }; // compiler replaces this with Pair<int>

  Coord<int> p6{ 1, 2 }; // for some reason doesn't support CTAD here

  return 0;
}