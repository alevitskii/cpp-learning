#include <algorithm> // for std::copy
#include <cassert> // for assert()
#include <initializer_list> // for std::initializer_list
#include <iostream>

class IntArray
{
private:
  int m_length{};
  int* m_data{};

public:
  IntArray() = default;

  IntArray(int length) : m_length{ length }, m_data{ new int[static_cast<std::size_t>(length)]{} } {}

  IntArray(std::initializer_list<int> list) // allow IntArray to be initialized via list initialization
    : IntArray(static_cast<int>(list.size())) // use delegating constructor to set up initial array
  {
    // Now initialize our array from the list
    std::copy(list.begin(), list.end(), m_data);

    /*
    // In case you need to access elements here is the way (or use a range-based for loop). initializer_list doesn't
    support operator[] for some reason.

    for (std::size_t count{}; count < list.size(); ++count)
    {
            m_data[count] = list.begin()[count];
    }
    */
  }

  ~IntArray()
  {
    delete[] m_data;
    // we don't need to set m_data to null or m_length to 0 here, since the object will be destroyed immediately after
    // this function anyway
  }

  /*
  Note that if you implement a constructor that takes a std::initializer_list, you should ensure you do at least one of
  the following:
  - provide an overloaded list assignment operator;
  - provide a proper deep-copying copy assignment operator;
  - delete the copy assignment operator.
  The reason is this
  ```
  IntArray array{};
  array = { 1, 3, 5, 7, 9, 11 }; // Here's our list assignment statement
  std::cout << array[0] << ' ' // UB
  ```
  will cause UB. During assignment temp IntArray object will be constructed from init list and after that we'll do a
  shallow copy -> temp object is destroyed at the end of the statement and `array` is left with dangling pointer to
  m_data.
  */
  IntArray(const IntArray&) = delete; // to avoid shallow copies
  IntArray& operator=(const IntArray& list) = delete; // to avoid shallow copies

  int& operator[](int index)
  {
    assert(index >= 0 && index < m_length);
    return m_data[index];
  }

  int getLength() const { return m_length; }
};

int main()
{
  IntArray array{ 5, 4, 3, 2, 1 }; // initializer list
  for (int count{ 0 }; count < array.getLength(); ++count) std::cout << array[count] << ' ';

  // List initialization favors matching list constructors over matching non-list constructors. Because of it adding a
  // list constructor to an existing class that did not have one may break existing programs.
  IntArray a1(5); // uses IntArray(int), allocates an array of size 5
  IntArray a2{ 5 }; // uses IntArray<std::initializer_list<int>, allocates array of size 1

  return 0;
}