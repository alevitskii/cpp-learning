#include <iostream>
#include <string>
#include <string_view>

/*
When constructing a derived class, the derived class constructor is responsible for determining which base class
constructor is called. If no base class constructor is specified, the default base class constructor will be used. In
that case, if no default base class constructor can be found (or created by default), the compiler will display an
error. The classes are then constructed in order from most base to most derived.
When a derived class is destroyed, each destructor is called in the reverse order of construction.

Constructors can only call constructors from their immediate parent/base class.

Base class  Inherited publicly  Inherited privately Inherited protectedly
Public      Public              Private             Protected
Protected   Protected           Private             Protected
Private     Inaccessible        Inaccessible        Inaccessible

The protected access specifier allows the class the member belongs to, friends, and derived classes to access protected
members, but not the public.

Favor private members over protected members.
Use public inheritance unless you have a specific reason to do otherwise.
*/

class Person
{
private:
  std::string m_name;
  int m_age{};

public:
  Person(std::string_view name = "", int age = 0) : m_name{ name }, m_age{ age } {}

  const std::string& getName() const { return m_name; }
  int getAge() const { return m_age; }
};

// BaseballPlayer publicly inheriting Person
class BaseballPlayer : public Person
{
private:
  double m_battingAverage{};
  int m_homeRuns{};

public:
  BaseballPlayer(std::string_view name = "", int age = 0, double battingAverage = 0.0, int homeRuns = 0)
    : Person{ name, age } // call Person(std::string_view, int) to initialize these fields
      ,
      m_battingAverage{ battingAverage }, m_homeRuns{ homeRuns }
  {}

  double getBattingAverage() const { return m_battingAverage; }
  int getHomeRuns() const { return m_homeRuns; }
};


int main()
{
  BaseballPlayer pedro{ "Pedro Cerrano", 32, 0.342, 42 };

  std::cout << pedro.getName() << '\n';
  std::cout << pedro.getAge() << '\n';
  std::cout << pedro.getBattingAverage() << '\n';
  std::cout << pedro.getHomeRuns() << '\n';
  // Can't access because m_name is a private member of Person
  // std::cout << pedro.m_name << '\n';

  return 0;
}