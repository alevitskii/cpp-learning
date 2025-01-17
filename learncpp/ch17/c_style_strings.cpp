#include <cstring> // for std::strlen
#include <iostream>
#include <iterator> // for std::size

int main()
{
  // Recommended way to read c-style strings.
  // Prior to C++20, it was allowed to read into a decayed string (and get buffer overflow), in C++20 it's disallowed.
  char rolls[255]{}; // declare array large enough to hold 254 characters + null terminator
  std::cout << "Enter your rolls: ";
  std::cin.getline(rolls, std::size(rolls));
  std::cout << "You entered: " << rolls << '\n';

  char str[255]{ "string" }; // 6 characters + null terminator
  std::cout << "length = " << std::size(str) << '\n'; // prints length = 255 (returns size, not length)

  char* ptr{ str };
  // std::size doesn't work on decayed strings
  // std::cout << "length = " << std::size(ptr) << '\n'; // compile error
  // Note that std::strlen is slow, it traverses the string.
  std::cout << "length = " << std::strlen(ptr) << '\n'; // prints length = 6

  // Avoid non-const C-style string objects in favor of std::string.

  // // // // // // // // C-style string symbolic constants // // // // // // // //

  // First "Alex" is put in RO memory somewhere, then memory for the C-style array of length 5 is allocated and inited
  // with the string. As a result, 2 copies (in global RO memory and in "name"). Since name is a const, making a copy is
  // inefficient.
  const char name[]{ "Alex" }; // case 1: const C-style string initialized with C-style string literal
  // How the compiler handles this is implementation defined. Usually the compiler places the string into RO memory, and
  // then inits the pointer with the address of the string.
  const char* const color{ "Orange" }; // case 2: const pointer to C-style string literal

  std::cout << name << ' ' << color << '\n';

  // multiple string may be consolidated into a single value, name1 and name2 may point at the same address
  const char* name1{ "Alex" };
  const char* name2{ "Alex" };

  auto s1{ "Alex" }; // type deduced as const char*
  auto* s2{ "Alex" }; // type deduced as const char*
  auto& s3{ "Alex" }; // type deduced as const char(&)[5]

  int narr[]{ 9, 7, 5, 3, 1 };
  char carr[]{ "Hello!" };
  const char* ptr2{ "Alex" };

  // The output streams assumes that you want to print a string when char* or const char* is passed. Beware when you try
  // to print the address of char (it's not null terminated so you'll get garbage (UB)).
  std::cout << narr << '\n'; // narr will decay to type int* (prints address)
  std::cout << carr << '\n'; // carr will decay to type char* (prints string)
  std::cout << ptr << '\n'; // name is already type char* (prints string)
  std::cout << static_cast<const void*>(ptr) << '\n'; // if you really want to print address

  // Avoid C-style string symbolic constants in favor of constexpr std::string_view.

  return 0;
}