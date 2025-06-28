/*
Category			Standard Conversion		Description
Value transformation		Lvalue-to-rvalue		Converts lvalue expression to rvalue expression
Value transformation		Array-to-pointer		Converts C-style array to pointer to first array element (a.k.a. array decay)
Value transformation		Function-to-pointer		Converts function to function pointer
Value transformation		Temporary materialization	Converts value to temporary object
Qualification conversion	Qualification conversion	Adds or removes const or volatile from types
Numeric promotions		Integral promotions		Converts smaller integral types to int or unsigned int
Numeric promotions		Floating point promotions	Converts float to double
Numeric conversions		Integral conversions		Integral conversions that aren’t integral promotions
Numeric conversions		Floating point conversions	Floating point conversions that aren’t floating point promotions
Numeric conversions		Integral-floating conversions	Converts integral and floating point types
Numeric conversions		Boolean conversions		Converts integral, unscoped enumeration, pointer, or pointer-to-memver to bool
Pointer conversions		Pointer conversions		Converts std::nullptr to pointer, or pointer to void pointer or base class
Pointer conversions		Pointer-to-member conversions	Converts std::nullptr to pointer-to-member or pointer-to-member of base class to pointer-to-member of derived class
Pointer conversions		Function pointer conversions	Converts pointer-to-noexcept-function to pointer-to-function

Floating-point and integral promotions are safe. They are done implicilty for the purpose of better performance.
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
