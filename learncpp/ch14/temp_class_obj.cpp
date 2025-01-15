#include <iostream>

class IntPair
{
private:
  int m_x{};
  int m_y{};

public:
  IntPair(int x, int y) : m_x{ x }, m_y{ y } {}

  int x() const { return m_x; }
  int y() const { return m_y; }
};

void print(IntPair p) { std::cout << "(" << p.x() << ", " << p.y() << ")\n"; }

// Case 1: Create named variable and return
IntPair ret1()
{
  IntPair p{ 3, 4 };
  return p; // returns temporary object (initialized using p)
}

// Case 2: Create temporary IntPair and return
IntPair ret2()
{
  return IntPair{ 5, 6 }; // returns temporary object (initialized using another temporary object)
}

// Case 3: implicitly convert { 7, 8 } to IntPair and return
IntPair ret3()
{
  return { 7, 8 }; // returns temporary object (initialized using another temporary object)
}

int main()
{
  print(ret1());
  print(ret2());
  print(ret3());

  char c{ 'a' };
  std::cout << static_cast<int>(c) << '\n'; // static_cast returns a temporary int direct-initialized with value of `c`
  std::cout << int{ c } << '\n'; // explicitly creates a temporary int list-initialized with value `c`

  /*
  As a quick rule of thumb: prefer static_cast when converting to a fundamental type, and a list-initialized temporary
  when converting to a class type.

  Prefer static_cast when create a temporary object when any of the following are true:
  - we need to performing a narrowing conversion;
  - we want to make it really obvious that we're converting to a type that will result in some different behavior (e.g.
  a char to an int);
  - we want to use direct-initialization for some reason (e.g. to avoid list constructors taking precedence).

  Prefer creating a new object (using list initialization) to create a temporary object when any of the following are
  true:
  - we want to use list-initialization (e.g. for the protection against narrowing conversions, or because we need to
  invoke a list constructor);
  - we need to provide additional arguments to a constructor to facilitate the conversion.
  */
  return 0;
}