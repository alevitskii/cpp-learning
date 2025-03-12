#include <iterator>
#include <list>
#include <string>
#include <vector>


void advance(std::forward_iterator auto p, int n) // move p n elements forward
{
  while (n--) ++p; // a forward iterator has ++, but not + or +=
}

void advance(std::random_access_iterator auto p, int n) // move p n elements forward
{
  p += n; // a random-access iterator has +=
}

// requrires-expression is a low level way to define requirements, should not be used in ordinary code, only to define
// concepts.
// template<typename Iter>
//   requires requires(Iter p, int i) {
//     p[i];
//     p + i;
//   } // Iter has subscripting and integer addition
// void advance(Iter p, int n) // move p n elements forward
// {
//   p += n;
// }


void user(std::vector<int>::iterator vip, std::list<std::string>::iterator lsp)
{
  advance(vip, 10); // uses the fast advance()
  advance(lsp, 10); // uses the slow advance()
}

int main() {}
