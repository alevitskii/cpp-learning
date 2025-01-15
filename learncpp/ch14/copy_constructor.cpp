#include <iostream>

class Fraction
{
private:
  int m_numerator{ 0 };
  int m_denominator{ 1 };

public:
  // Default constructor
  Fraction(int numerator = 0, int denominator = 1) : m_numerator{ numerator }, m_denominator{ denominator } {}

  /*
  Copy constructors should have no side effects beyond copying because compiler may sometimes optimize out copying.

  Prefer the implicit copy constructor, unless you have a specific reason to create your own. Default copy constructor
  does memberwise init.
  If you write your own copy constructor, the parameter should be a const lvalue reference (pass by value will cause
  infinite calls to the constructor).
  */

  // Copy constructor
  Fraction(const Fraction& fraction) : m_numerator{ fraction.m_numerator }, m_denominator{ fraction.m_denominator }
  {
    std::cout << "Copy constructor called\n";
  }

  // Explicitly requested default copy constructor
  // Fraction(const Fraction& fraction) = default;

  // Delete the copy constructor so no copies can be made. We could also make the copy constructor private but that
  // would allow class members use it.
  // Fraction(const Fraction& fraction) = delete;

  void print() const { std::cout << "Fraction(" << m_numerator << ", " << m_denominator << ")\n"; }
};

void printFraction(Fraction f) // f is pass by value
{
  f.print();
}

Fraction generateFraction(int n, int d)
{
  Fraction f{ n, d };
  return f;
}

class Something
{
public:
  Something() = default;
  Something(const Something&) { std::cout << "Copy constructor called\n"; }
};

Something rvo()
{
  return Something{}; // calls Something() and copy constructor
}

Something nrvo()
{
  Something s{}; // calls Something()
  return s; // calls copy constructor
}

int main()
{
  Fraction f2{ generateFraction(
    1, 2) }; // Fraction is returned using copy constructor (when types of the returned value and return type match)

  printFraction(f2); // f2 is copied into the function parameter using copy constructor (when types of the parameter and
                     // argument type match)

  /*
  Copy elision can sometimes happen. Since C++17 copy elision is mandatory in some cases and can happen even if the copy
  constructor is deleted. But it's still optional in other cases (an accessible copy constructor must be available even
  if the copy is elided).
  There also may be a move semantics for types that support it.
  */

  /*
  Without copy elision there would 4 copy constructor calls:
  - once when rvo returns Something to main;
  - once when the return value of rvo() is used to initialize s1;
  - once when nrvo returns s to main;
  - once when the return value of nrvo() is used to initialize s2.
  Modern compilers can eliminate all 4.
  */
  std::cout << "Initializing s1\n";
  Something s1{ rvo() }; // calls copy constructor

  std::cout << "Initializing s2\n";
  Something s2{ nrvo() }; // calls copy constructor

  // Copy elision is mandatory here since C++17. Prior to C++17 we could get temp object inited with the args and then
  // copy construct "f" in printFraction with temp. Since C++17 we copy init "f" with the args.
  printFraction({ 1, 2 });

  return 0;
}