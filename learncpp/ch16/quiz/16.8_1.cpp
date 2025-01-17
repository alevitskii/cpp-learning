#include <iostream>
#include <string_view>
#include <vector>


template<typename T> bool isValueInArray(const std::vector<T>& arr, const T& val)
{
  for (const auto& e : arr) {
    if (e == val) { return true; }
  }
  return false;
}

int main()
{
  using namespace std::string_view_literals;

  std::vector names{ "Alex"sv, "Betty"sv, "Caroline"sv, "Dave"sv, "Emily"sv, "Fred"sv, "Greg"sv, "Holly"sv };

  std::cout << "Enter a name: ";
  std::string name{};
  std::cin >> name;

  // This will also work
  // isValueInArray(names, static_cast<std::string_view>(name));
  // Above we rely on CTAD (template type argument is not specified). The compiler doesn't convert to match the template
  // type parameters.

  // The compiler will implicitly convert name to `std::string_view` to match the parameter type (because the template
  // type is now known to the compiler)
  if (isValueInArray<std::string_view>(names, name)) {
    std::cout << name << " was found.\n";
  } else {
    std::cout << name << " was not found.\n";
  }

  return 0;
}