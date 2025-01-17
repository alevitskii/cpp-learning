#include <iostream>
#include <string_view>
#include <utility>

/*
Static members are global variables that live inside the scope region of the class.
Access static members using the class name and the scope resolution operator (::).
In general, a static class is preferable when you have static data members and/or need access controls. Otherwise,
prefer a namespace.
C++ does not support static constructors. As workaround, we can create a static function that creates and inits an
object which is then copied to the static variable.
*/

class Something
{
public:
  static int s_value; // declare s_value as static

  // if const integral or const enum (compile-time constants), it can be inited inside class definition
  static const int s_value2{ 4 }; // a static const int can be defined and initialized directly

  // C++17 (preferred)
  static inline int s_value3{ 4 }; // a static inline variable can be defined and initialized directly
  // constexpr members are implicitly inline (as of C++17)
  static constexpr double s_value4{ 2.2 }; // ok
  static constexpr std::string_view s_view{
    "Hello"
  }; // this even works for classes that support constexpr initialization

  // Only static members may use type deduction (auto and CTAD)
  // auto m_x{ 5 }; // auto not allowed for non-static members
  // std::pair m_v{ 1, 2.3 }; // CTAD not allowed for non-static members

  static inline auto s_x{ 5 }; // auto allowed for static members
  static inline std::pair s_v{ 1, 2.3 }; // CTAD allowed for static members

  // static member functions have no `this` pointer
  static int getValue() { return s_value5; }; // static member function
  static int getValue2(); // static member function
private:
  static inline int s_value5{ 2 };
};

// note no "static" keyword. If defined in a header, `inline` keyword must be used.
int Something::getValue2() { return s_value5; }

// Because static member variables are essentially global variables, you must explicitly define (and optionally
// initialize) the static member outside of the class, in the global scope.
// If no initializer is provided, static member variables are zero-initialized by default.
int Something::s_value{ 1 }; // define and initialize s_value to 1
// If a class defined in a header, definition of static variable is usually placed in the corresposing cpp. It can also
// be made inline and placed under the class definition in the header (for class templates it's usually the case).

int main()
{
  Something first{};
  Something second{};

  first.s_value = 2;

  std::cout << first.s_value << '\n';
  std::cout << second.s_value << '\n';
  std::cout << Something::s_value << '\n';
  return 0;
}