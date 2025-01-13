#include <string>


std::string& getRef(); // some function that returns a reference

const std::string& getConstRef(); // some function that returns a reference to const

constexpr std::string_view hello{ "Hello" }; // implicitly const

constexpr const std::string_view& getConstRef2() // function is constexpr, returns a const std::string_view&
{
  return hello;
}

int main()
{
  // auto drops top-level const qualifiers
  // const int x; // this const applies to x, so it is top-level
  // int* const ptr; // this const applies to ptr, so it is top-level
  // const int& ref; // this const applies to the object being referenced, so it is low-level
  // const int* ptr; // this const applies to the object being pointed to, so it is low-level

  // auto drops reference
  auto& ref0{ getRef() }; // std::string& (reference dropped, reference reapplied)

  // Reference dropped (low-level const is turned into top-level), then top-level const dropped from result.
  // const std::string& -> const std::string -> std::string.
  auto ref1{ getConstRef() };
  const auto ref2{ getConstRef() }; // const std::string (reference dropped, const dropped, const reapplied)

  auto& ref3{ getConstRef() }; // const std::string& (reference dropped and reapplied, low-level const not dropped)
  const auto& ref4{ getConstRef() }; // const std::string& (reference dropped and reapplied, low-level const not
                                     // dropped, reapplying const is redundant, but it's more clear)

  auto ref5{ getConstRef2() }; // std::string_view (reference dropped and top-level const dropped)
  constexpr auto ref6{ getConstRef2() }; // constexpr const std::string_view (reference dropped and top-level const
                                         // dropped, constexpr applied, implicitly const)

  auto& ref7{ getConstRef2() }; // const std::string_view& (reference reapplied, low-level const not dropped)
  constexpr const auto& ref8{
    getConstRef2()
  }; // constexpr const std::string_view& (reference reapplied, low-level const not dropped, constexpr applied)

  /*
    Type deduction doesn't drop pointers (but it's still better to use auto*).
    There are many different scenarios with type deduction on pointer (+const) check
    https://www.learncpp.com/cpp-tutorial/type-deduction-with-pointers-references-and-const/.

    If you want a const pointer, pointer to const, or const pointer to const, reapply the const qualifier(s) even when
    it's not strictly necessary, as it makes your intent clear and helps prevent mistakes.
  */
  return 0;
}