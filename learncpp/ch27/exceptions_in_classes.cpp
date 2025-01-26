#include <iostream>

/*
Exceptions of a fundamental type can be caught by value since they are cheap to copy.
Exceptions of a class type should be caught by (const) reference to prevent expensive copying and slicing.

If an exception is thrown out of a destructor during stack unwinding, the program will be halted. Never throw exceptions
in destructor.

Exception handling is best used when all of the following are true:
- the error being handled is likely to occur only infrequently;
- the error is serious and execution could not continue otherwise;
- the error cannot be handled at the place where it occurs;
- there isn't a good alternative way to return an error code back to the caller.
*/

class Member
{
public:
  Member() { std::cerr << "Member allocated some resources\n"; }

  ~Member() { std::cerr << "Member cleaned up\n"; }
};

class A
{
private:
  int m_x{};
  Member m_member;

public:
  A(int x) : m_x{ x }
  {
    if (x <= 0) throw 1;
  }

  /*
  A's destructor is not called if exception is thrown in A's constructor, but A's members are destroyed properly.
  This is the reason to use RAII. C++ standard library comes with RAII-compliant classes to manage common resource types
  (std::fstream, smart pointers etc)
  */
  ~A()
  {
    std::cerr << "~A\n"; // should not be called
  }
};


int main()
{
  try {
    A a{ 0 };
  } catch (int) {
    std::cerr << "Oops\n";
  }

  return 0;
}