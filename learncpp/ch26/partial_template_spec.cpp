#include <iostream>

template<typename T, int size> // size is the expression parameter
class StaticArray2
{
private:
  // The expression parameter controls the size of the array
  T m_array[size]{};

public:
  T* getArray() { return m_array; }

  const T& operator[](int index) const { return m_array[index]; }
  T& operator[](int index) { return m_array[index]; }
};

// non-member function template
template<typename T, int size> void print2(const StaticArray2<T, size>& array)
{
  for (int count{ 0 }; count < size; ++count) std::cout << array[count] << ' ';
}

// Note that it's not a partially specialized functions (only class templates are allowed to be partially specialized),
// it's a non-specialized fun template with partially specialized class as a parameter.
// Overload of print() function for partially specialized StaticArray<char, size>
template<int size> void print2(const StaticArray2<char, size>& array)
{
  for (int count{ 0 }; count < size; ++count) std::cout << array[count];
}

// // // // // // // // // // // // // // // // // // // // // // //

/*
Given that only classes can be partially specialized, how to deal with member functions?
1. We can partially specialized the whole class but it may lead to duplicated code;
2. We can use inheritance.
*/

template<typename T, int size> class StaticArray_Base
{
protected:
  T m_array[size]{};

public:
  T* getArray() { return m_array; }

  const T& operator[](int index) const { return m_array[index]; }
  T& operator[](int index) { return m_array[index]; }

  void print() const
  {
    for (int i{ 0 }; i < size; ++i) std::cout << m_array[i] << ' ';
    std::cout << '\n';
  }

  // Don't forget a virtual destructor if you're going to use virtual function resolution
};

template<typename T, int size> class StaticArray : public StaticArray_Base<T, size>
{
};

template<int size> class StaticArray<double, size> : public StaticArray_Base<double, size>
{
private:
  // using StaticArray_Base<double, size>::m_array;

public:
  void print() const
  {
    for (int i{ 0 }; i < size; ++i) std::cout << std::scientific << this->m_array[i] << ' ';
    // note: The this-> prefix in the above line is needed. We can also have using declaration above instead.
    // See https://stackoverflow.com/a/6592617 or https://isocpp.org/wiki/faq/templates#nondependent-name-lookup-members
    // for more info on why.
    std::cout << '\n';
  }
};

int main()
{
  // Declare an char array of size 14
  StaticArray2<char, 14> char14{};

  // Copy some data into it
  constexpr std::string_view hello14{ "Hello, world!" };
  std::copy_n(hello14.begin(), hello14.size(), char14.getArray());

  // Print the array
  print2(char14);

  std::cout << ' ';

  // Now declare an char array of size 12
  StaticArray2<char, 12> char12{};

  // Copy some data into it
  constexpr std::string_view hello12{ "Hello, mom!" };
  std::copy_n(hello12.begin(), hello12.size(), char12.getArray());

  // Print the array
  print2(char12);

  // // // // // // // // // // // // // // // // // // // // // // //

  // declare an integer array with room for 6 integers
  StaticArray<int, 6> intArray{};

  // Fill it up in order, then print it
  for (int count{ 0 }; count < 6; ++count) intArray[count] = count;

  intArray.print();

  // declare a double buffer with room for 4 doubles
  StaticArray<double, 4> doubleArray{};

  for (int count{ 0 }; count < 4; ++count) doubleArray[count] = (4.0 + 0.1 * count);

  doubleArray.print();

  return 0;
}