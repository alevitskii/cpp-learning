#include <cassert>
#include <utility>
#include <vector>

namespace Students {
  /*
  Enumeration's underlying type is implementation-defined. Could be signed integer, causing narrowing conversion
  warnings when non-constexpr enumerators are used as indexes.
  */
  enum Names : unsigned int // explicitly specifies the underlying type is unsigned int
  {
    kenny, // 0
    kyle, // 1
    stan, // 2
    butters, // 3
    cartman, // 4
    max_students // 5
  };
} // namespace Students

enum class StudentNames // now an enum class
{
  kenny, // 0
  kyle, // 1
  stan, // 2
  butters, // 3
  cartman, // 4
  max_students // 5
};

// Overload the unary + operator to convert StudentNames to the underlying type
constexpr auto operator+(StudentNames a) noexcept { return std::to_underlying(a); }

int main()
{
  std::vector testScores{ 78, 94, 66, 77, 14 };

  // should use static_assert if array supports constexpr
  assert(std::size(testScores) == Students::max_students);

  Students::Names name{ Students::stan }; // non-constexpr

  testScores[Students::stan] = 76; // not a sign conversion since constexpr
  testScores[name] = 76; // not a sign conversion since name is unsigned

  testScores[+StudentNames::stan] = 76;
  testScores[static_cast<int>(StudentNames::stan)] = 76;

  return 0;
}