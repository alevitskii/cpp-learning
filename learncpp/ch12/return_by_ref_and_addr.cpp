#include <iostream>
#include <string>


const int& returnByConstReference(const int& ref) { return ref; }

// takes two integers by non-const reference, and returns the greater by reference
int& max(int& x, int& y) { return (x > y) ? x : y; }

std::string& getRef(); // some function that returns a reference


int main()
{
  // case 1: direct binding
  const int& ref1{ 5 }; // extends lifetime (a const reference can extend the lifetime of a temporary)
  std::cout << ref1 << '\n'; // okay

  // The object being returned by reference must exist after the function returns.
  // Lifetime extension doesn't work across function boundaries.
  // case 2: indirect binding
  const int& ref2{ returnByConstReference(5) }; // binds to dangling reference
  // std::cout << ref2 << '\n'; // UB

  /*
  If a function returns a reference, and that reference is used to initialize or assign to a non-reference variable, the
  return value will be copied (as if it had been returned by value).

  Avoid returning references to non-const local static variables. Returning a const ref to a const local static is OK
  (e.g., when init is expensive).

  Returning a const ref to a const global is OK (e.g., to encapsulate access to a global var).

  It's okay to return reference parameters by reference (because reference params are known to the caller and can't
  become dangling after the function).

  It's okay for an rvalue passed by const reference to be returned by const reference (because rvalues are not destroyed
  until the end of the full expression in which they are created).
  */

  // The caller can modify values through the reference
  int a{ 5 };
  int b{ 6 };
  max(a, b) = 7; // sets the greater of a or b to 7, same as b = 7
  std::cout << a << b << '\n';

  /*
  Return by address is similar to return by ref. But returned address can be nullptr.

  Prefer return by reference over return by address unless the ability to return "no object" (using nullptr) is
  important.

  Avoid out-parameters (except in the rare case where no better options exist).
  Prefer pass by reference for non-optional out-parameters.

  It's sometimes acceptable to pass by non-const ref. For example, when doing init of an expensive-to-init object in a
  function (it's cheaper to pass a ref and use the object after the call on the caller site).
  */

  // `auto` drops reference
  auto& ref7{ getRef() }; // std::string& (reference dropped, reference reapplied)

  return 0;
}