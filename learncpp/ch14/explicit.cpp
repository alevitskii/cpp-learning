#include <iostream>
#include <string>
#include <string_view>

/*
The following should not be made explicit:
- copy (and move) constructors (as these do not perform conversions).

The following are typically not made explicit:
- default constructors with no parameters (as these are only used to convert {} to a default object, not something we
typically need to restrict);
- constructors that only accept multiple arguments (as these are typically not a candidate for conversions anyway).

However, if you prefer, the above can be marked as explicit to prevent implicit conversions with empty and
multiple-argument lists.

The following should usually be made explicit:
- constructors that take a single argument.

There are some occasions when it does make sense to make a single-argument constructor non-explicit. This can be useful
when all of the following are true:
- the constructed object is semantically equivalent to the argument value;
- the conversion is performant.
*/

class Employee
{
private:
  std::string m_name{};
  int m_id{};

public:
  Employee(std::string_view name) : m_name{ name } {}
  explicit Employee(std::string_view name, int id) : m_name{ name }, m_id{ id } {}

  const std::string& getName() const { return m_name; }
};

void printEmployee(Employee e) // has an Employee parameter
{
  std::cout << e.getName();
}

int main()
{
  /*
  The C++ standard doesn’t have specific rules that tell the compiler how to convert values to (or from) a
  program-defined type.
  Instead, the compiler will look to see if we have defined some function that it can use to perform such a conversion.
  Such a function is called a user-defined conversion.
  A constructor that can be used to perform an implicit conversion is called a converting constructor. By default, all
  constructors are converting constructors.
  */

  // Only one user-defined conversion may be applied.
  // This requires two conversions: C-style string -> string_view -> Employee.
  // printEmployee("Joe"); // error, we're supplying an string literal argument
  using namespace std::literals;
  printEmployee("Joe"sv); // now a std::string_view literal
  printEmployee(Employee{ "Joe" }); // no conversion is required

  Employee e1 = { "Joe" };
  printEmployee(Employee{ "Joe", 1 });
  // Not allowed because constructor is explicit (implicit conversions uses copy initialization or copy list
  // initialization).
  // printEmployee({ "Joe"sv, 1 }); // error
  // Employee e2 = { "Joe", 1 }; // error

  // Explicit allows direct initialization, note that static_cast return object that is direct inited.
  Employee e3("Joe", 1);
  // Explicit also affects implicit conversion in return by value.

  return 0;
}