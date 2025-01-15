#include <iostream>

/*
Structs that are owners should have data members that are owners.
Non-owning structs may result in dangling members (when a member is destroyed before the struct is).
The size of the struct is at least == sum of the sizes of its members. It can be more because of added padding.
It's better to define struct members in decresing order of size (compiler is not allowed to reorder).
No private or protected non-static data members are allowed in aggregates.
*/

struct Employee
{
  // Providing a value for non-static member is called non-static member initialization.
  // The initialization value is called a default member initializer.
  int id{};
  int age{};
  double wage{ 76000.0 };
  double whatever; // (bad) we should always provide a default value
};

struct Company
{
  int numberOfEmployees{};
  Employee CEO{};
};

struct Company2
{
  struct Employee // accessed via Company2::Employee
  {
    int id{};
    int age{};
    double wage{};
  };

  int numberOfEmployees{};
  Employee CEO{}; // Employee is a struct within the Company2 struct
};

void printEmployee(const Employee& employee) // note pass by reference here
{
  std::cout << "ID:   " << employee.id << '\n';
  std::cout << "Age:  " << employee.age << '\n';
  std::cout << "Wage: " << employee.wage << '\n';
}


Employee getEmptyEmployee()
{
  // return Employee{}; // unnamed Employee object
  return {}; // value-initialize all members
}

int main()
{
  Employee joe0; // joe0.whatever is undefined (bad)
  // Value initialization (with empty braces) is preferred over default init (with no braces).
  // Note that for non-aggregates there is a case where default init can be more efficient.
  Employee joe1{}; // joe1.whatever is 0.0
  // If the number of initialization values is fewer than the number of members:
  // - if the member has a default member initializer, that is used;
  // - the member is copy-initialized from an empty initializer list (in most cases, it's value-initialization).
  Employee joe2{ 2, 28 }; // (preferred), joe.whatever will be value-initialized to 0.0
  Employee joe3 = { 2, 28 }; // (not preferred) copy-list initialization using braced list
  Employee joe4(2, 28); // direct initialization using parenthesized list (C++20), not preferred for now because
                        // doesn't work with aggregates that utilize brace elision (like std::array)
  // designated initializers, helpful when a new member is added to existing struct and not at the end
  Employee joe5{ .id = 2, .age = 28 };
  Employee joe6{ .id = 2, .whatever = 28.0 };
  Employee joe7{ .id{ 2 }, .age{ 28 } }; // ignore "Braces around scalar initializer"
  Employee joe8{ .age = 28, .id = 3 }; // error, must be declaration order
  // std::cout << joe1.whatever << '\n';
  // std::cout << joe1.wage << '\n';

  Employee joe9{ 1, 32, 60000.0 };
  joe9 = { joe9.id, 33, 66000.0 };
  // Without ".id = joe9.id" joe9 would get 0 as an id
  joe9 = { .id = joe9.id, .age = 34, .wage = 70000.0 };
  std::cout << joe9.id << '\n';

  Employee joe10{ 1, 2, 3 };

  Employee x = joe10; // copy-initialization
  Employee y(joe10); // direct-initialization
  Employee z{ joe10 }; // direct-list-initialization

  printEmployee(joe10);
  printEmployee(Employee{ 14, 32, 24.15 }); // preferred over type deduction
  printEmployee({ 14, 32, 24.15 }); // type deduced from parameter

  Employee* ptr{ &joe10 };
  // -> can be chained and mixed with . operator
  std::cout << ptr->id << '\n'; // use -> to select member from pointer to object, == (*ptr).id

  const Employee joe11{};

  return 0;
}