#include <iostream>

class Foo
{
private:
  int m_x{};
  int m_y{ 2 };
  int m_z;

public:
  /*
  The compiler sets up the memory allocation for the object prior to the constructor call. The constructor is then
  called on the uninitialized object. Constructors don't create objects.

  The lack of a matching constructor will prevent creation of an object. Aggregates are not allowed to have
  constructors. Constructors must be non-const. Constructors can have default arguments.
  */
  Foo(int x, int y) : m_x{ x }, m_y{ y } // without member initializer list data members are defaulted
  // Note that members are inited in the order of definition, not in the order of initializer list
  {
    std::cout << "Foo(" << x << ", " << y << ") constructed\n";
  }

  /*
  Once the member initializer list has finished executing, the object is considered initialized. Once the function body
  has finished executing, the object is considered constructed.
  Member initializer list should be preferred over assigning values in the body of the constructor (it won't work for
  const or ref member).
  Often the best way to halt the construction (e.g. if an invariant can't be established) is to throw an exception.
  Another option is to utilize a factory function that checks the validity.
  */

  /*
  Below we use delegating constructor, have to hardcode 2, there is no way to access default of m_y. Constructors can
  delegate or initialize, but not both. Another solution is to have default value for "y" parameter: `Foo(int x, int y =
  2)`, to avoid magic number we can create `static constexpr int default_y { 2 };` in private section and then `Foo(int
  x, int y = default_y)`
  */
  Foo(int x) : Foo{ x, 2 } { std::cout << "Foo(" << x << ") constructed\n"; }

  /*
  If a class doesn't have user-defined constuctor, the compiler will generate implicit default constructor.
  Implicit default constructor (or one got from using =default) will first zero-init members and then default init.
  Only create a default constructor when it makes sense.
  */
  Foo() = default; // explicitly defaulted default constructor

  void print() const { std::cout << "Foo(" << m_x << ", " << m_y << ")\n"; }
  void printYZ() const { std::cout << "Foo(" << m_y << ", " << m_z << ")\n"; }
  void printXYZ() const { std::cout << "Foo(" << m_x << ", " << m_y << ", " << m_z << ")\n"; }
};

int main()
{
  Foo foo{ 6, 7 }; // calls Foo(int, int) constructor
  foo.print();
  Foo foo2{ 'a', true }; // will match Foo(int, int) constructor

  const Foo foo3{ 6, 7 }; // despite object's constness, non-const constructor can be called. It's because const takes
                          // effect after an object is constructed (per C++ standard)

  // m_z is left uninited because constuctor doesn't init it
  Foo foo4{ 6 };
  // foo4.printYZ(); // UB

  // m_z is zero-inited because of `Foo() = default;`
  Foo foo5{};
  foo5.printXYZ();

  return 0;
}