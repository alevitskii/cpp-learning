#include <iostream>

class Calc
{
private:
  int m_value{};

public:
  // note that a reference is returned
  Calc& add(int value)
  {
    m_value += value;
    return *this;
  }
  Calc& sub(int value)
  {
    m_value -= value;
    return *this;
  }
  Calc& mult(int value)
  {
    m_value *= value;
    return *this;
  }

  int getValue() const { return m_value; }

  // this is the way to reset the object to its default state
  void reset() { *this = {}; }
};


int main()
{
  Calc calc{};
  // returning *this can be used for chaining
  calc.add(5).sub(3).mult(4);

  std::cout << calc.getValue() << '\n'; // prints 8

  calc.reset();

  std::cout << calc.getValue() << '\n'; // prints 0

  /*
  All non-static member functions have a `this` const pointer that holds the address of the implicit object.
  When compiled the compiler rewrites `calc.add(5)` into something like `Calc::add(&calc, 5);`.
  The method is transformed into something like (implementation-specific)
  `static Calc& add(Calc* const this, int value) { this->m_value += value; return *this; }`
  On const objects `this` is a const pointer to a const object, on non-const - const pointer to non-const object.
  `this` is a pointer and not a reference because C++ didn't have refs when `this` was added in the language.
  */
  return 0;
}