#include <iostream>
#include <string_view>
#include <vector>

class Base
{
protected:
  int m_value{};

public:
  Base(int value) : m_value{ value } {}
  virtual ~Base() = default;

  virtual std::string_view getName() const { return "Base"; }
  int getValue() const { return m_value; }
};

class Derived : public Base
{
public:
  Derived(int value) : Base{ value } {}

  std::string_view getName() const override { return "Derived"; }
};

void printName(const Base base) { std::cout << "I am a " << base.getName() << '\n'; }

int main()
{
  Derived d{ 5 };
  // printName(d); // slicing because passed by value

  std::vector<Base> v{};
  v.push_back(Base{ 5 });
  // v.push_back(Derived{ 6 }); // slicing

  Derived d1{ 5 };
  Derived d2{ 6 };
  Base& b{ d2 };
  // Compiler generate operator= for Base which is non-virtual by default. As a result only base part of d1 gets copied
  // into d2.
  // b = d1; // this line is problematic

  /*
  If the Base class is not designed to be instantiated by itself (e.g. it is just an interface class), slicing can be
  avoided by making the Base class non-copyable (by deleting the Base copy constructor and Base assignment operator).

  You should generally try to avoid slicing.
  */

  return 0;
}