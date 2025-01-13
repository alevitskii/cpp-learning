#include <iostream>

int g_x{ 5 };

int main()
{
  int x{ 5 }; // x is a normal integer variable

  // References must be initialized. Non-const lvalue ref can only be bound to a modifiable lvalue.
  int& ref{ x }; // ref is an lvalue reference variable that can now be used as an alias for variable x

  std::cout << x << '\n'; // print the value of x (5)
  std::cout << ref << '\n'; // print the value of x via ref (5)

  short y{ 5 };
  double d{ 6.0 };
  // When types don't match, a temp object (rvalue) will be created from conversion/promotion of lvalue type to the ref
  // type.
  // int& invalidRef2{ y }; // invalid: non-const lvalue reference can't bind to rvalue (result of promoting y to int)
  const int& validRef2{ y }; // ok

  /*
    Refs can't be reseated (changed the underlying object they're referencing).
    Refs have the same scope and duration rules that normal variables do.
    References and referents have independent lifetimes:
    - reference can be destroyed before the object (no impact on the object);
    - object can be destroyed before the reference (leaving dangling reference - UB).
    References aren't objects, but there is std::reference_wrapper to make them feel like objects.
  */

  // Const lvalue refs can bind to modifiable lvalues, non-mod lvalues and rvalues.
  // Const references directly bound to temporary objects extend the lifetime of the temporary object (temporaries
  // returned from a function are not eligible for lifetime extension). For class type rvalues, binding a reference
  // to a member will extend the lifetime of the entire object.
  const int z{ 5 }; // z is a non-modifiable lvalue
  const int& ref2{ z }; // okay: ref is a an lvalue reference to a const value
  const double& r1{
    5
  }; // temporary double initialized with value 5, r1 binds to temporary (which has its lifetime extended to match r1)

  // Constexpr references can only be bound to objects with static duration (either globals or static locals)
  [[maybe_unused]] constexpr int& ref3{ g_x }; // ok, can bind to global
  static int s_x{ 6 };
  [[maybe_unused]] constexpr int& ref4{ s_x }; // ok, can bind to static local
  static const int s_x2{ 6 }; // a const int
  [[maybe_unused]] constexpr const int& ref22{ s_x }; // needs both constexpr and const
  int xx{ 6 };
  // [[maybe_unused]] constexpr int& ref5{ xx }; // compile error: can't bind to non-static object

  return 0;
}