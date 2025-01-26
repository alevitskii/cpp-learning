#include <iostream>

/*
A template non-type parameter is a template parameter where the type of the parameter is predefined and is substituted
for a constexpr value passed in as an argument.

A non-type parameter can be any of the following types:
- an integral type;
- an enumeration type;
- a pointer or reference to a class object;
- a pointer or reference to a function;
- a pointer or reference to a class member function;
- std::nullptr_t;
- a floating point type (since C++20).
*/

template<typename T, int size> // size is an integral non-type parameter
class StaticArray
{
private:
  // The non-type parameter controls the size of the array
  T m_array[size]{}; // note that it's allocated statically!

public:
  T* getArray();

  T& operator[](int index) { return m_array[index]; }
};

// Showing how a function for a class with a non-type parameter is defined outside of the class
template<typename T, int size> T* StaticArray<T, size>::getArray() { return m_array; }

int main()
{
  // declare an integer array with room for 12 integers
  StaticArray<int, 12> intArray;

  // Fill it up in order, then print it backwards
  for (int count{ 0 }; count < 12; ++count) intArray[count] = count;

  for (int count{ 11 }; count >= 0; --count) std::cout << intArray[count] << ' ';
  std::cout << '\n';

  // declare a double buffer with room for 4 doubles
  StaticArray<double, 4> doubleArray;

  for (int count{ 0 }; count < 4; ++count) doubleArray[count] = 4.4 + 0.1 * count;

  for (int count{ 0 }; count < 4; ++count) std::cout << doubleArray[count] << ' ';

  return 0;
}