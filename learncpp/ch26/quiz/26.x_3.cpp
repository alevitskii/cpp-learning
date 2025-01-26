#include <iostream>

template<typename T, typename U> class Pair
{
public:
  Pair(const T& first, const U& second) : m_first{ first }, m_second{ second } {}

  T& first() { return m_first; }
  U& second() { return m_second; }
  const T& first() const { return m_first; }
  const U& second() const { return m_second; }

protected:
  T m_first{};
  U m_second{};
};

template<typename T> class StringValuePair : public Pair<std::string, T>
{
public:
  StringValuePair(std::string_view s, const T& v) : Pair<std::string, T>(static_cast<std::string>(s), v) {}
};

int main()
{
  StringValuePair<int> svp{ "Hello", 5 };
  std::cout << "Pair: " << svp.first() << ' ' << svp.second() << '\n';

  return 0;
}