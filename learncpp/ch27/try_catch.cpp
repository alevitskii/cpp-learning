#include <iostream>
#include <string>

/*
The program will not perform implicit conversions or promotions when matching exceptions with catch blocks. For example,
a char exception will not match with an int catch block. However, casts from a derived class to one of its parent
classes will be performed.

Unwinding the stack (removal of the functions from the call stack) destroys local variables in the functions that
are unwound (which is good, because it ensures their destructors execute). If no matching exception handler is found,
std::terminate() is called, the stack may or may not be unwound.

Exception object being thrown survives stack unwinding because the compiler makes a copy of the exception object to some
piece of unspecified memory (outside of the call stack) reserved for handling exceptions. For this reason exceptions
objects need to be copyable (however, compiler may move instead or elide the copy).

Exception objects should not keep pointers or references to stack-allocated objects because they will be left dangling
in case of stack unwinding.
*/

// A modular square root function
double mySqrt(double x)
{
  // If the user entered a negative number, this is an error condition
  if (x < 0.0) throw "Can not take sqrt of negative number"; // throw exception of type const char*

  return std::sqrt(x);
}

class DummyException // a dummy class that can't be instantiated
{
  DummyException() = delete;
};

int main()
{
  try {
    // Statements that may throw exceptions you want to handle go here
    throw -1; // here's a trivial example
  } catch (double) // no variable name since we don't use the exception itself in the catch block below (to prevent
                   // compiler warnings about unused var)
  {
    // Any exceptions of type double thrown within the above try block get sent here
    std::cerr << "We caught an exception of type double\n";
  } catch (int x) {
    // Any exceptions of type int thrown within the above try block get sent here
    std::cerr << "We caught an int exception with value: " << x << '\n';
  } catch (const std::string&) // catch classes by const reference (we don't want an expensive copy)
  {
    // Any exceptions of type std::string thrown within the above try block get sent here
    std::cerr << "We caught an exception of type std::string\n";
    // throw without a value can be used to rethrow the exact same exception object (no copying or slicing made)
    throw;
#ifndef NDEBUG // if we're in release mode
  } catch (...) { // must go last
    /*
    If your program uses exceptions, consider using a catch-all handler in main, to help ensure orderly behavior if an
    unhandled exception occurs.
    If an exception is caught by the catch-all handler, you should assume the program is now in some indeterminate
    state, perform cleanup immediately, and then terminate.
    */
    std::cerr << "Abnormal termination\n";
  }
#else // in debug mode, compile in a catch that will never be hit (for syntactic reasons, we must have a catch block)
    catch (DummyException) {}
#endif

  // Execution continues here after the exception has been handled by any of the above catch blocks
  std::cout << "Continuing on our merry way\n";

  // // // // // // // // // // // // // // // // // // // // // // // // //

  std::cout << "Enter a number: ";
  double x{};
  std::cin >> x;

  try // Look for exceptions that occur within try block and route to attached catch block(s)
  {
    double d = mySqrt(x);
    std::cout << "The sqrt of " << x << " is " << d << '\n';
  } catch (const char* exception) // catch exceptions of type const char*
  {
    std::cerr << "Error: " << exception << std::endl;
  }

  return 0;
}