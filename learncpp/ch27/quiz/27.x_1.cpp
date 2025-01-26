#include <exception>
#include <iostream>
#include <stdexcept>

class Fraction
{
public:
  explicit Fraction(int numerator = 0, int denominator = 1) : m_numerator{ numerator }, m_denominator{ denominator }
  {
    if (denominator == 0) { throw std::runtime_error("Invalid denominator"); }
  }

  friend std::ostream& operator<<(std::ostream& os, const Fraction& f)
  {
    return os << f.m_numerator << '/' << f.m_denominator;
  }

private:
  int m_numerator{ 0 };
  int m_denominator{ 1 };
};

int main()
{
  int n{}, d{};
  std::cout << "Enter the numerator: ";
  std::cin >> n;
  std::cout << "Enter the denominator: ";
  std::cin >> d;
  try {
    Fraction f{ n, d };
    std::cout << f << '\n';
  } catch (const std::exception& e) {
    std::cerr << "Exception occurred: " << e.what() << '\n';
  }

  return 0;
}