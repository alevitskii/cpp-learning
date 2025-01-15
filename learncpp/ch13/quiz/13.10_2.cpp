#include <iostream>

struct Fraction
{
  int numerator{};
  int denominator{};
};

// it's also OK to create temp object and return by value because Fraction is small
void getFraction(Fraction& f)
{
  std::cout << "Enter a value for the numerator: ";
  std::cin >> f.numerator;
  std::cout << "Enter a value for the denominator: ";
  std::cin >> f.denominator;
}

Fraction multiply(const Fraction& f1, const Fraction& f2)
{
  return { f1.numerator * f2.numerator, f1.denominator * f2.denominator };
}

void printFraction(const Fraction& f)
{
  std::cout << "Your fractions multiplied together: " << f.numerator << '/' << f.denominator << '\n';
}

int main()
{
  Fraction f1{};
  getFraction(f1);
  Fraction f2{};
  getFraction(f2);
  printFraction(multiply(f1, f2));
  return 0;
}