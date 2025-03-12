#include <concepts>
#include <iostream>
#include <iterator>
#include <ranges>
#include <vector>

/*
The concepts specified for a template are used to check arguments at the point of use of the template. They are not used
to check the use of the parameters in the definition of the template
*/

template<typename B>
concept Boolean = requires(B x, B y) {
  { x = true };
  { x = false };
  { x = (x == y) };
  { x = (x != y) };
  { x = !x };
  { x = (x = y) };
};

template<typename T, typename T2 = T>
concept Equality_comparable = requires(T a, T2 b) {
  { a == b } -> Boolean; // compare a T to a T2 with ==
  { a != b } -> Boolean; // compare a T to a T2 with !=
  { b == a } -> Boolean; // compare a T2 to a T with ==
  { b != a } -> Boolean; // compare a T2 to a T with !=
};


static_assert(Equality_comparable<int>); // succeeds
struct S
{
  int a;
};
// static_assert(Equality_comparable<S>); // fails because structs don’t automatically get == and !=

template<typename T, typename U = T>
concept Number = requires(T x, U y) { // Something with arithmetic operations and a zero
  x + y;
  x - y;
  x* y;
  x / y;
  x += y;
  x -= y;
  x *= y;
  x /= y;
  x = x; // copy
  x = 0;
};

template<typename T, typename U = T>
concept Arithmetic = Number<T, U> && Number<U, T>;

template<typename S>
concept Sequence = requires(S a) {
  typename std::ranges::range_value_t<S>; // S must have a value type
  typename std::ranges::iterator_t<S>; // S must have an iterator type
  { a.begin() } -> std::same_as<std::ranges::iterator_t<S>>; // S must have a begin() that returns an iterator
  { a.end() } -> std::same_as<std::ranges::iterator_t<S>>;
  requires std::input_iterator<std::ranges::iterator_t<S>>; // S's iterator must be an input_iterator
  requires std::same_as<std::ranges::range_value_t<S>, std::iter_value_t<S>>;
};

// Simpler alternative
// template<typename S>
// concept Sequence = std::ranges::input_range<S>; // simple to write and general

template<Sequence Seq, Number Num>
  requires Arithmetic<std::ranges::range_value_t<Seq>, Num>
Num sum(Seq s, Num v)
{
  for (const auto& x : s) v += x;
  return v;
}

Number auto some_function(int x) { return 0; }

auto some_function2(int x)
{
  // a bit verbose and not all types can be cheaply copied
  Number auto y = 0;
  return y;
}

int main()
{
  auto ret = sum(std::vector{ 1, 2, 3 }, 0.0);
  //   auto ret2 = sum(std::vector<char*>{ 1, 2, 3 }, 0); // error
  std::cout << ret << '\n';
}
