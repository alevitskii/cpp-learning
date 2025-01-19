#include <cassert>
#include <iostream>
#include <iterator>
#include <ostream>
#include <string>
#include <string_view>

class MyString
{
public:
  MyString(std::string_view s = {}) : m_str{ s } {}

  friend std::ostream& operator<<(std::ostream& os, const MyString& s);
  std::string_view operator()(int start, int end);

private:
  std::string m_str{};
};

std::ostream& operator<<(std::ostream& os, const MyString& s)
{
  os << s.m_str;
  return os;
}

std::string_view MyString::operator()(int start, int length)
{
  assert(start >= 0);
  assert(start + length <= std::ssize(m_str) && "MyString::operator(int, int): Substring is out of range");
  return std::string_view{ m_str }.substr(
    static_cast<std::string::size_type>(start), static_cast<std::string::size_type>(length));
  // Returning MyString would be inefficient. There would be at most 3 copies: substr, constructor of MyString,
  // returning MyString to the caller. Compiler may optimize some of these.
  // return MyString{ m_str.substr(
  //   static_cast<std::string::size_type>(start), static_cast<std::string::size_type>(length)) };
}

int main()
{
  MyString s{ "Hello, world!" };
  std::cout << s(7, 5) << '\n'; // start at index 7 and return 5 characters

  return 0;
}