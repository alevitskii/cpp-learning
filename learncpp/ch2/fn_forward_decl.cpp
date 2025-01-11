/*
The one definition rule (or ODR for short) is a well-known rule in C++. The ODR has three parts:

1. Within a file, each function, variable, type, or template in a given scope can only have one definition. Definitions
occurring in different scopes (e.g. local variables defined inside different functions, or functions defined inside
different namespaces) do not violate this rule.

2. Within a program, each function or variable in a given scope can only have one definition. This rule exists because
programs can have more than one file. Functions and variables not visible to the linker are excluded from this rule.

3. Types, templates, inline functions, and inline variables are allowed to have duplicate definitions in different
files, so long as each definition is identical.
*/

#include <iostream>

// parameter names are optional
int add(int x, int y);

int main()
{
  std::cout << "Sum is: " << add(3, 4) << '\n';
  return 0;
}

int add(int x, int y) { return x + y; }

// Won't link, linker can't find "int add(int x, int y);" definition
/*
int add(int x, int y);

int main() {
  std::cout << "Sum is :" << add(3, 4) << '\n';
  return 0;
}

int add(int x, int y, int z) { return x + y + z; }
*/

// Won't compile, compiler can't find "add(3, 4, 5)" declaration
/*
int add(int x, int y);

int main() {
  std::cout << "Sum is :" << add(3, 4, 5) << '\n';
  return 0;
}

int add(int x, int y, int z) { return x + y + z; }
*/
