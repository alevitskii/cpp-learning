#include <cassert>
#include <cstdint>
#include <iostream>

class FixedPoint2
{
public:
  FixedPoint2(std::int16_t base = 0, std::int8_t decimal = 0) : m_base{ base }, m_decimal{ decimal }
  {
    if (m_base < 0 || m_decimal < 0) {
      if (m_base > 0) m_base = -m_base;
      if (m_decimal > 0) m_decimal = -m_decimal;
    }
    m_base += m_decimal / 100;
    m_decimal %= 100;
  }

  FixedPoint2(double d)
    : FixedPoint2(static_cast<std::int16_t>(std::trunc(d)),
        static_cast<std::int8_t>(std::round(d * 100) - std::trunc(d) * 100))
  {}

  explicit operator double() const { return m_base + (static_cast<double>(m_decimal) / 100); }

  FixedPoint2 operator-() const
  {
    return FixedPoint2{ -static_cast<double>(*this) };
    // or return FixedPoint2{ static_cast<std::int16_t>(-m_base), static_cast<int8_t>(-m_decimal) };
  }

  friend bool operator==(const FixedPoint2& fp1, const FixedPoint2& fp2);
  friend FixedPoint2 operator+(const FixedPoint2& fp1, const FixedPoint2& fp2);
  friend std::istream& operator>>(std::istream& is, FixedPoint2& fp);

  friend bool testDecimal(const FixedPoint2& fp);

private:
  std::int16_t m_base{};
  std::int8_t m_decimal{};
};

std::ostream& operator<<(std::ostream& os, const FixedPoint2& p)
{
  os << static_cast<double>(p);
  return os;
}

std::istream& operator>>(std::istream& is, FixedPoint2& fp)
{
  double d{};
  is >> d;
  fp = d;
  return is;
}

bool operator==(const FixedPoint2& fp1, const FixedPoint2& fp2)
{
  return fp1.m_base == fp2.m_base && fp1.m_decimal == fp2.m_decimal;
}

FixedPoint2 operator+(const FixedPoint2& fp1, const FixedPoint2& fp2)
{
  return FixedPoint2{ static_cast<double>(fp1) + static_cast<double>(fp2) };
}

bool testDecimal(const FixedPoint2& fp)
{
  if (fp.m_base >= 0)
    return fp.m_decimal >= 0 && fp.m_decimal < 100;
  else
    return fp.m_decimal <= 0 && fp.m_decimal > -100;
}

int main()
{
  FixedPoint2 a{ 1, 104 };
  std::cout << a << '\n';
  std::cout << static_cast<double>(a) << '\n';
  assert(static_cast<double>(a) == 2.04);
  assert(testDecimal(a));

  FixedPoint2 a1{ 0.01 };
  assert(static_cast<double>(a1) == 0.01);

  FixedPoint2 b{ -0.01 };
  assert(static_cast<double>(b) == -0.01);

  FixedPoint2 c{ 1.9 }; // make sure we handle single digit decimal
  assert(static_cast<double>(c) == 1.9);

  FixedPoint2 d{ 5.01 }; // stored as 5.0099999... so we'll need to round this
  assert(static_cast<double>(d) == 5.01);

  FixedPoint2 e{ -5.01 }; // stored as -5.0099999... so we'll need to round this
  assert(static_cast<double>(e) == -5.01);

  // Handle case where the argument's decimal rounds to 100 (need to increase base by 1)
  FixedPoint2 f{ 106.9978 }; // should be stored with base 107 and decimal 0
  assert(static_cast<double>(f) == 107.0);

  // Handle case where the argument's decimal rounds to -100 (need to decrease base by 1)
  FixedPoint2 g{ -106.9978 }; // should be stored with base -107 and decimal 0
  assert(static_cast<double>(g) == -107.0);

  assert(FixedPoint2{ 0.75 } == FixedPoint2{ 0.75 }); // Test equality true
  assert(!(FixedPoint2{ 0.75 } == FixedPoint2{ 0.76 })); // Test equality false

  // Test additional cases
  assert(FixedPoint2{ 0.75 } + FixedPoint2{ 1.23 } == FixedPoint2{ 1.98 }); // both positive, no decimal overflow
  assert(FixedPoint2{ 0.75 } + FixedPoint2{ 1.50 } == FixedPoint2{ 2.25 }); // both positive, with decimal overflow
  assert(FixedPoint2{ -0.75 } + FixedPoint2{ -1.23 } == FixedPoint2{ -1.98 }); // both negative, no decimal overflow
  assert(FixedPoint2{ -0.75 } + FixedPoint2{ -1.50 } == FixedPoint2{ -2.25 }); // both negative, with decimal overflow
  assert(FixedPoint2{ 0.75 } + FixedPoint2{ -1.23 } == FixedPoint2{ -0.48 }); // second negative, no decimal overflow
  assert(
    FixedPoint2{ 0.75 } + FixedPoint2{ -1.50 } == FixedPoint2{ -0.75 }); // second negative, possible decimal overflow
  assert(FixedPoint2{ -0.75 } + FixedPoint2{ 1.23 } == FixedPoint2{ 0.48 }); // first negative, no decimal overflow
  assert(
    FixedPoint2{ -0.75 } + FixedPoint2{ 1.50 } == FixedPoint2{ 0.75 }); // first negative, possible decimal overflow

  FixedPoint2 a2{ -0.48 };
  assert(static_cast<double>(a2) == -0.48);
  assert(static_cast<double>(-a2) == 0.48);

  std::cout << "Enter a number: "; // enter 5.678
  std::cin >> a2;
  std::cout << "You entered: " << a2 << '\n';
  assert(static_cast<double>(a2) == 5.68);

  return 0;
}