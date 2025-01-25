#include <iostream>

/*
The compiler will select the best matching function (using function overload resolution process) from the most-derived
class with at least one function with that name.
*/

class Base
{
public:
  Base() {}

  void identify() const { std::cout << "Base::identify()\n"; }

  friend std::ostream& operator<<(std::ostream& out, const Base&)
  {
    out << "In Base\n";
    return out;
  }

  void print(int) { std::cout << "Base::print(int)\n"; }
  void print(double) { std::cout << "Base::print(double)\n"; }

  void changeAccessLevel() { std::cout << "Base::changeAccessLevel()\n"; }
  void changeAccessLevel(int) { std::cout << "Base::changeAccessLevel(int)\n"; }

  void toDelete() const { std::cout << "Base::toDelete()\n"; }

protected:
  void test() const { std::cout << "Base::test()\n"; }
};

class Derived : public Base
{
public:
  Derived() {}

  // Can change access specifier when overriding
  void test() const { std::cout << "Derived::test()\n"; }

  void identify() const
  {
    std::cout << "Derived::identify()\n";
    Base::identify(); // note call to Base::identify() here
  }

  friend std::ostream& operator<<(std::ostream& out, const Derived& d)
  {
    out << "In Derived\n";
    // static_cast Derived to a Base object, so we call the right version of operator<<
    out << static_cast<const Base&>(d);
    return out;
  }

  using Base::print; // make all Base::print() functions eligible for overload resolution
  void print(double) { std::cout << "Derived::print(double)"; }

  // can delete in derived. Note that we can access it directly from Base or casting Derived to Base&
  void toDelete() const = delete;

private:
  // It will make `changeAccessLevel()` AND changeAccessLevel(int) (you can't choose) inaccessible from Derived
  // object
  using Base::changeAccessLevel; // now it's private
  /*
  Note that changeAccessLevel is still public in Base -- can be accessed by casting to Base&. For the same reason, if a
  Base class has a public virtual function, and the Derived class changes the access specifier to private, the public
  can still access the private Derived function by casting a Derived object to a Base& and calling the virtual function.
  Access controls are not enforced at runtime.
  */
};

int main()
{
  Base base{};
  base.identify();

  Derived derived{};
  derived.identify();

  Derived d{};
  d.print(5); // calls Base::print(int), which is the best matching function visible in Derived. Without `using`
              // Derived::print(double) would be called.

  d.Base::print(2.3); // calls Base version of print(double). Can be useful with multiple inheritance to disambiguate
                      // members of base classes with the same name
  d.print(2.3); // calls Derived version of print(double)

  // d.changeAccessLevel(); // error
  // We cast to a Base& rather than a Base to avoid making a copy of the Base portion of Derived.
  static_cast<Base&>(d).changeAccessLevel(); // can call because of casting

  return 0;
}