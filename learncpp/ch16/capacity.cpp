#include <iostream>
#include <vector>

/*
When a std::vector changes the amount of storage it is managing, this process is called reallocation:
- acquire new memory with desired capacity, value-init the elements (default-initialization for class types, and
zero-initialization for other types);
- copy (or move if possible) elements from old location to the new one. Return old memory to the OS;
- update capacity and length.

Reallocation is typically expensive. Avoid unnecessary reallocations.
*/

void printCapLen(const std::vector<int>& v)
{
  std::cout << "Capacity: " << v.capacity() << " Length:" << v.size() << '\n';
}

class Foo
{
private:
  std::string m_a{};
  int m_b{};

public:
  Foo(std::string_view a, int b) : m_a{ a }, m_b{ b } {}

  explicit Foo(int b) : m_a{}, m_b{ b } {};

  Foo() = default;
};

int main()
{
  // Create a vector with length 5
  std::vector v{ 0, 1, 2, 3, 4 };
  v = { 0, 1, 2, 3, 4 }; // okay, array length = 5
  printCapLen(v); // capacity 5

  for (auto i : v) std::cout << i << ' ';
  std::cout << '\n';

  // Resize vector to 3 elements
  v.resize(3); // we could also assign a list of 3 elements here
  printCapLen(v); // capacity 5, no reallocation

  for (auto i : v) std::cout << i << ' ';
  std::cout << '\n';

  // Resize vector back to 5 elements
  v.resize(5);
  printCapLen(v); // capacity 5, no reallocation

  for (auto i : v) std::cout << i << ' ';
  std::cout << '\n';

  // `shrink_to_fit` request is non-binding (implementation may fulfill, fulfill partially or ignore it).
  // When the vector is large and its elements no longer needed, it may make sense to call it.
  v.resize(0);
  v.shrink_to_fit();
  printCapLen(v); // capacity 0, reallocation happened

  /*
  A subscript is only valid if it is between 0 and the vector's length (not its capacity)!

  To increase the number of elements in a std::vector:
  - use resize() when accessing a vector via indexing. This changes the length of the vector so your indices will be
  valid;
  - use reserve() when accessing a vector using stack operations. This adds capacity without changing the length of
  the vector.
  */

  std::vector<Foo> v2{};
  // The resize() member function changes the length of the vector, and the capacity (if necessary).
  v2.resize(10);
  // The reserve() member function changes just the capacity (if necessary)
  // For vector capacity is usually changed automatically (implementation-defined, GCC and clang doubles, MSVC 1.5x)
  v2.reserve(20);

  // // // // // // // // // // // // // // // // // // // // //

  Foo f{ "a", 2 };
  // When object already exists, prefer push_back
  v2.push_back(f);
  v2.emplace_back(f);

  // When object is temporary, prefer emplace_back. It forwards (perfect forwarding) the arguments so the object can be
  // created directly in the vector (no copy made)
  v2.emplace_back("a", 2);

  // push_back won't use explicit constructors, emplace_back will
  // v2.push_back({ 2 }); // compile error: Foo(int) is explicit
  v2.emplace_back('a'); // ok

  // Prior to C++20, emplace_back() doesn't work with aggregate initialization.

  return 0;
}