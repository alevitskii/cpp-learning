#include <iostream>
#include <type_traits>

/*
As a general rule, if a function can be evaluated as part of a required constant expression, it should be made
constexpr.

Constexpr functions are implicitly inline, simple forward declaration won't suffice if you use constexpr fun where
compile-time eval is required, but it's possible to get by with forward decl if constexpr fun is used when evaluated
at runtime only.
*/

constexpr double calcCircumference(double radius)
{
  // radius parameter is not constexpr
  constexpr double pi{ 3.14159265359 };
  return 2.0 * pi * radius;
}

// such forward decl is allowed to allow mutually recursive constexpr calls
constexpr int foo(int);

constexpr int goo(int c)
{
  return foo(c); // note that foo is not defined yet
}

constexpr int foo(int b) // okay because foo is still defined before any calls to goo
{
  return b;
}

int getValue(int x) { return x; }

// This function can be evaluated at runtime.
// When evaluated at compile-time, the function will produce a compilation error because the call to getValue(x) cannot
// be resolved at compile-time.
constexpr int foo2(int x)
{
  // Prior to C++23, if no argument values exist that would allow a constexpr function to be evaluated at compile-time,
  // the program is ill-formed
  if (x < 0) return 0; // needed prior to adoption of P2448R1 in C++23
  return getValue(x); // call to non-constexpr function here
}

// consteval must evaluate at compile time (arguments must be constexpr).
// Parameters are still not constexpr (same as for constexpr fun, probably made so for consistency?)
consteval int greaterConsteval(int x, int y) // function is now consteval
{
  return (x > y ? x : y);
}

consteval auto compileTimeEval(auto value) { return value; }

constexpr int greaterConstexpr(int x, int y) // function is constexpr
{
  return (x > y ? x : y);
}

constexpr int someFunction()
{
  if (std::is_constant_evaluated()) // if evaluating in constant context
    // a call to constexpr fun
    return 0;
  else
    // a call to non-constexpr fun
    return 0;
}

int main()
{
  // The call to the constexpr function must have arguments that are known at compile time (e.g. are constant
  // expressions).
  // All statements and expressions within the constexpr function must be evaluatable at compile-time.
  // Here calcCircumference must be evaluated at compile-time because it's in the context when constexpr is required
  // (initialization of a constexpr variable).
  constexpr double circumference{ calcCircumference(3.0) };

  double x{ 5.5 };
  // can be called at runtime too
  double circumference2{ calcCircumference(x) };

  // Doesn't have to be evaluated at compile-time. Compiler may choose when to evaluate it.
  // Compiler may also choose to inline a function call or optimize it away.
  // Compiler may also evaluate non-constexpr functions call with constexpr args at compile-time under "as-if" rule.
  double circumference3{ calcCircumference(4.1) };

  // Compiler is not required to know if a function can be evaluated at compile-time until it's evaluated.
  // It's possible that at runtime it'll run fine, but fail when has to be evaluated at compile-time.
  // It's recommended to always check that constexpr fun can be evaluated at compile-time.
  int b{ foo2(2) };
  // constexpr int b2{ foo2(2) }; // error

  std::cout << "Our circle has circumference " << circumference << "\n";

  constexpr int a{ goo(5) }; // this is the outermost invocation

  constexpr int g{ greaterConsteval(5, 6) };
  std::cout << g << '\n';

  std::cout << greaterConsteval(5, 6) << " is greater!\n";

  // int x{ 5 }; // not constexpr
  // std::cout << greater(x, 6) << " is greater!\n"; // error: consteval functions must evaluate at compile-time

  std::cout << greaterConstexpr(5, 6) << '\n'; // may or may not execute at compile-time
  // This is a hack to make constexpr evaluate at compile-time but still have benefits of constexpr (like usage at
  // runtime)
  std::cout << compileTimeEval(greaterConstexpr(5, 6)) << '\n'; // will execute at compile-time

  // "if consteval" (replacement for "if (std::is_constant_evaluated())") tells if you're inside constant context (100%
  // evaluated at compile-time). It doesn't tell that compiler decided to evaluate something at compile-time (there is
  // no way to find it out currently).

  return 0;
}