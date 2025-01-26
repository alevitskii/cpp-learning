#include "Array.h"
#include <iostream>

/*
Just like with function templates, the compiler will only instantiate a class template if the class template is used in
a translation unit. In order to perform the instantiation, the compiler must see both the full class template definition
(not just a declaration) and the specific template type(s) needed.

There are multiple ways to organize template classes:
1. (preferred) put all of template class code in the header:
  + simplicity;
  - increased compile and linking time;
2. put definitions for template class members into a separate .inl file and include it at the bottom of the header file
3. three-file approach: create a third file which contains all of the instantiated classes like this
-----------------------------------------
// Ensure the full Array template definition can be seen
// clang-format off
#include "Array.h"
#include "Array.cpp" // we're breaking best practices here, but only in this one place
// clang-format on

// #include other .h and .cpp template definitions you need here

template class Array<int>; // Explicitly instantiate template Array<int>
template class Array<double>; // Explicitly instantiate template Array<double>

// instantiate other templates here
-----------------------------------------
Compiler will instantiate templates only once and linker will use them in all other files.
*/

int main()
{
  const int length{ 12 };
  Array<int> intArray{ length };
  Array<double> doubleArray{ length };

  for (int count{ 0 }; count < length; ++count) {
    intArray[count] = count;
    doubleArray[count] = count + 0.5;
  }

  for (int count{ length - 1 }; count >= 0; --count) std::cout << intArray[count] << '\t' << doubleArray[count] << '\n';

  return 0;
}