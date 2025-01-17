#include <string_view>
#include <vector>

int main()
{
  std::vector even{ 2, 4, 6, 8, 10, 12 };
  const std::vector doubles{ 1.2, 3.4, 5.6, 7.8 };

  using namespace std::string_view_literals;
  const std::vector names{ "Alex"sv, "Brad"sv, "Charles"sv, "Dave"sv };

  std::vector twelve{ 12 };
  std::vector<int> twelve2(12);

  return 0;
}