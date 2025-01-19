#include <cassert>
#include <iostream>
#include <ostream>

class IntArray
{
public:
  explicit IntArray(int size) : m_size{ size }
  {
    assert(m_size > 0);
    m_arr = new int[static_cast<std::size_t>(m_size)]{};
  }

  IntArray(const IntArray& arr) : m_size{ arr.m_size }
  {
    m_arr = new int[static_cast<std::size_t>(arr.m_size)]{};
    std::copy_n(arr.m_arr, arr.m_size, m_arr);
  }

  IntArray& operator=(const IntArray& arr)
  {
    if (&arr == this) { return *this; }
    int* temp = new int[static_cast<std::size_t>(arr.m_size)]{};
    std::copy_n(arr.m_arr, arr.m_size, temp);
    delete[] m_arr;
    m_arr = temp;
    m_size = arr.m_size;
    return *this;
  }

  ~IntArray() { delete[] m_arr; }

  int& operator[](int index)
  {
    assert(index >= 0);
    assert(index < m_size);
    return m_arr[index];
  }
  friend std::ostream& operator<<(std::ostream& os, const IntArray& arr);

private:
  int m_size{ 0 };
  int* m_arr{ nullptr };
};

std::ostream& operator<<(std::ostream& os, const IntArray& arr)
{
  for (int i{ 0 }; i < arr.m_size; ++i) { os << arr.m_arr[i] << ' '; }
  return os;
}

IntArray fillArray()
{
  IntArray a(5);

  a[0] = 5;
  a[1] = 8;
  a[2] = 2;
  a[3] = 3;
  a[4] = 6;

  return a;
}

int main()
{
  IntArray a{ fillArray() };

  std::cout << a << '\n';

  auto& ref{ a }; // we're using this reference to avoid compiler self-assignment errors
  a = ref;

  IntArray b(1);
  b = a;

  a[4] = 7;

  std::cout << b << '\n';

  return 0;
}