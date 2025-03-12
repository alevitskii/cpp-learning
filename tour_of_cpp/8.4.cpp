#include <iostream>


template<typename T>
concept Printable = requires(T t) { std::cout << t; }; // just one operation!

// not needed thanks to constexpr if
/*
void print()
{
  // what we do for no arguments: nothing
}
*/

/*
The strength of variadic templates is that they can accept any arguments you care to give them.
Weaknesses include:
- the recursive implementations can be tricky to get right;
- the type checking of the interface is a possibly elaborate template program;
- the type checking code is ad hoc, rather than defined in the standard;
- the recursive implementations can be surprisingly expensive in compile time and compiler memory requirements.
*/

// A variadic template. `...` is called a parameter pack
template<Printable T, Printable... Tail> void print(T head, Tail... tail)
{
  std::cout << head << ' ';
  if constexpr (sizeof...(tail) > 0) {
    // constexpr if avoids the need to write `print` with no arguments
    print(tail...);
  }
}

// using Fold expression
template<Printable... T> void print2(T&&... args)
{
  (std::cout << ... << args) << '\n'; // print all arguments
}


int main()
{
  using std::operator""s;
  print("Hello!"s, ' ', "World ", 2017);
  print2("Hello!"s, ' ', "World ", 2017);
}
