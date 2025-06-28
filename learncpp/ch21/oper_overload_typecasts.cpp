#include <iostream>

/*
Typecasts should be marked as explicit, except in cases where the class to be converted to is essentially synonymous.

Overloaded typecasts and converting constructors perform similar roles. In general, a converting constructor should be
preferred to an overloaded typecast, as it allows the type being constructed to own the construction.

There are a few cases where an overloaded typecast should be used instead:
- when providing a conversion to a fundamental type (since you can't define constructors for these types). Most
idiomatically, these are used to provide a conversion to bool where it makes sense;
- when the conversion returns a reference or const reference;
- when providing a conversion to a type you can't add members to (e.g. a conversion to std::vector);
- when you do not want the type being constructed to be aware of the type being converted from. This can be helpful for
avoiding circular dependencies (e.g. std::string -> std::string_view conversion is implemented as a typecast in
<string>).

When you need to define how convert type A to type B:
- if B is a class type you can modify, prefer using a converting constructor to create B from A;
- otherwise, if A is a class type you can modify, use an overloaded typecast to convert A to B;
- otherwise use a non-member function to convert A to B.
*/

class Cents
{
private:
  int m_cents{};

public:
  Cents(int cents = 0) : m_cents{ cents } {}

  // Note doesn't have return type (it's always int). Note doesn't take params.
  explicit operator int() const { return m_cents; }

  int getCents() const { return m_cents; }
  void setCents(int cents) { m_cents = cents; }
};

class Dollars
{
private:
  int m_dollars{};

public:
  Dollars(int dollars = 0) : m_dollars{ dollars } {}

  // Not explicit: Dollars to Cents implicit conversion is allowed
  operator Cents() const { return Cents{ m_dollars * 100 }; }
};

void printCents(Cents cents)
{
  std::cout << static_cast<int>(cents); // must use explicit cast to invoke explicit typecast
}

int main()
{
  Dollars dollars{ 9 };
  printCents(dollars);

  std::cout << '\n';

  return 0;
}
