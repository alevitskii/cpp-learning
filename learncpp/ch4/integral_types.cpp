#include <climits> // for CHAR_BIT
#include <cstddef>
#include <cstdint> // for fixed-width integers
#include <iomanip> // for std::setw (which sets the width of the subsequent output)
#include <iostream>

// The C++ standard defines the following terms:
// - the standard integer types are short, int, long, long long (including their signed and unsigned variants).
// - the integral types are bool, the various char types, and the standard integer types.
// "integral types" only includes fundamental types: `enum` and `enum class` are not integrals

int main()
{
  std::cout << "A byte is " << CHAR_BIT << " bits\n\n";

  std::cout << std::left; // left justify output

  // C++ standard only specifies that an integral type has at least N bytes, actual size is implementation-specific. For
  // example, int must be at least 2 bytes but it's often 4 bytes
  std::cout << std::setw(16) << "bool:" << sizeof(bool) << " bytes\n";
  std::cout << std::setw(16) << "char:" << sizeof(char) << " bytes\n";
  std::cout << std::setw(16) << "short:" << sizeof(short) << " bytes\n";
  std::cout << std::setw(16) << "int:" << sizeof(int) << " bytes\n";
  std::cout << std::setw(16) << "long:" << sizeof(long) << " bytes\n";
  std::cout << std::setw(16) << "long long:" << sizeof(long long) << " bytes\n";
  std::cout << std::setw(16) << "float:" << sizeof(float) << " bytes\n";
  std::cout << std::setw(16) << "double:" << sizeof(double) << " bytes\n";
  std::cout << std::setw(16) << "long double:" << sizeof(long double) << " bytes\n";

  // sizeof returns std::size_t (defined in many headers, but it's better to include <cstddef>)

  // std::size_t is unsigned integer type, must be at least 16 bits long. Actual size is implementation-specific,
  // usually equals to the size of address-width of the app: 32ui on 32-bit platforms, 64ui on 64-bit platforms

  // Constructing an object with represantation size larger than size_t will cause a compile error. Usually the allowed
  // size if much smaller than size_t and is determined by different factors
  std::cout << sizeof(std::size_t) << '\n';

  short s; // prefer "short" instead of "short int"
  int i;
  long l; // prefer "long" instead of "long int"
  long long ll; // prefer "long long" instead of "long long int"
  signed int si; // signed prefix is redundant

  // Signed intergers range is -2^(n-1)..2^(n-1)-1, unsigned integers range is 0..(2^n)-1.
  // Signed can overflow (UB), unsigned wrap around.
  // Signed is preferable in most cases. Unsigned is preferable for bit manipulation or when well-defined wrap-around
  // behavior is required
  unsigned short us;

  // It's ok to use fixed-width types if you need a type with a guaranteed range

  // NOTE: int8_t and uint8_t behaves like chars. It's because int8_t/uint8_t and other *_t integers are aliases to
  // existing types. E.g. in most cases, std::int8_t is an alias for `signed char`, because often it's the only
  // available 8 bit integral type (`bool` and `char` are not considered to be signed integral types). std::uint8_t
  // behaves similarly.

  // If a platform has an implementation-specific 8 bit integral, int8_t will be a alias to it and behave like an
  // integer.
  std::int8_t x{ 65 }; // initialize 8-bit integral type with value 65
  std::cout << x << '\n'; // it likely prints 'A'

  // `*_least*` will give the smallest type with at least N bits.
  // `*_fast*` will give the fastest to process on CPU type with at least N bits.
  // They are very implementation-specific, careful usage is required.
  std::cout << "least 8:  " << sizeof(std::int_least8_t) * 8 << " bits\n";
  std::cout << "least 16: " << sizeof(std::int_least16_t) * 8 << " bits\n";
  std::cout << "least 32: " << sizeof(std::int_least32_t) * 8 << " bits\n";
  std::cout << '\n';
  std::cout << "fast 8:  " << sizeof(std::int_fast8_t) * 8 << " bits\n";
  std::cout << "fast 16: " << sizeof(std::int_fast16_t) * 8 << " bits\n";
  std::cout << "fast 32: " << sizeof(std::int_fast32_t) * 8 << " bits\n";

  // `char` can be signed or unsigned, usually signed.
  // `char` holds integers interpreted as ASCII characters.
  // Some implementations support multichar literals - shouldn't be used.
  char ch1{ 'a' }; // (preferred)
  std::cout << ch1; // cout prints character 'a'

  char ch2{ 98 }; // code point for 'b' (not preferred)
  std::cout << ch2; // cout prints a character ('b')

  // To extract whitespace from cin (skipped by default) `std::cin.get(ch)` can be used

  // char16_t and char32_t have the same size as std::uint_least16_t and std::uint_least32_t respectively.
  // char8_t (C++20) uses the same represantation as unsigned char.
  // wchar_t size is implementation defined.

  return 0;
}
