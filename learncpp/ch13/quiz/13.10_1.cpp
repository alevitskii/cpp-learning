#include <iostream>

struct Stats
{
  int watched{};
  double clicked_pct{};
  double avg_earn_per_click{};
};

void printRevenue(const Stats& s)
{
  std::cout << "watched: " << s.watched << '\n';
  std::cout << "clicked (%): " << s.clicked_pct << '\n';
  std::cout << "avg earnings per click: " << s.avg_earn_per_click << '\n';
  std::cout << "revenue: " << s.watched * (s.clicked_pct / 100) * s.avg_earn_per_click << '\n';
}

int main()
{
  Stats s{};
  std::cin >> s.watched;
  std::cin >> s.clicked_pct;
  std::cin >> s.avg_earn_per_click;
  printRevenue(s);
  return 0;
}