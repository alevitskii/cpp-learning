#include <iomanip>
#include <iostream>
#include <limits>

int main()
{
  // The digits in the significand (the part before the ‘e’) are called the significant digits.
  // 4 significant digits
  double a{ 1.345e2 };
  // 6 significant digits, it's equal to 1.345e2 but states the precision
  double b{ 1.34500e2 };
  double c{ 134000 }; // 1.34e5 (if there are no decimal point, by default assuming trailing zeroes are not significant.
                      // But they may be significant for some reason)
  double d{ 0.0078900 }; // 7.8900e-3

  // Because float and double are usually implemented according to IEEE 754 they are almost always 4 and 8 bytes
  // respectively, long double can be 8, 12 or 16 bytes
  std::cout << std::boolalpha; // print bool as true or false rather than 1 or 0
  std::cout << "float: " << std::numeric_limits<float>::is_iec559 << '\n';
  std::cout << "double: " << std::numeric_limits<double>::is_iec559 << '\n';
  std::cout << "long double: " << std::numeric_limits<long double>::is_iec559 << '\n';

  int e{ 5 }; // 5 means integer
  double f{ 5.0 }; // 5.0 is a floating point literal (no suffix means double type by default)
  float g{ 5.0f }; // 5.0 is a floating point literal, f suffix means float type
  float h{ 5.0 }; // 5.0 literal is double, conversion happens, it's better to specify suffix

  std::cout << std::setprecision(17); // show 17 digits of precision
  // floats are usually trimmed to 6 when outputing, because 6 is a minimum precision for a float.
  // Output will show that float is less precise
  std::cout << 3.33333333333333333333333333333333333333f << '\n';
  std::cout << 3.33333333333333333333333333333333333333 << '\n';
  float i{ 123456789.0f }; // f has 10 significant digits
  std::cout << std::setprecision(9); // to show 9 digits in f
  std::cout << i << '\n'; // rounding error

  double j{ 0.1 };
  std::cout << j << '\n'; // use default cout precision of 6
  std::cout << std::setprecision(17);
  // rounding errors may grow and cause unexpected results during comparison
  std::cout << j << '\n';


  // IEEE 754 compatible formats additionally support some special values: +Inf, -Inf, NaN (several kinds), +0.0, -0.0
  // Avoid division by 0.0, even if your compiler supports it. If it doesn't -- implementation-defined behavior.

  // division by integer 0 causes UB
  double zero{ 0.0 };

  double posinf{ 5.0 / zero }; // positive infinity
  std::cout << posinf << '\n';

  double neginf{ -5.0 / zero }; // negative infinity
  std::cout << neginf << '\n';

  double z1{ 0.0 / posinf }; // positive zero
  std::cout << z1 << '\n';

  double z2{ -0.0 / posinf }; // negative zero
  std::cout << z2 << '\n';

  double nan{ zero / zero }; // not a number (mathematically invalid)
  std::cout << nan << '\n';

  return 0;
}
