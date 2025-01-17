#include "Date.h"

// not inline, should be defined in cpp
void Date::print() const // print function definition
{
  std::cout << "Date(" << m_year << ", " << m_month << ", " << m_day << ")\n";
};
