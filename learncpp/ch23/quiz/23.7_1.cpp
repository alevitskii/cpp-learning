#include <algorithm>
#include <cassert>
#include <initializer_list>
#include <iostream>

class IntArray
{
private:
  int m_length{};
  int* m_data{};

public:
  IntArray() = default;

  IntArray(int length) : m_length{ length }, m_data{ new int[static_cast<std::size_t>(length)]{} } {}

  IntArray(std::initializer_list<int> list) : IntArray(static_cast<int>(list.size()))
  {
    std::copy(list.begin(), list.end(), m_data);
  }

  ~IntArray() { delete[] m_data; }

  int& operator[](int index)
  {
    assert(index >= 0 && index < m_length);
    return m_data[index];
  }

  IntArray& operator=(std::initializer_list<int> list)
  {
    if (m_length == list.size()) {
      std::copy(list.begin(), list.end(), m_data);
      return *this;
    }
    auto* temp = new int[static_cast<std::size_t>(list.size())]{};
    std::copy(list.begin(), list.end(), temp);
    delete[] m_data;
    m_data = temp;
    m_length = list.size();
    return *this;
  }

  int getLength() const { return m_length; }
};

int main()
{
  IntArray array{ 5, 4, 3, 2, 1 }; // initializer list
  for (int count{ 0 }; count < array.getLength(); ++count) std::cout << array[count] << ' ';

  std::cout << '\n';

  array = { 1, 3, 5, 7, 9, 11 };

  for (int count{ 0 }; count < array.getLength(); ++count) std::cout << array[count] << ' ';

  std::cout << '\n';

  return 0;
}