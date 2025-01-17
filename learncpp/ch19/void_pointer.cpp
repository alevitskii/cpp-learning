#include <iostream>

int main()
{
  int value{ 5 };
  // void pointer can point at any type
  void* voidPtr{ &value };

  // std::cout << *voidPtr << '\n'; // illegal: dereference of void pointer
  int* intPtr{ static_cast<int*>(voidPtr) }; // however, if we cast our void pointer to an int pointer...
  std::cout << *intPtr << '\n'; // then we can dereference the result

  void* ptr{ nullptr }; // ptr is a void pointer that is currently a null pointer

  /*
  Deleting a void pointer will result in UB.
  It is not possible to do pointer arithmetic on a void pointer.
  */
  return 0;
}