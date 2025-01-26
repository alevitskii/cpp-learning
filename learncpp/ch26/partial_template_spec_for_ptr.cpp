#include <iostream>
#include <memory>
#include <type_traits> // for std::is_pointer_v and std::is_null_pointer_v

template<typename T> class Storage
{
  // Make sure T isn't a pointer or a std::nullptr_t (note that nullptr doesn't match T*, that's why we check it
  // separately).
  // Guess `!std::is_pointer_v<T>` is no longer needed because we have a specialization for pointers below.
  static_assert(!std::is_pointer_v<T> && !std::is_null_pointer_v<T>, "Storage<T*> and Storage<nullptr> disallowed");

private:
  T m_value{};

public:
  Storage(T value) : m_value{ value } {}

  void print() { std::cout << m_value << '\n'; }
};

template<typename T> class Storage<T*>
{
private:
  std::unique_ptr<T> m_value{}; // use std::unique_ptr to automatically deallocate when Storage is destroyed

public:
  Storage(T* value) : m_value{ std::make_unique<T>(value ? *value : 0) } // or throw exception when !value
  {}

  void print()
  {
    if (m_value) std::cout << *m_value << '\n';
  }
};

int main()
{
  double d{ 1.2 };

  Storage s1{ d }; // ok
  s1.print();

  Storage s2{ &d }; // ok, copies d on heap
  s2.print();

  // Storage s3{ nullptr }; // error

  return 0;
}