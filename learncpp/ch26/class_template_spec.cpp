#include <cstdint>
#include <format>
#include <iostream>

/*
In order to use a specialization, the compiler must be able to see the full definition of both the non-specialized class
and the specialized class. If the compiler can only see the definition of the non-specialized class, it will use that
instead of the specialization. For this reason, specialized classes and functions are often defined in a header file
just below the definition of the non-specialized class, so that including a single header includes both the
non-specialized class and any specializations. This ensures the specialization can always be seen whenever the
non-specialized class can also be seen.
*/

// First define our non-specialized class template
template<typename T> class Storage8
{
private:
  T m_array[8];

public:
  void set(int index, const T& value) { m_array[index] = value; }

  const T& get(int index) const { return m_array[index]; }

  void print()
  {
    for (const auto& e : m_array) { std::cout << e << '\n'; }
  }
};

// Now define our specialized class template
template<> // the following is a template class with no templated parameters
class Storage8<bool> // we're specializing Storage8 for bool
{
  // What follows is just standard class implementation details

private:
  std::uint8_t m_data{};

public:
  void set(int index, bool value)
  {
    // Figure out which bit we're setting/unsetting
    // This will put a 1 in the bit we're interested in turning on/off
    auto mask{ 1 << index };

    if (value) // If we're setting a bit
      m_data |= mask; // use bitwise-or to turn that bit on
    else // if we're turning a bit off
      m_data &= ~mask; // bitwise-and the inverse mask to turn that bit off
  }

  bool get(int index)
  {
    // Figure out which bit we're getting
    auto mask{ 1 << index };
    // bitwise-and to get the value of the bit we're interested in
    // Then implicit cast to boolean
    return (m_data & mask);
  }

  void print() { std::cout << std::format("{:#b}\n", m_data); }
};

// This is a specialized member function definition.
// Explicit function specializations are not implicitly inline, so make this inline if put in header file.
// Note that you don't need to specialize the whole Storage8<double>.
template<> void Storage8<double>::print()
{
  std::cout << std::scientific;
  for (const auto& e : m_array) { std::cout << e << '\n'; }
}

// Same example as before
int main()
{
  // Define a Storage8 for integers (instantiates Storage8<T>, where T = int)
  Storage8<int> intStorage;
  for (int count{ 0 }; count < 8; ++count) { intStorage.set(count, count); }
  for (int count{ 0 }; count < 8; ++count) { std::cout << intStorage.get(count) << '\n'; }
  intStorage.print();

  // Define a Storage8 for bool  (instantiates Storage8<bool> specialization)
  Storage8<bool> boolStorage;
  for (int count{ 0 }; count < 8; ++count) { boolStorage.set(count, count & 3); }
  std::cout << std::boolalpha;
  for (int count{ 0 }; count < 8; ++count) { std::cout << boolStorage.get(count) << '\n'; }
  boolStorage.print();

  // Define a Storage8 for double (instantiates Storage8<T>, where T = double, with print specialized)
  Storage8<double> doubleStorage;
  for (int count{ 0 }; count < 8; ++count) { doubleStorage.set(count, count + 0.5); }
  doubleStorage.print();

  return 0;
}
