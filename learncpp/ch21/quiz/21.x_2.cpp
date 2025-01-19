#include <cstdint>
#include <iostream>
#include <ostream>

class Average
{
public:
  friend std::ostream& operator<<(std::ostream& os, const Average& a);
  Average& operator+=(std::int32_t v)
  {
    m_sum += v;
    ++m_count;
    return *this;
  }

private:
  std::int32_t m_sum{ 0 };
  int m_count{ 0 };

  double average() const { return m_count ? static_cast<double>(m_sum) / m_count : 0; }
};

std::ostream& operator<<(std::ostream& os, const Average& a)
{
  os << a.average();
  return os;
}

int main()
{
  Average avg{};
  std::cout << avg << '\n';

  avg += 4;
  std::cout << avg << '\n'; // 4 / 1 = 4

  avg += 8;
  std::cout << avg << '\n'; // (4 + 8) / 2 = 6

  avg += 24;
  std::cout << avg << '\n'; // (4 + 8 + 24) / 3 = 12

  avg += -10;
  std::cout << avg << '\n'; // (4 + 8 + 24 - 10) / 4 = 6.5

  (avg += 6) += 10; // 2 calls chained together
  std::cout << avg << '\n'; // (4 + 8 + 24 - 10 + 6 + 10) / 6 = 7

  Average copy{ avg };
  std::cout << copy << '\n';

  return 0;
}