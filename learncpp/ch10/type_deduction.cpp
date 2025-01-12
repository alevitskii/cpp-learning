#include <string>
#include <string_view>
#include <type_traits>

/*
Use type deduction for your variables when the type of the object doesn’t matter.
Favor an explicit type when you require a specific type that differs from the type of the initializer, or when your
object is used in a context where making the type obvious is useful.
*/

void foo() {}

// auto return type can't be used in functions' forward declarations.
// It's usually better not use return type deduction.
// Type deduction can't be used for function parameter types.

// Let the compiler deduce the return type of unsigned short + char
auto add(unsigned short x, char y) { return x + y; }

// auto needs to be used for trailing return syntax.
// auto doesn't do anything here
std::common_type_t<int, double> compare(int,
  double); // harder to read (where is the name of the function in this mess?)
auto compare(int,
  double) -> std::common_type_t<int, double>; // easier to read (we don't have to read the return type unless we care)

// decltype(x) evaluates to the type of x.
// It's sometimes necessary to use trailing return syntax.
// std::common_type_t<decltype(x), decltype(y)> add(int x,
//   double y); // Compile error: compiler hasn't seen definitions of x and y yet
auto add(int x, double y) -> std::common_type_t<decltype(x), decltype(y)>; // ok

auto someFcn(bool b)
{
  if (b)
    return 5; // return type int
  else
    // We need to convert all return values to the same type or specify exact return type so the values are converted by
    // the compiler
    // return 6.7; // error
    return static_cast<int>(6.7); // ok, but it's better to drop return type deduction
}

int main()
{
  auto d{ 5.0 }; // 5.0 is a double literal, so d will be deduced as a double
  auto i{ 1 + 2 }; // 1 + 2 evaluates to an int, so i will be deduced as an int
  auto x{ i }; // i is an int, so x will be deduced as an int

  auto a{ 1.23f }; // f suffix causes a to be deduced to float
  auto b{ 5u }; // u suffix causes b to be deduced to unsigned int

  // auto c; // The compiler is unable to deduce the type of `c`
  // auto z{}; // The compiler is unable to deduce the type of `f`
  // auto e{ foo() }; // Invalid: `c` can't have incomplete type void

  using namespace std::literals; // easiest way to access the s and sv suffixes

  auto s1{ "goo"s }; // "goo"s is a std::string literal, so `s1` will be deduced as a std::string
  auto s2{ "moo"sv }; // "moo"sv is a std::string_view literal, so `s2` will be deduced as a std::string_view

  constexpr double f{ 3.4 }; // `a` has type const double (constexpr not part of type, const is implicit)

  auto g{ f }; // `b` has type double (const dropped)
  const auto h{ f }; // `c` has type const double (const dropped but reapplied)
  constexpr auto l{ f }; // `d` has type const double (const dropped but implicitly reapplied by constexpr)

  return 0;
}