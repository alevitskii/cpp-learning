#include <iostream>

/*
In C++, all functions are classified as either non-throwing or potentially throwing. A non-throwing function is one that
promises not to throw exceptions that are visible to the caller. A potentially throwing function may throw exceptions
that are visible to the caller.
To define a function as non-throwing, we can use the noexcept specifier (it's not considered during function
overloading).
If an unhandled exception would exit a noexcept function, std::terminate will be called, stack unwinding may or may not
occur.
It's better not to do anything that can throw exception inside a non-throwing function.

noexcept can take a boolean parameter: noexcept(true) is equal to plain noexcept, noexcept(false) indicates a
potentially throwing function. These parameters are typically only used in template functions to generate
throwing/non-throwing functions based on some parameterized value.

Functions that are implicitly non-throwing:
- destructors.
Functions that are non-throwing by default for implicitly-declared or defaulted functions:
- constructors: default, copy, move;
- assignments: copy, move;
- comparison operators (as of C++20).
However, if any of these functions call (explicitly or implicitly) another function which is potentially throwing, then
the listed function will be treated as potentially throwing as well.
Functions that are potentially throwing (if not implicitly-declared or defaulted):
- normal functions;
- user-defined constructors;
- user-defined operators.

An exception safety guarantee is a contractual guideline about how functions or classes will behave in the event an
exception occurs. There are four levels of exception safety guarantees:
- no guarantee -- there are no guarantees about what will happen if an exception is thrown (e.g. a class may be left in
an unusable state);
- basic guarantee -- if an exception is thrown, no memory will be leaked and the object is still usable, but the program
may be left in a modified state;
- strong guarantee -- if an exception is thrown, no memory will be leaked and the program state will not be changed
(e.g. by rolling back the changes or not letting anything be modified prior to the exception occurrence);
- no throw / no fail guarantee -- the function will always succeed (no-fail) or fail without throwing an exception that
is exposed to the caller (no-throw). noexcept functions provide this level of guarantee.

The standard library's policy is to use noexcept only on functions that must not throw or fail. Functions that are
potentially throwing but do not actually throw exceptions (due to implementation) typically are not marked as noexcept.

Always make move constructors, move assignment, and swap functions noexcept.
Make copy constructors, copy assignment operators, destructor noexcept when you can.
Use noexcept on other functions to express a no-fail or no-throw guarantee.

If you are uncertain whether a function should have a no-fail/no-throw guarantee, err on the side of caution and do not
mark it with noexcept.
*/

class Doomed
{
public:
  ~Doomed() { std::cout << "Doomed destructed\n"; }
};

void thrower()
{
  std::cout << "Throwing exception\n";
  throw 1;
}

void pt()
{
  std::cout << "pt (potentally throwing) called\n";
  // This object will be destroyed during stack unwinding (if it occurs)
  Doomed doomed{};
  thrower();
  std::cout << "This never prints\n";
}

void nt() noexcept
{
  std::cout << "nt (noexcept) called\n";
  // This object will be destroyed during stack unwinding (if it occurs)
  Doomed doomed{};
  thrower();
  std::cout << "this never prints\n";
}

void tester(int c) noexcept
{
  std::cout << "tester (noexcept) case " << c << " called\n";
  try {
    (c == 1) ? pt() : nt();
  } catch (...) {
    std::cout << "tester caught exception\n";
  }
}

void foo() { throw -1; }
void boo() {};
void goo() noexcept {};
struct S
{
};

int main()
{
  std::cout << std::unitbuf; // flush buffer after each insertion
  std::cout << std::boolalpha; // print boolean as true/false
  tester(1);
  std::cout << "Test successful\n\n";
  // tester(2); // terminates
  // std::cout << "Test successful\n";

  // noexcept can be used to tell if the compiler thinks the expression will throw an exception
  constexpr bool b1{ noexcept(5 + 3) }; // true; ints are non-throwing
  constexpr bool b2{ noexcept(foo()) }; // false; foo() throws an exception
  constexpr bool b3{ noexcept(boo()) }; // false; boo() is implicitly noexcept(false)
  constexpr bool b4{ noexcept(goo()) }; // true; goo() is explicitly noexcept(true)
  constexpr bool b5{ noexcept(S{}) }; // true; a struct's default constructor is noexcept by default

  return 0;
}