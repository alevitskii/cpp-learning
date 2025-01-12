#include <cstdlib> // for std::exit()
#include <exception>
#include <iostream>

// Halts usually shouldn't be used in code, exceptions is a better way to handle errors

void cleanup()
{
  // code here to do any kind of cleanup required
  std::cout << "cleanup!\n";
}

int main()
{
  // Passed functions must take no parameters and return nothing
  std::atexit(cleanup); // note: we use cleanup rather than cleanup() since we're not making a function call to
                        // cleanup() right now
  std::cout << 1 << '\n';
  //   cleanup();

  // std::exit doesn't trigger local variables clean up (and variables of other functions in the stack).
  // std::exit (normal termination) cleans up static variables and does some other misc files cleanup.

  // In multithreaded programs cleaned up static vars may case a crash if one thread calls exit while other threads
  // continue using the vars. Because of that there is sys::quick_exit (+at_quick_exit) which doesn't cleanup static
  // vars (and some other things)

  std::exit(0); // terminate and return status code 0 to operating system

  // The following statements never execute
  std::cout << 2 << '\n';

  // abort is an abnormal termination, no cleanup is performed. assert and static_assert call it implicitly
  std::abort();

  // terminate is usually called implicitly when an exception is never handled, it usually calls abort then
  std::terminate();

  return 0;
}