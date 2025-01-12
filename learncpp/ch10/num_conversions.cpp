/*
Floating-point and intergral promotions are safe. They are done implicilty for the purpose of better performance.
For example, if working with ints is faster than with short, compiler will promote short to int.
Often compiler opt in for numeric promotions rather than conversions.

There are 3 types of conversions:
1. Value-preserving conversions - they are safe;
2. Reinterpretive conversions are unsafe numeric conversions where the converted value may be different than the source
value, but no data is lost;
3. Lossy conversions are unsafe numeric conversions where data may be lost during the conversion.

Some conversion may be of different types on different platforms. For example, if int and double are both 8 bytes there
will be a data loss when converting from int to double if int is big enough
*/

int main()
{
  // (1)
  int n{ 5 };
  long l = n; // okay, produces long value 5

  short s{ 5 };
  double d = s; // okay, produces double value 5.0

  // (2)
  int n2{ 5 };
  unsigned int u1{ static_cast<unsigned int>(n2) }; // okay: will be converted to unsigned int 5 (value preserved)

  int n3{ -5 };
  unsigned int u2{ static_cast<unsigned int>(n3) }; // bad: will result in large integer outside range of signed int

  // reinterpreting conversion when converted back produce the same value
  int u = static_cast<int>(static_cast<unsigned int>(-5)); // convert '-5' to unsigned and back

  // (3)
  double d2{ static_cast<double>(static_cast<float>(1.23456789)) }; // convert double 1.23456789 to float and back

  // It's better to be explicit when doing narrowing conversions -- use static_cast
  double d3{ 3.5 };
  // static_cast<int> converts double to int, initializes i with int result
  int i{ static_cast<int>(d) };

  // If source value is known at compile time (constexpr), compiler won't complain about conversion if the value is
  // preserved
  constexpr int n1{ 5 }; // note: constexpr
  unsigned int u3{ n1 }; // okay: conversion is not narrowing due to exclusion clause

  constexpr int n4{ -5 }; // note: constexpr
  // unsigned int u4{ n4 }; // compile error: conversion is narrowing due to value change

  // However, conversion from floating point to int is always an error.
  // int n5{ 5.0 }; // compile error: narrowing conversion

  // But double to float is allowed, even if precision is lost.
  constexpr double d4{ 1.23456789 };
  float f{ d4 }; // not narrowing, even though loss of precision results

  return 0;
}