#include <algorithm>
#include <iostream>
#include <map> // std::map
#include <string>
#include <string_view>
#include <vector>

struct StudentGrade
{
  std::string name{};
  char grade{};
};

class GradeMap
{
public:
  char& operator[](std::string_view name);

private:
  std::vector<StudentGrade> m_map{};
};

char& GradeMap::operator[](std::string_view name)
{
  // this is inefficient, we could possibly keep m_map sorted and use binary search
  auto found = std::find_if(m_map.begin(), m_map.end(), [name](const auto& sg) { return name == sg.name; });
  if (found != m_map.end()) {
    return found->grade;
  } else {
    // C++20 emplace_back works for aggregates, use .push_back() + .back() prior C++20
    return m_map.emplace_back(std::string{ name }).grade;
  }
}

int main()
{
  GradeMap grades{};

  grades["Joe"] = 'A';
  grades["Frank"] = 'B';

  std::cout << "Joe has a grade of " << grades["Joe"] << '\n';
  std::cout << "Frank has a grade of " << grades["Frank"] << '\n';

  GradeMap grades2{};

  char& gradeJoe{ grades2["Joe"] }; // does an emplace_back
  gradeJoe = 'A';

  char& gradeFrank{ grades2["Frank"] }; // does a emplace_back
  // WARNING: at this point gradeJoe ref may be invalidated because vector might grow
  gradeFrank = 'B';

  // Prefer using std::map over writing your own implementation.
  std::map<std::string, char> gradesMap{ { "Joe", 'A' }, { "Frank", 'B' } };

  // and assigned
  grades["Susan"] = 'C';
  grades["Tom"] = 'D';

  return 0;
}