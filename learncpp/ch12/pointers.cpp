#include <iostream>

/*
There are some differences between pointers and references:
- With references, the address-of and dereference happens implicitly, with pointers it needs to be done explicitly;
- References must be initialized, pointers are not required to be initialized (but should be);
- References are not objects, pointers are;
- References can not be reseated (changed to reference something else), pointers can change what they are pointing at;
- References must always be bound to an object, pointers can point to nothing;
- References are "safe" (outside of dangling references), pointers are inherently dangerous.
Other than that, refs and pointers behave similarly.
*/

int main()
{
  int x{ 5 };
  std::cout << x << '\n'; // print the value of variable x
  std::cout << &x << '\n'; // print the memory address of variable x

  // Dereferencing operator returns the value of an address (as lvalue)
  std::cout << *(&x) << '\n'; // print the value at the memory address of variable x (parentheses not required, but make
                              // it easier to read)

  int* ptr; // an uninitialized pointer ("wild pointer", holds a garbage address), it's better to always init a pointer
  int* ptr2{}; // a null pointer
  int* ptr22{ nullptr }; // explicitly, dereferencing is UB
  int* ptr3{ &x }; // a pointer initialized with the address of variable x
  *ptr3 = 6; // legal because deref oper returns lvalue

  // Note that & oper doesn't return literal address, it return pointer containing the address (pointer type is derived
  // from the operand)
  std::cout << typeid(&x).name() << '\n'; // print the type of &x

  /*
  Dereferencing an invalid pointer will lead to UB. Any other use of an invalid pointer value (such as incrementing) is
  implementation-defined. Assigning a new value is fine because original value isn't used in this case.

  There is no convenient way to find out if a pointer is dangling of valid, it's better to set unused pointers to
  nullptr, then we can check "if (ptr)".

  NULL (a macro from <cstdref>) and 0 as pointers value should be avoided, use nullptr.

  It's recommended to use references instead of pointers where possible.
  */

  int v{ 5 };

  // If the const is on the left side of the *, the const belongs to the value.
  // If the const is on the right side of the *, the const belongs to the pointer.
  // Can change the value of the underlying object and the value of the pointer
  int* ptr4{ &v }; // points to an "int" but is not const itself, so this is a normal pointer
  // Can't change the value of the underlying object but can change the value of the pointer
  const int* ptr5{ &v }; // points to a "const int" but is not const itself, so this is a pointer to a const value
  // Can change the value of the underlying object but can't change the value of the pointer
  int* const ptr6{ &v }; // points to an "int" and is const itself, so this is a const pointer (to a non-const value)
  // Can't change the value of the underlying object and the value of the pointer
  const int* const ptr7{
    &v
  }; // points to a "const int" and is const itself, so this is a const pointer to a const value

  /*
  Non-const pointer to const value is not allowed.
  Pointer to const can point to const and non-const lvalues but not to rvalues because they don't have an address.

  Prefer pass by reference to pass by address unless you have a specific reason to use pass by address.

  It's possible to have reference of a pointer. For example, if you want to change what pointer is pointing at inside a
  function, you pass the pointer by reference (like int*& refptr). But it's uncommon.
  */
  return 0;
}