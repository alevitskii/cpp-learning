#include <iostream>
#include <iterator>

void print(const char* begin, const char* end)
{
  for (; begin != end; ++begin) { std::cout << *begin; }
}

void printReversed(const char* begin, const char* end)
{
  for (; (begin - 1) != end; --end) { std::cout << *(end - 1); }
}

int main()
{
  const char str[]{ "Hello, world!" };
  print(str, str + std::size(str));
  printReversed(str, str + std::size(str));
  return 0;
}