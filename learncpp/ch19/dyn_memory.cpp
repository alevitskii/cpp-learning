#include <cstddef>
#include <iostream>
#include <new>

int main()
{
  // int* ptr1{ new int(5) }; // use direct initialization
  int* ptr2{ new int{ 6 } }; // use uniform initialization
  delete ptr2; // return the memory pointed to by ptr to the operating system
  // Set deleted pointers to nullptr unless they are going out of scope immediately afterward. deref deleted (dangling)
  // pointer is UB.
  ptr2 = nullptr; // set ptr to be a null pointer

  // new may throw bad_alloc, std::nothrow prevents it
  int* value{ new (std::nothrow) int{} }; // ask for an integer's worth of memory
  if (!value) // handle case where new returned nullptr
  {
    // Do error handling here
    std::cerr << "Could not allocate memory\n";
  }

  /*
  Deleting a null pointer is okay, and does nothing. There is no need to conditionalize your delete statements.
  Deleting a pointer pointing not at dynamic memory (except if it's nullptr) is not allowed.
  Avoid memory leaks, when address of the allocated memory is lost.
  */

  // // // // // // // // // // // // // // // // // // // // // // //

  // length doesn't have to be constexpr
  int length{ 5 };
  // can use auto instead of typing int twice
  auto* array{ new int[length]{ 9, 7, 5, 3, 1 } }; // initialize a dynamic array since C++11
  delete[] array; // use array delete to deallocate array
  array = nullptr; // not necessary since array ptr is going out of scope soon
}