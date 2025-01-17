#ifndef DATE_H
#define DATE_H

#include <iostream>

/*
Prefer to put your class definitions in a header file with the same name as the class. Trivial member functions (such
as access functions, constructors with empty bodies, etc...) can be defined inside the class definition.

Prefer to define non-trivial member functions in a source file with the same name as the class.

Put any default arguments for member functions inside the class definition.

Template member functions should be defined in headers, beneath the class definition (compiler needs to see their
definition in order to instantiate).

Member functions defined inside the class definition are implicitly inline, and exempt from ODR ("one definition per
program" part).
*/

class Date
{
private:
  int m_year{};
  int m_month{};
  int m_day{};

public:
  Date(int year, int month, int day);

  void print() const;

  int getYear() const { return m_year; }
  int getMonth() const { return m_month; }
  int getDay() const { return m_day; }
};

// can be made inline explicitly
inline Date::Date(int year, int month, int day) : m_year{ year }, m_month{ month }, m_day{ day } {}

#endif
