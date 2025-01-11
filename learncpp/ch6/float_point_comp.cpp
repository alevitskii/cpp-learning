#include <algorithm> // for std::max
// #include <cmath>     // for std::abs
#include <iostream>

template<typename T> constexpr T constAbs(T x) { return (x < 0 ? -x : x); }

// Return true if the difference between a and b is within epsilon percent of the larger of a and b
constexpr bool approximatelyEqualRel(double a, double b, double relEpsilon)
{
  return (constAbs(a - b) <= (std::max(constAbs(a), constAbs(b)) * relEpsilon));
}

// Return true if the difference between a and b is less than or equal to absEpsilon, or within relEpsilon percent of
// the larger of a and b
constexpr bool approximatelyEqualAbsRel(double a, double b, double absEpsilon, double relEpsilon)
{
  // Check if the numbers are really close -- needed when comparing numbers near zero.
  if (constAbs(a - b) <= absEpsilon) return true;

  // Otherwise fall back to Knuth's algorithm
  return approximatelyEqualRel(a, b, relEpsilon);
}

int main()
{
  // If values are calculated == and != with floating point operands is better avoided due to rounding errors, but it's
  // ok to compare if there is enough precision.

  std::cout << std::boolalpha << (0.3f == 0.3) << '\n'; // prints false

  std::cout << std::boolalpha << (0.3 == 0.2 + 0.1) << '\n'; // prints false

  // a is really close to 1.0, but has rounding errors
  constexpr double a{ 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 };

  constexpr double relEps{ 1e-8 };
  constexpr double absEps{ 1e-12 };

  // Prior to C++23 (P0533R9) std::abs wasn't constexpr so we couldn't use this function to initialize a constexpr,
  // still not supported in clang libc++. But we can create our own constexpr abs -- constAbs
  constexpr bool same{ approximatelyEqualAbsRel(a, 1.0, absEps, relEps) };

  std::cout << approximatelyEqualRel(a, 1.0, relEps) << '\n'; // compare "almost 1.0" to 1.0
  std::cout << approximatelyEqualRel(a - 1.0, 0.0, relEps) << '\n'; // compare "almost 0.0" to 0.0

  std::cout << approximatelyEqualAbsRel(a, 1.0, absEps, relEps) << '\n'; // compare "almost 1.0" to 1.0
  std::cout << approximatelyEqualAbsRel(a - 1.0, 0.0, absEps, relEps) << '\n'; // compare "almost 0.0" to 0.0

  return 0;
}