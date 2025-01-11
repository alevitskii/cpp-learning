#include <iostream>
#include <iterator>
#include <string>
#include <string_view>

void printSV(std::string_view str) // now a std::string_view
{
  std::cout << str << '\n';
}

int main()
{
  // string literal is copied into name
  std::string name{ "Alex" };
  std::cout << name << " has " << name.length() << " characters\n";

  std::cout << "Now enter your name: ";
  // std::getline allowes to get the string with whitespace characters but you should add std::ws manipulator to skip
  // leading whitespace characters. std::cin does that automatically but it stops extracting at the first non-whitespace
  std::getline(std::cin >> std::ws, name); // note: added std::ws here
  std::cout << name << ' ' << name.length() << std::ssize(name) << '\n';
  int length{ static_cast<int>(name.length()) };
  int length2{ static_cast<int>(std::ssize(name)) };

  // Don't pass std::string by value, it makes expensive copies, use std::string_view instead. It's ok to return
  // std::string by value in some cases because it supports move semantics.
  // If you return C-style literal, use std::string_view type.

  using namespace std::string_literals;
  auto str = "string"s;

  //   constexpr string has a limited support
  constexpr std::string name2{ "Alex" };
  //   constexpr string_view is supported
  constexpr std::string_view name3{ "Alex" };

  // std::string_view provides a read-only non-owning access to an existing string (C-style, std::string or
  // std::string_view) without copying. It's preferable for read-only strings.
  using namespace std::string_view_literals;
  // C-style string literals exists for the entire program so it's ok to use them in std::string_view init
  std::string_view s{ "Hello, world!" };

  // This is UB, string in init is a temp object and destroyed at the end of the full expression leaving dangling
  // std::string_view
  std::string_view sv1{ "Hello, world!"s };

  auto s2 = "Hello, world!"sv;
  printSV(s2);

  // std::string s31 = s; // implicit conversion is not allowed
  std::string s32 = static_cast<std::string>(s);

  // Modifying a std::string is likely to invalidate all views into that std::string.
  std::string s4{ "Hello, world!" };
  std::string_view sv{ s4 }; // sv is now viewing s
  s4 = "Hello, a!"; // modifies s, which invalidates sv (s is still valid)
  //   std::cout << sv << '\n'; // UB
  sv = s4; // valid again

  sv.remove_prefix(2);
  sv.remove_suffix(2);
  std::cout << sv << '\n';
  sv = s4; // reset

  // A C-style string literal and a std::string are always null-terminated. A std::string_view may or may not be
  // null-terminated.
  return 0;
}