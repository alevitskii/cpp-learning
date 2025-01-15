#include <iostream>

template<typename T, typename U> struct Pair
{
  T first{};
  U second{};
};

struct Point
{
  int first{};
  int second{};
};

template<typename T, typename U> void print(Pair<T, U> p) { std::cout << '[' << p.first << ", " << p.second << ']'; }

template<typename T> void print(T p) // type template parameter will match anything
{
  std::cout << '[' << p.first << ", " << p.second << ']'; // will only compile if type has first and second members
}

int main()
{
  Pair<double, int> p1{ 4.5, 6 };
  print(p1); // matches print(Pair<double, int>)
  print<double, int>(p1); // not preferred

  std::cout << '\n';

  Point p2{ 7, 8 };
  print(p2); // matches print(Point)

  std::cout << '\n';

  return 0;
}