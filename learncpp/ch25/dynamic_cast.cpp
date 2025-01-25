#include <iostream>
#include <string>
#include <string_view>

class Base
{
protected:
  int m_value{};

public:
  Base(int value) : m_value{ value } {}

  virtual ~Base() = default;
};

class Derived : public Base
{
protected:
  std::string m_name{};

public:
  Derived(int value, std::string_view name) : Base{ value }, m_name{ name } {}

  const std::string& getName() const { return m_name; }
};

Base* getObject(bool returnDerived)
{
  if (returnDerived)
    return new Derived{ 1, "Apple" };
  else
    return new Base{ 2 };
}

/*
Also note that there are several cases where downcasting using dynamic_cast will not work:
- with protected or private inheritance;
- for classes that do not declare or inherit any virtual functions (and thus don’t have a virtual table);
- in certain cases involving virtual base classes (see
https://learn.microsoft.com/en-us/cpp/cpp/dynamic-cast-operator?view=msvc-170&redirectedfrom=MSDN for an example of some
of these cases, and how to resolve them).

In general, using a virtual function should be preferred over downcasting. However, there are times when downcasting is
the better choice:
- when you can not modify the base class to add a virtual function (e.g. because the base class is part of the standard
library);
- when you need access to something that is derived-class specific (e.g. an access function that only exists in the
derived class);
- when adding a virtual function to your base class doesn't make sense (e.g. there is no appropriate value for the base
class to return). Using a pure virtual function may be an option here if you don't need to instantiate the base class.

dynamic_cast uses run-time type information (RTTI) (feature of C++ that exposes information about an object's data type
at runtime). It has a significant space performance cost, some compilers allow you to turn RTTI off as an optimization
(dynamic_cast won't work).
*/

int main()
{
  Base* b{ getObject(true) };

  Derived* d{ dynamic_cast<Derived*>(b) }; // use dynamic cast to convert Base pointer into Derived pointer

  // when downcasting with pointers dynamic_cast returns nullptr if the casting fails
  // Always ensure your dynamic casts actually succeeded by checking for a null pointer result.
  if (d) // make sure d is not a nullptr
    std::cout << "The name of the Derived is: " << d->getName() << '\n';

  // It's also possible with static_cast but does no runtime checking, thus usage of d2 may be UB.
  // Use static_cast unless you're downcasting, in which case dynamic_cast is usually a better choice.
  Derived* d2{ static_cast<Derived*>(b) };

  // it's also possible to dynamic_cast refs (it throws std::bad_cast if casting fails)
  Derived apple{ 1, "Apple" }; // create an apple
  Base& b2{ apple }; // set base reference to object
  Derived& d3{ dynamic_cast<Derived&>(b2) }; // dynamic cast using a reference instead of a pointer

  delete b;

  return 0;
}