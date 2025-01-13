#include <functional> // for std::reference_wrapper
#include <iostream>
#include <optional> // for std::optional (C++17)
#include <string>

// Our function now optionally returns an int value
std::optional<int> doIntDivision(int x, int y)
{
  if (y == 0) return {}; // or return std::nullopt
  return x / y;
}

struct Employee
{
  std::string name{}; // expensive to copy
  int id;
};

// Reference wrapper is a workaround to avoid copying (optional doesn't support refs (as of C++23) and only copies the
// value) another option is to use pointers (`void printEmployeeID(const Employee* e=nullptr)`), but we wouldn't be able
// to pass rvalue and we'd have to use & on the caller site.
// It's better to use funcs overloading (one with "const Employee&" and another without params)
void printEmployeeID(std::optional<std::reference_wrapper<Employee>> e = std::nullopt)
{
  if (e)
    std::cout << "Your ID number is " << e->get().id << ".\n";
  else
    std::cout << "Your ID number is not known.\n";
}

int main()
{
  /*
  Return a std::optional (instead of a sentinel value) for functions that may fail, unless your function needs to return
  additional information about why it failed (C++23, can also use std::expected).
  std::optional has similar to pointers syntax but has value semantics, optional contains the value (not points to),
  assignment copies the value, return by value copies optional (with the value) to the caller.
  */

  std::optional<int> result1{ doIntDivision(20, 5) };
  if (result1) // If the function returned a value (or result1.has_value())
    // Derefing optional without a value is UB
    std::cout << "Result 1: " << *result1 << '\n'; // get the value (or result1.value())
  else
    std::cout << "Result 1: failed\n";

  std::optional<int> result2{ doIntDivision(5, 0) };

  if (result2)
    std::cout << "Result 2: " << *result2 << '\n';
  else
    std::cout << "Result 2: failed\n";

  printEmployeeID(); // we don't know the Employee yet

  Employee e{ "James", 34 };
  printEmployeeID(e); // we know the Employee's ID now

  /*
  Prefer std::optional for optional return types.
  Prefer function overloading for optional function parameters (when possible). Otherwise, use std::optional<T> for
  optional arguments when T would normally be passed by value. Favor const T* when T is expensive to copy.
  */

  return 0;
}