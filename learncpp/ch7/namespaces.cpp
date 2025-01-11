#include <iostream>

void print() // this print() lives in the global namespace
{
  std::cout << " there\n";
}

namespace Foo {
  void print() // this print() lives in the Foo namespace
  {
    std::cout << "Hello";
  }

  void printHelloThere()
  {
    print(); // calls print() in Foo namespace
    // if print inside Foo wasn't there the compiler would check the contaning namespace (global in this case)
    ::print(); // calls print() in global namespace
  }

  namespace Goo // Goo is a namespace inside the Foo namespace
  {
    int add(int x, int y) { return x + y; }
  } // namespace Goo
} // namespace Foo

namespace Foo::Boo // Boo is a namespace inside the Foo namespace
{
  int add(int x, int y) { return x + y; }
} // namespace Foo::Boo

// Unnamed (anonymous) namespaces give identifiers inside internal linkage.
// Identifiers are accessed as they were in the ns's parent namespace (global in this case).
// Avoid unnamed namespaces in header files.
namespace // unnamed namespace
{
  void doSomething2() // can only be accessed in this file
  {
    std::cout << "v1\n";
  }
} // namespace

namespace V1 // declare a normal namespace named V1
{
  void doSomething() { std::cout << "V1\n"; }
} // namespace V1

// Same as for unnamed, identifiers are accessed as they were in the ns's parent namespace (global in this case).
// inline namespaces don't affect linkage, they are often used for versioning (e.g. by adding/removing inline toggle
// between versions of functions from different namespaces that can be used without qualifier).
// doSomething from V2 can be accesses without qualifier
inline namespace V2 // declare an inline namespace named V2
{
  void doSomething() { std::cout << "V2\n"; }
} // namespace V2

// It's also possible to have inline anonymous namespace (inline namespace {}) but it's probably better to just nest
// unnamed inside inline.
// ids inside anonymous ns will have internal linkage.
inline namespace V3 // declare an inline namespace named V3
{
  namespace // unnamed namespace
  {
    void doSomething3() // has internal linkage
    {
      std::cout << "V3\n";
    }

  } // namespace
} // namespace V3

int main()
{
  // namespaces exist to prevent naming collisions
  Foo::printHelloThere();

  // namespace alias
  namespace Active = Foo::Goo;

  std::cout << Active::add(1, 2) << '\n';
  std::cout << Foo::Boo::add(1, 2) << '\n';

  V1::doSomething(); // calls the V1 version of doSomething()
  V2::doSomething(); // calls the V2 version of doSomething()

  doSomething2(); // from unnamed
  doSomething(); // calls the inline version of doSomething() (which is V2)
  doSomething3(); // calls the inline version of doSomething3() (which is V3)

  return 0;
}