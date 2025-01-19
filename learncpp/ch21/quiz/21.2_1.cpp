#include <iostream>
#include <numeric>

class Fraction
{
public:
  explicit Fraction(int n, int d = 1) : m_nominator{ n }, m_denominator{ d } { reduce(); }
  void print() { std::cout << m_nominator << '/' << m_denominator << '\n'; }
  friend Fraction operator*(const Fraction& f1, const Fraction&);
  // if we didn't have explicit constructor we could get rid of these functinons, but we'd get conversion from int to
  // Fraction which is a litle slower
  friend Fraction operator*(const Fraction& f1, int value);
  friend Fraction operator*(int value, const Fraction& f1);

private:
  int m_nominator{ 0 };
  int m_denominator{ 1 };

  void reduce()
  {
    int gcd{ std::gcd(m_nominator, m_denominator) };
    if (gcd) {
      m_nominator /= gcd;
      m_denominator /= gcd;
    }
  }
};

Fraction operator*(const Fraction& f1, const Fraction& f2)
{
  return Fraction{ f1.m_nominator * f2.m_nominator, f1.m_denominator * f2.m_denominator };
}
Fraction operator*(const Fraction& f1, int value) { return Fraction{ f1.m_nominator * value, f1.m_denominator }; }
Fraction operator*(int value, const Fraction& f1) { return f1 * value; }

int main()
{
  Fraction f1{ 2, 5 };
  f1.print();

  Fraction f2{ 3, 8 };
  f2.print();

  Fraction f3{ f1 * f2 };
  f3.print();

  Fraction f4{ f1 * 2 };
  f4.print();

  Fraction f5{ 2 * f2 };
  f5.print();

  Fraction f6{ Fraction{ 1, 2 } * Fraction{ 2, 3 } * Fraction{ 3, 4 } };
  f6.print();

  Fraction f7{ 0, 6 };
  f7.print();

  return 0;
}