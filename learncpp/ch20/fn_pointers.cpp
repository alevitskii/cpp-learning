#include <functional>
#include <iostream>

int foo() { return 5; }

int goo() { return 6; }

int hoo(int x) { return x; };

void print(int x) { std::cout << "print(int)\n"; }
void print(int x, int y = 10) { std::cout << "print(int, int)\n"; }

bool ascending(int x, int y) { return x > y; }

void selectionSort(int* array, int size, bool (*comparisonFcn)(int, int));
// this also works but only in fun params, in other cases it's interpreted as a fun forward decl
void selectionSort2(int* array, int size, bool comparisonFcn(int, int));
// can take default
void selectionSort3(int* array, int size, bool (*comparisonFcn)(int, int) = ascending);

using CompareRaw = bool (*)(int, int);
using Compare = std::function<bool(int, int)>;
void selectionSort4(int* array, int size, Compare comp = ascending);


int main()
{
  // pointer to a function returning int and taking no arguments
  int (*fcnPtr)();
  int (*fcnPtr1)(){ &foo };
  fcnPtr1 = &goo;
  // pointer to a function returning int and taking int
  int (*fcnPtr2)(int){ &hoo };

  int (*fcnPtr3)(){ foo }; // okay, foo implicitly converts to function pointer to foo
  // void* vPtr{ foo }; // not okay, though some compilers may allow

  int (*fcnPtr4)(){ nullptr };

  // constant pointer to a function returning int and taking no arguments
  int (*const fcnPtr5)(){ &foo };

  int (*fcnPtr6)(int){ &hoo }; // Initialize fcnPtr with function foo
  (*fcnPtr6)(5); // call function foo(5) through fcnPtr.
  fcnPtr6(5); // call function foo(5) through fcnPtr.

  // Because the resolution happens at runtime, default arguments are not resolved when a function is called through a
  // function pointer.
  // print(1); // ambiguous function call

  // Deconstructed method
  using vnptr = void (*)(int); // define a type alias for a function pointer to a void(int) function
  vnptr pi{ print }; // initialize our function pointer with function print
  pi(1); // call the print(int) function through the function pointer

  // Concise method
  static_cast<void (*)(int)>(print)(1); // call void(int) version of print with argument 1

  // std::function
  std::function<int()> fcnPtr7{ foo };
  std::function fcnPtr8{ foo }; // CTAD
  // (*fcnPtr8)(); // not allowed
  fcnPtr8();

  // type inference
  auto fcnPtr9{ foo };

  return 0;
}