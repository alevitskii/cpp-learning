/*
Headers are useful for collecting forward declarations in one place so we don't need to define them in .cpp files.

Don't rely on transitive includes, include everything you need explicitly.

<> brackets tell preprocessor to search for headers in special include directories
"" tells to search in current directory and, if not found, in the include directories
*/
#include "add.h"
#include <iostream>

int main()
{
  std::cout << "The sum of 3 and 4 is " << add(3, 4) << '\n';
  return 0;
}