#include <ios> // for std::boolalpha
#include <iostream>

template<typename T> class Pair
{
private:
  T m_first{};
  T m_second{};

public:
  // When we define a member function inside the class definition, the template parameter declaration belonging to the
  // class applies

  // Note that we use pass by const reference, it might be expensive to pass by value.
  // Note that constructor name is Pair, not Pair<T>. Within the scope of a class, the unqualified name of the class is
  // called an "injected class name". In a class template, the injected class name serves as shorthand for the fully
  // templated name.
  Pair(const T& first, const T& second) : m_first{ first }, m_second{ second } {}

  bool isEqual(const Pair<T>& pair);
};

// Any member function templates defined outside the class definition should be defined just below the class definition
// (in the same file).

// When we define a member function outside the class definition, we need to resupply a template parameter declaration,
// note `Pair<T>::isEqual`, not `Pair::isEqual`.
// Note `const Pair& pair`, not `const Pair&<T> pair` (although both are valid). We can do without <T> because of the
// injected class name (we're in the scope of the Pair<T> class template).
// Functions (member and non-member) implicitly instantiated from templates are implicitly inline.
template<typename T> bool Pair<T>::isEqual(const Pair& pair)
{
  return m_first == pair.m_first && m_second == pair.m_second;
}

int main()
{
  // we don't need explicit deduction guides, matching constructor provides necessary information
  Pair p1{ 5, 6 }; // uses CTAD to infer type Pair<int>

  std::cout << std::boolalpha << "isEqual(5, 6): " << p1.isEqual(Pair{ 5, 6 }) << '\n';
  std::cout << std::boolalpha << "isEqual(5, 7): " << p1.isEqual(Pair{ 5, 7 }) << '\n';

  return 0;
}