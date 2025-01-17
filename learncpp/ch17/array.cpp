#include <array>
#include <iostream>
#include <iterator>

template<typename T, auto N> // (C++20) using auto to deduce type of N. Prior C++20 -- std::size_t
void printElement3(const std::array<T, N>& arr)
{
  std::cout << std::get<3>(arr) << '\n';

  static_assert(N > 3);

  // C++23 P2280: language defect, when passes by ref size is not constexpr, not addressed in clang
  // static_assert(std::size(arr) > 3);

  std::cout << arr[3] << '\n';
}

struct House
{
  int number{};
  int stories{};
  int roomsPerStory{};
};

int main()
{
  // non-const variables and runtime constants cannot be used for the length
  std::array<int, 7> a{}; // Using a literal constant

  constexpr int len{ 8 };
  std::array<int, len> b{}; // Using a constexpr variable

  enum Colors { red, green, blue, max_colors };

  std::array<int, max_colors> c{}; // Using an enumerator

  // accessing data of an empty array is UB
  std::array<int, 0> arr{}; // creates a zero-length std::array
  std::cout << arr.empty(); // true if arr is zero-length

  // std::array is an aggregate
  std::array<int, 6> fibonnaci = { 0, 1, 1, 2, 3, 5 }; // copy-list initialization using braced list
  std::array<int, 5> prime{ 2, 3, 5, 7, 11 }; // list initialization using braced list (preferred)

  std::array<int, 5> a2; // Members default initialized (int elements are left uninitialized)
  std::array<int, 5> b2{}; // Members value initialized (int elements are zero initialized) (preferred)

  // std::array<int, 4> a3{ 1, 2, 3, 4, 5 }; // compile error: too many initializers
  std::array<int, 4> b3{ 1, 2 }; // b[2] and b[3] are value initialized

  const std::array<int, 5> prime2{ 2, 3, 5, 7, 11 };
  // Define as constexpr whenever possible. Otherwise, consider std::vector
  constexpr std::array<int, 5> prime3{ 2, 3, 5, 7, 11 };

  // C++17 CTAD (preferred)
  constexpr std::array a3{ 9.7, 7.31 }; // The type is deduced to std::array<double, 2>

  // C++20 std::to_array, it's more expensive because temp object is created and then copy-init
  constexpr auto myArray1{ std::to_array<int, 5>({ 9, 7, 5, 3, 1 }) }; // Specify type and size
  constexpr auto myArray2{ std::to_array<int>({ 9, 7, 5, 3, 1 }) }; // Specify type only, deduce size
  constexpr auto myArray3{ std::to_array({ 9, 7, 5, 3, 1 }) }; // Deduce type and size

  constexpr std::array<int, 5> prime4{ 2, 3, 5, 7, 11 };
  std::cout << prime4[3]; // print the value of element with index 3 (7)
  // std::cout << prime4[9]; // invalid index (UB)

  // // // // // // // // // // // // // // // // // // //

  // The length and indices of std::array have type size_type, which is always std::size_t

  std::cout << prime4.size() << '|' << std::size(prime4) << '|' << std::ssize(prime4) << '\n';

  std::array arr2{ 9, 7, 5, 3, 1 };
  constexpr int length{ std::size(
    arr2) }; // ok: return value is constexpr std::size_t and can be converted to int, not a narrowing conversion

  // operator[] does no bound checking, at() checks at runtime, std::get check at compile time (index must be constexpr)
  std::cout << std::get<2>(prime); // print the value of element with index 3
  // std::cout << std::get<9>(prime); // invalid index (compile error)

  // // // // // // // // // // // // // // // // //

  std::array arr3{ 1, 2, 3, 4, 5, 6 }; // use CTAD to infer std::array<int, 6>
  printElement3(arr3); // ok: compiler will instantiate passByRef(const std::array<int, 6>& arr)

  std::array arr4{ 1.2, 3.4 }; // use CTAD to infer std::array<double, 5>
  // printElement3(arr4); // compile error in static_assert

  /*
  std::array is not movable.
  Use return by value if:
  - the array isn't huge;
  - the element type is cheap to copy (or move);
  - the code isn't being used in a performance-sensitive context.
  Use out parameter if:
  - the copy is expensive.
  Use std::vector instead.
  */

  constexpr std::array houses{
    House{ 13, 1, 7 },
    House{ 14, 2, 5 },
    House{ 15, 2, 4 },
  };

  std::array<House, 3> houses2{};
  houses2[0] = { 13, 1, 7 };
  houses2[1] = { 14, 2, 5 };
  houses2[2] = { 15, 2, 4 };

  constexpr std::array<House, 3> houses3{ {
    // Note another set of braces, this is an artifact of aggregate initialization.
    // Other standard library container types (that use list constructors) do not require the double braces in these
    // cases.
    { 13, 4, 30 },
    { 14, 3, 10 },
    { 15, 3, 40 },
  } };

  constexpr std::array<int, 5> arr5{ { 1, 2, 3, 4, 5 } };
  // Single braces works too because of brace elision (scalar (single) values, or when initializing with class types or
  // arrays where the type is explicitly named with each element (like with houses above))
  constexpr std::array<int, 5> arr6{ 1, 2, 3, 4, 5 };

  // // // // // // // // // // // // // // // // // // //

  int x{ 1 };
  int y{ 2 };
  int z{ 3 };

  // Can't have array of refs because ref is not an object (array can hold only objects (of any type))
  // std::array<int&, 2> refarr{ x, y }; // compile error: cannot define array of references

  int& ref1{ x };
  int& ref2{ y };
  [[maybe_unused]] std::array valarr{ ref1,
    ref2 }; // ok: this is actually a std::array<int, 2>, not an array of references

  /*
  A workaround is to use std::reference_wrapper:
  - operator= will reseat a std::reference_wrapper (change which object is being referenced);
  - std::reference_wrapper<T> will implicitly convert to T&;
  - the get() member function can be used to get a T&. This is useful when we want to update the value of the object
  being referenced.
  */

  std::array<std::reference_wrapper<int>, 3> arr7{ x, y, z };

  arr7[1].get() = 5; // modify the object in array element 1

  std::cout << arr7[1] << y << '\n'; // show that we modified arr7[1] and y, prints 55 (it can't print a
                                     // std::reference_wrapper<int> so it'll implicitly convert to T&)

  // C++17 CTAD
  std::reference_wrapper ref3{ x };
  auto ref4{ std::reference_wrapper{ x } };

  // C++11 (it's often preferred because it's shorter)
  auto ref{ std::ref(x) }; // C++11, deduces to std::reference_wrapper<int>
  auto cref{ std::cref(x) }; // C++11, deduces to std::reference_wrapper<const int>

  return 0;
}