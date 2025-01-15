#include <iostream>

// Aggregates implicitly support constexpr.
struct PairS // Pair is an aggregate
{
  int m_x{};
  int m_y{};

  constexpr int greater() const { return (m_x > m_y ? m_x : m_y); }
};

class PairC
{
private:
  int m_x{};
  int m_y{};

public:
  // Must have constexpr constructor if want to be used in constexpr context.
  constexpr PairC(int x, int y) : m_x{ x }, m_y{ y } {}

  constexpr int greater() const // constexpr and const
  {
    return (m_x > m_y ? m_x : m_y);
  }

  // As of C++14, constexpr member functions are not implicitly const.
  constexpr void reset() // constexpr but non-const
  {
    m_x = m_y = 0; // non-const member function can change members
  }

  // `constexpr` says the function can be evaluated at compile-time. `const int&` is the return type. const says the
  // function can be called on const objects
  constexpr const int& getX() const { return m_x; }
};

constexpr PairC zero()
{
  // When evaluated in a compile-time context all functions in zero must be constexpr (not necessarily const).
  PairC p{ 1, 2 }; // p is non-const
  p.reset(); // okay to call non-const member function on non-const object
  return p;
}

int main()
{
  constexpr PairS p{ 5, 6 };
  std::cout << p.greater() << '\n'; // p.greater() evaluates at runtime or compile-time

  constexpr int g{ p.greater() }; // p.greater() must evaluate at compile-time
  std::cout << g << '\n';

  PairC p1{ 3, 4 };
  p1.reset(); // okay to call non-const member function on non-const object
  std::cout << p1.getX() << '\n'; // prints 0

  PairC p2{ zero() }; // zero() will be evaluated at runtime
  p2.reset(); // okay to call non-const member function on non-const object
  std::cout << p2.getX() << '\n'; // prints 0

  // zero() returns a non-const object. There is no requirement that a constexpr variable be initialized with a const
  // value. The important thing isn't the const, its that the compiler can determine the value of the object at
  // compile-time
  constexpr PairC p3{ zero() }; // zero() will be evaluated at compile-time
  // p3.reset(); // Compile error: can't call non-const member function on const object
  std::cout << p3.getX() << '\n'; // prints 0

  return 0;
}