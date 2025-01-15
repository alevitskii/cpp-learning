#include <iostream>


/*
Structs should avoid having constructors, it'll make them non-aggregates.
If a class has no data members, namespace should be preferred.
*/

struct Date
{
  /*
  Member variables and functions can be defined in any order (to allow this the compiler generates declarations for
  members defined inside the class type definition outside the class, leaving only declarations inside the class)
  */

  // Note that members are inited in the order of declaration. Better not use another member for init (as default)
  // before it's declared (UB)
  int year{};
  int month{};
  int day{};

  // Member functions must be declared inside the class type definition and can be defined inside or outside of the
  // class type definition. Members defined inside class type def are implicitly inline (don't violate ODR).
  void print() const // defines a member function named print
  {
    // members (year, month, day) are implicitly accessed through the implicity object (this)
    std::cout << year << '/' << month << '/' << day;
  }

  // Can be overloaded without const, considered distinct. Typically done when the return value needs to differ in
  // constness (rare)
  void print() { std::cout << year << '/' << month << '/' << day; }

  void print(std::string_view prefix) const;

  // Can't be made const because it modifies a member
  void incrementDay() { ++day; }
};

// definition can be placed outside, `const` has to be in def and in decl
void Date::print(std::string_view prefix) const { std::cout << prefix << year << '/' << month << '/' << day; }

int main()
{
  Date today{ 2020, 10, 14 }; // aggregate initialize our struct

  today.day = 16; // member variables accessed using member selection operator (.)
  today.print(); // member functions also accessed using member selection operator (.)

  const Date today2{ 2020, 10, 14 }; // const
  // today2.day += 1; // error
  // today2.incrementDay(); // error
  today2.print(); // can be called because print is declared const

  return 0;
}