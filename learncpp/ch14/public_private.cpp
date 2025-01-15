#include <iostream>
#include <string>
#include <string_view>

/*
Classes should generally make member variables private (or protected), and member functions public.
Structs should generally avoid using access specifiers (all members will default to public).
Class members are private be default, struct member are public be default. Classes inherit privatly by default, structs
- publicly. Other than that, structs are classes.

As a rule of thumb, use a struct when all of the following are true:
- you have a simple collection of data that doesn't benefit from restricting access;
- aggregate initialization is sufficient;
- you have no class invariants, setup needs, or cleanup needs.
Use a class otherwise.

A few examples of where structs might be used: constexpr global program data, a point struct (a simple collection of
int members that don't benefit from being made private), structs used to return a set of data from a function.
*/

class Date // now a class instead of a struct
{
public: // public usually goes first to emphasize the interface
  void print() const { std::cout << m_year << '/' << m_month << '/' << m_day; }

  // Access levels are set per class, not per object. Here we can access private data members of other Date object while
  // being inside a member fun of Date
  void printOther(const Date& other) const { std::cout << other.m_year << '/' << other.m_month << '/' << other.m_day; }

  /*
  If a class has no invariants and requires a lot of access functions, consider using a struct (whose data members are
  public) and providing direct access to members instead.

  Prefer implementing behaviors or actions instead of access functions. For example, instead of a `setAlive(bool)`
  setter, implement a `kill()` and a `revive()` function.

  Only provide access functions in cases where the public would reasonably need to get or set the value of an individual
  member.
  */

  // Getter should be const and return either by value (if inexpensive) or by const lvalue reference (if expensive)
  int getDay() const { return m_day; } // getter for day (accessor)
  void setDay(int day) { m_day = day; } // setter for day (mutator)

  // Return type should match the type of the member to avoid conversions.
  // Can use `auto&` but that obscures the return type.
  // It's ok to return by lvalue ref because it's assumed that a member exists as long as the object exists.
  const std::string& getNote() const { return m_note; }
  void setNote(std::string_view note) { m_note = note; }

private:
  // Class members are private by default, can only be accessed by other members.
  // `m_` prefix can be used for private data members to help distinguish.
  int m_year{};
  int m_month{};
  int m_day{};
  std::string m_note{};

  void print()
  {
    // private members can be accessed in member functions
    std::cout << m_year << '/' << m_month << '/' << m_day;
  }
};

// note: rvalue is returned
Date createDate(std::string_view note)
{
  Date e{};
  e.setNote(note);
  return e;
}

int main()
{
  // Aggregates can have no private or protected non-static data members. Date has some, so it's not an aggregate.
  // Date today{ 2020, 10, 14 }; // compile error: can no longer use aggregate initialization

  // private members can not be accessed by the public
  // today.m_day = 16; // compile error: the m_day member is private
  // today.print(); // compile error: the print() (not const) member function is private

  const Date today2{}; // default inited
  today2.print(); // print() (const) is public
  today2.printOther(Date{});

  // Case 1: okay: use returned reference to member of rvalue class object in same expression
  std::cout << createDate("Frank").getNote();

  // Case 2: bad: save returned reference to member of rvalue class object for use later
  const std::string& ref{
    createDate("Garbo").getNote()
  }; // reference becomes dangling when return value of createDate() is destroyed
  // std::cout << ref; // UB

  // Case 3: okay: copy referenced value to local variable for use later
  std::string val{ createDate("Hans").getNote() }; // makes copy of referenced member
  std::cout << val; // okay: val is independent of referenced member

  /*
  Do not return non-const references to private data members -- this will violate privateness.
  Const member functions can't return non-const references to data members.
  */

  return 0;
}