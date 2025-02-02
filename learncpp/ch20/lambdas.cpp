#include <algorithm>
#include <functional>
#include <iostream>
#include <string_view>

/*
Following the best practice of defining things in the smallest scope and closest to first use, lambdas are preferred
over normal functions when we need a trivial, one-off function to pass as an argument to some other function.

Lambdas aren't actually functions, it allows them to avoid the limitation of C++ not supporting nested functions.
Lambdas are special objects called functors (contain overloaded operator()).
*/

int main()
{
  // if return type is not specified then its auto, parameters `()` may be omited
  // [] {}; // a lambda with an omitted return type, no captures, and omitted parameters

  constexpr std::array<std::string_view, 4> arr{ "apple", "banana", "walnut", "lemon" };

  /*
  Can store in a variable and then pass it, or write directly where use it.
  Lambdas don't have a type that we can explicitly use, the compiler generates a unique type just for the lambda.
  */

  // no capture clause
  auto hasNut{ [](std::string_view str) { return str.find("nut") != std::string_view::npos; } };
  // A regular function pointer. Only works with an empty capture clause (empty []).
  bool (*hasNut2)(std::string_view){ [](std::string_view str) { return str.find("nut") != std::string_view::npos; } };
  // Using std::function. The lambda could have a non-empty capture clause
  std::function hasNut3{ // note: pre-C++17, use std::function<double(double, double)> instead
    [](std::string_view str) { return str.find("nut") != std::string_view::npos; }
  };

  auto found{ std::find_if(arr.begin(), arr.end(), hasNut) };

  if (found == arr.end()) {
    std::cout << "No nuts\n";
  } else {
    std::cout << "Found " << *found << '\n';
  }

  auto found2{ std::ranges::find_if(arr, hasNut) };


  /*
  When storing a lambda in a variable, use auto as the variable's type.
  When passing a lambda to a function:
  - if C++20 capable, use auto as the parameter's type;
  - otherwise, use a function with a type template parameter or std::function parameter (or a function pointer if the
  lambda has no captures).

  Lambdas can be generic (some or all parameters auto). When used in the context of a lambda, auto is just a shorthand
  for a template parameter. Whether to use generic lambda or not depends on the operations done by the lambda.
  */

  constexpr std::array months{ // pre-C++17 use std::array<const char*, 12>
    "January",
    "February",
    "March",
    "April",
    "May",
    "June",
    "July",
    "August",
    "September",
    "October",
    "November",
    "December"
  };

  /*
  As of C++17, lambdas are implicitly constexpr if the result satisfies the requirements of a constant expression.
  This generally requires two things:
  - the lambda must either have no captures, or all captures must be constexpr;
  - the functions called by the lambda must be constexpr. Note that many standard library algorithms and math functions
  weren't made constexpr until C++20 or C++23.
  */
  constexpr auto fiveLetterMonths{ std::count_if(
    months.begin(), months.end(), [](std::string_view str) { return str.length() == 5; }) };

  // // // // // // // // // // // // // // // // // // // // // // // // //

  /*
  Lambdas can only access certain kinds of objects that have been defined outside the lambda, including those with
  static storage duration (e.g. global variables and static locals) and constexpr objects.

  When the compiler encounters a lambda definition, it creates a custom object definition for the lambda (functor).
  Each captured variable becomes a data member of the object. At runtime, when the lambda definition is encountered,
  the lambda object is instantiated, and the members of the lambda are initialized at that point.
  */

  // may be actually variable (e.g. input from a user)
  std::string substr{ "nut" };
  /*
  Captures are treated as const by default, to make them non-const use mutable keyword after the params ().
  Note that values of captured variables are persisted across multiple calls to the lambda, but they're still copies.
  To change the outside variable - capture by ref. Note that if outside var is const, captured variable will also be
  const.
  */
  auto hasNut4{ [&substr](std::string_view str) { return str.find(substr) != std::string_view::npos; } };

  /*
  A default capture (also called a capture-default) captures all variables that are mentioned in the lambda.
  To capture all used variables by value, use a capture value of =.
  To capture all used variables by reference, use a capture value of &.

  Be extra careful when you capture variables by reference, especially with a default reference capture. The captured
  variables must outlive the lambda.

  It's possible to define new variables in the lambda-capture.

  We store areas, but the user entered width and height. We need to calculate the area before we can search for it.
  //   auto found{ std::find_if(areas.begin(),
  //     areas.end(),
  //     // Declare a new variable that's visible only to the lambda.
  //     // The type of userArea is automatically deduced to int.
  //     [userArea{ width * height }](int knownArea) { return userArea == knownArea; }) };

  Only initialize variables in the capture if their value is short and their type is obvious. Otherwise it's best to
  define the variable outside of the lambda and capture it.

  There may be issues with unintended copies of mutable lambdas (see
  https://www.learncpp.com/cpp-tutorial/lambda-captures/).
  Standard library functions may copy function objects (reminder: lambdas are function objects). If you want to provide
  lambdas with mutable captured variables, pass them by reference using std::ref (then reference_wrapper object will
  copied, not the lambda). Try to avoid mutable lambdas. Non-mutable lambdas are easier to understand and don't suffer
  from the above issues, as well as more dangerous issues that arise when you add parallel execution.
  */

  return 0;
}