#include <iostream>
#include <string>
#include <string_view>

class Base
{
public:
  std::string_view getName() const { return "Base"; }
};

class Derived : public Base
{
public:
  std::string_view getName() const { return "Derived"; }
};

/*
A virtual function is a special type of member function that, when called, resolves to the most-derived version of the
function for the actual type of the object being referenced or pointed to.

A derived function is considered a match if it has the same signature (name, parameter types, and whether it is const)
and return type as the base version of the function. Such functions are called overrides.

Virtual function resolution only works when a member function is called through a pointer or reference to a class type
object.

Compile-time polymorphism refers to forms of polymorphism that are resolved by the compiler. These include function
overload resolution, as well as template resolution.

Runtime polymorphism refers to forms of polymorphism that are resolved at runtime. This includes virtual function
resolution.

Never call virtual functions from constructors or destructors. The reason is that it can't be properly resolved - either
the object of the derived class is not constructed yet (it'll call base's function) or it has already been destroyed.
*/

class Animal
{
protected:
  std::string m_name{};

  // We're making this constructor protected because we don't want people creating Animal objects directly, but we still
  // want derived classes to be able to use it.
  Animal(std::string_view name) : m_name{ name } {}

public:
  const std::string& getName() const { return m_name; } // we don't need to make it virtual in this case
  virtual std::string_view speak() const { return "???"; } // note virtual

  /*
  Whenever you are dealing with inheritance, you should make any explicit destructors virtual. Without it you will end
  up with leaked memory when Base pointer or ref to derived object is destroyed (only Base's part will be destroyed).

  "A base class destructor should be either public and virtual, or protected and non-virtual" (by Herb Sutter).
  Protected destructor also prevents any use of the base class destructor by the public.
  */
  virtual ~Animal() = default;

  /*
  It's possible to make the assignment operator virtual but it required extra care.
  */
};

class Cat : public Animal
{
public:
  Cat(std::string_view name) : Animal{ name } {}

  /*
  Actually we don't need `virtual` here. If a function is virtual, all matching overrides in derived classes are
  implicitly virtual. It doesn't work the other way around.
  Signature must exactly match the signature of the base class virtual function in order for the derived class function
  to be used.
  */
  virtual std::string_view speak() const { return "Meow"; }
};

/*
If you intend your class to be inherited from, make sure your destructor is virtual and public.
If you do not intend your class to be inherited from, mark your class as final. This will prevent other classes from
inheriting from it in the first place, without imposing any other use restrictions on the class itself.
*/
// `final` means we disallow inheriting this class further
class Dog final : public Animal
{
public:
  Dog(std::string_view name) : Animal{ name } {}

  /*
  The proper way to mark virtual functions in derived classes is with `override` identifier. It implies that it's
  virtual and ensures that it really does override (checks signature).

  Use the virtual keyword on virtual functions in a base class.
  Use the override specifier (but not the virtual keyword) on override functions in derived classes. This includes
  virtual destructors.
  If a member function is both const and an override, the const must be listed first. const override is correct,
  override const is not.

  `final` means we disallow overriding the function in further derived classes
  */
  std::string_view speak() const override final { return "Woof"; }
};

void report(const Animal& animal) { std::cout << animal.getName() << " says " << animal.speak() << '\n'; }

// // // // // // // // // // // // // // // // // // // // // // // // //

/*
If the return type of a virtual function is a pointer or a reference to some class, override functions can return a
pointer or a reference to a derived class. These are called covariant return types. It's an exception to the rule that
return types of the functions must match.
*/

class Base2
{
public:
  // This version of getThis() returns a pointer to a Base class
  virtual Base2* getThis()
  {
    std::cout << "called Base2::getThis()\n";
    return this;
  }
  void printType() { std::cout << "returned a Base2\n"; }
};

class Derived2 : public Base2
{
public:
  // Normally override functions have to return objects of the same type as the base function
  // However, because Derived is derived from Base, it's okay to return Derived* instead of Base*
  Derived2* getThis() override
  {
    std::cout << "called Derived2::getThis()\n";
    return this;
  }
  void printType() { std::cout << "returned a Derived2\n"; }
};


int main()
{
  Derived derived{};
  Base& rBase{ derived };
  // this prints Base. Same if we used pointer instead of ref
  std::cout << "rBase is a " << rBase.getName() << '\n';

  Cat cat{ "Fred" };
  Dog dog{ "Garbo" };

  report(cat);
  report(dog);

  Derived2 d{};
  Base2* b{ &d };
  // C++ can't dynamically select types, so you'll always get the type that matches the actual version of the function
  // being called.
  d.getThis()->printType(); // calls Derived2::getThis(), returns a Derived2*, calls Derived2::printType
  b->getThis()->printType(); // calls Derived2::getThis(), returns a Base2*, calls Base2::printType

  return 0;
}