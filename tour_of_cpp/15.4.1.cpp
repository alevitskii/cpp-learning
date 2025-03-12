#include <print>
#include <string>
#include <string_view>
#include <variant>

// https://en.cppreference.com/w/cpp/utility/variant/visit

struct Base
{
};
struct Derived : Base
{
};

// helper type for the visitor
template<class... Ts> struct overloads : Ts...
{
  using Ts::operator()...;
};

// the variant to visit
using var_t = std::variant<int, std::string, Derived>;

int main()
{
  const auto visitor = overloads{ [](int i) { std::print("int = {}\n", i); },
    [](std::string_view s) { std::println("string = \"{}\"", s); },
    [](const Base&) { std::println("base"); } };

  const var_t var1 = 42, var2 = "abc", var3 = Derived();

#if (__cpp_lib_variant >= 202306L)
  var1.visit(visitor);
  var2.visit(visitor);
  var3.visit(visitor);
#else
  std::visit(visitor, var1);
  std::visit(visitor, var2);
  std::visit(visitor, var3);
#endif
}
