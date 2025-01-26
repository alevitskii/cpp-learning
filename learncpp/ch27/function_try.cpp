#include <iostream>

/*
Use function try blocks when you need a constructor to handle an exception thrown in the member initializer list.

Function type                   Can resolve exceptions via return statement         Behavior at end of catch block
Constructor                     No, must throw or rethrow                           Implicit rethrow
Destructor                      Yes                                                 Implicit rethrow
Non-value returning function	Yes                                                 Resolve exception
Value-returning function        Yes                                                 Undefined behavior

Avoid letting control reach the end of a function-level catch block. Instead, explicitly throw, rethrow, or return.

Function try blocks are almost exclusively used with constructors. Function try blocks can catch both base and the
current class exceptions. Function try is useful primarily for either logging failures before passing the exception up
the stack, or for changing the type of exception thrown (don't try to cleanup the failed object, referring to members of
the failed object is considered UB).
*/

class A
{
private:
  int m_x;

public:
  A(int x) : m_x{ x }
  {
    if (x <= 0) throw 1; // Exception thrown here
  }
};

class B : public A
{
public:
  B(int x)
  try : A{ x } // note addition of try keyword here
  {
  } catch (...) // note this is at same level of indentation as the function itself
  {
    // Exceptions from member initializer list or from constructor body are caught here

    std::cerr << "Exception caught\n";

    throw; // rethrow the existing exception
  }
};

int main()
{
  try {
    B b{ 0 };
  } catch (int) {
    std::cout << "Oops\n";
  }
}