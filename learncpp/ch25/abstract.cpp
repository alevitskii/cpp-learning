#include <iostream>
#include <string>
#include <string_view>

class Animal // This Animal is an abstract base class because it has a pure virtual function
{
protected:
  std::string m_name{};

public:
  Animal(std::string_view name) : m_name{ name } {}

  const std::string& getName() const { return m_name; }
  virtual std::string_view speak() const = 0; // note that speak is now a pure virtual function

  // Any class with pure virtual functions should also have a virtual destructor. A destructor can be made pure virtual,
  // but must be given a definition so that it can be called when a derived object is destructed.
  virtual ~Animal() = default;
};

// Having the definition is unrelated to being pure virtual. Definition can't be provided inline. Derived classes can
// use this implementation.
std::string_view Animal::speak() const { return "buzz"; }

class Cow : public Animal
{
public:
  Cow(std::string_view name) : Animal(name) {}

  // if we didn't define speak in Cow, Cow would also be an abstract class
  std::string_view speak() const override { return "Moo"; }
};

class Dragonfly : public Animal
{

public:
  Dragonfly(std::string_view name) : Animal{ name } {}

  std::string_view speak() const override // this class is no longer abstract because we defined this function
  {
    return Animal::speak(); // use Animal's default implementation
  }
};

// // // // // // // // // // // // // // // // // // // // // // //

// An interface class, all functions are pure virtual
class IErrorLog
{
public:
  virtual bool openLog(std::string_view filename) = 0;
  virtual bool closeLog() = 0;

  virtual bool writeError(std::string_view errorMessage) = 0;

  virtual ~IErrorLog() {
  } // make a virtual destructor in case we delete an IErrorLog pointer, so the proper derived destructor is called
};

int main()
{
  // can't be instantiated because it's abstract
  // Animal animal{ "animal" };

  Cow cow{ "Betsy" };
  std::cout << cow.getName() << " says " << cow.speak() << '\n';

  Animal& a{ cow };
  std::cout << a.speak(); // resolves to Cow::speak(), prints "Moo"

  Dragonfly dfly{ "Sally" };
  std::cout << dfly.getName() << " says " << dfly.speak() << '\n';

  return 0;
}