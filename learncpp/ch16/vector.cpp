#include <cstddef>
#include <iostream>
#include <iterator>
#include <vector>

/*
What signed type to use?
- int for not large arrays;
- std::ptrdiff_t for large arrays (define alias "using Index = std::ptrdiff_t;") or (C++23) "Z" suffix (signed
counterpart to std::size_t (probably std::ptrdiff_t), e.g. 0Z).

Getting the length of an array as a signed value:
- (prior C++20) use static_cast to Index (see above);
- (preferred) (C++20) use std::ssize().

Converting the signed loop variable to an unsigned index:
- static_cast;
- use toUZ helper function below;
- use custom view (see SignedArrayView;
https://www.learncpp.com/cpp-tutorial/arrays-loops-and-sign-challenge-solutions/)
- (preferred for indexing) use arr.data() and query C-style array;
- (preferred) avoid array indexing with integral values whenever possible (use range-for and iterators).
*/

struct Foo
{
  // Direct initialization not allowed for member default initializers. This is because of parsing ambiguities (confuses
  // with function declaration)
  // std::vector<int> v1(8); // compile error
  std::vector<int> v{ std::vector<int>(8) }; // ok
};

template<typename T> constexpr std::size_t toUZ(T value)
{
  // make sure T is an integral type
  static_assert(std::is_integral<T>() || std::is_enum<T>());

  return static_cast<std::size_t>(value);
}

// Function template to calculate the average of the values in a std::vector
template<typename T> T calculateAverage(const std::vector<T>& arr)
{
  /*
  Any name that depends on a type containing a template parameter is called a dependent name.
  Dependent names must be prefixed with the keyword "typename" in order to be used as a type.
  */

  // Nested type std::vector<T>::size_type is a dependent name, and must be prefixed with typename to be used as a type.
  using size_type = typename std::vector<T>::size_type;
  // `decltype` returns the type of its parameter, reference needs to be removed first.
  // Here `arr` can be a reference or non-reference type.
  using size_type2 = typename std::remove_reference_t<decltype(arr)>::size_type;

  size_type length{ arr.size() };
  // or std::size_t (in general, it's a reasonable approach)

  T average{ 0 }; // if our array has elements of type T, our average should have type T too
  for (size_type index{ 0 }; index < length; ++index) // iterate through all the elements
    average += arr[index]; // sum up all the elements
  average /= static_cast<int>(length); // divide by count of items (integral in nature)

  return average;
}


int main()
{
  // Value initialization (uses default constructor)
  std::vector<int> empty{}; // vector containing 0 int elements

  // List construction (uses list constructor)
  std::vector<int> primes2{ 2, 3, 5, 7 }; // vector containing 4 int elements with values 2, 3, 5, and 7
  std::vector vowels{ 'a', 'e', 'i', 'o', 'u' }; // vector containing 5 char elements with values 'a', 'e', 'i', 'o',
                                                 // and 'u'.  Uses CTAD (C++17) to deduce element type char (preferred).

  std::vector primes{ 2, 3, 5, 7, 11 }; // hold the first 5 prime numbers (as int)

  // Arrays are contiguous in memory
  std::cout << "An int is " << sizeof(int) << " bytes\n";
  std::cout << &(primes[0]) << '\n';
  std::cout << &(primes[1]) << '\n';
  std::cout << &(primes[2]) << '\n';
  /*
  operator[] does not do any kind of bounds checking be default. An invalid index to operator[] will result in UB

  When constructing a class type object using a initializer list:
  - if the initializer list is empty, the default constructor is preferred over the list constructor;
  - if the initializer list is non-empty, a matching list constructor is preferred over other matching constructors.
  This means which behavior you get depends on whether a list constructor exists.
  When constructing a container (or any type that has a list constructor) with initializers that are not element values,
  use direct initialization.
  */

  std::vector<int> data(10); // vector containing 10 int elements, value-initialized to 0

  // Copy init
  // std::vector<int> v1 = 10; // compile error, 10 is not an initializer list, copy init won't match explicit
  // constructor

  // Direct init
  std::vector<int> v2(10); // 10 not an initializer list, matches explicit single-argument constructor

  // List init
  std::vector<int> v3{ 10 }; // { 10 } interpreted as initializer list, matches list constructor

  // Copy list init
  std::vector<int> v4 = { 10 }; // { 10 } interpreted as initializer list, matches list constructor
  // An alternate syntax for copy list initialization
  std::vector<int> v5({ 10 }); // { 10 } interpreted as initializer list, matches list constructor

  // Default init
  std::vector<int> v6{}; // {} is empty initializer list, matches default constructor
  std::vector<int> v7 = {}; // {} is empty initializer list, matches default constructor

  // A containers const-ness comes from const-ing the container itself, not the elements.
  const std::vector<int> prime{ 2, 3, 5, 7, 11 }; // prime and its elements cannot be modified
  // std::vector cannot be made constexpr. If you need a constexpr array, use std::array

  /*
  Back when C++ containers were designed, it was decided to use unsigned for containers length and indexes. Now it's
  considered a bad decision, because of implicit conversions unsigned <-> signed (which are narrowing) and having to
  static_cast when storing the size in a signed integer.

  size_type is a nested typedef defined in standard library container classes, used as the type for the length (and
  indices, if supported) of the container class.
  size_type defaults to std::size_t, and since this is almost never changed, we can reasonably assume size_type is an
  alias for std::size_t.
  Actually all std containers (except std::array) derive size_type from the allocator they use (std::allocator and
  std::allocator<T>::size_type is defined as std::size_t). Unless a custom allocator is used, it's safe to assume that
  std::size_t is containers' size type.
  Need to fully qualify the underlying type to get the size_type: std::vector<int>::size_type.
  */

  std::vector prime3{ 2, 3, 5, 7, 11 };
  // Unlike string and string_view, container types don't have .length
  std::cout << "length: " << prime3.size() << '\n'; // returns length as type `size_type` (alias for `std::size_t`)
  std::cout << "length: " << std::size(prime3) << '\n'; // for containers just calls prime3.size() (C++17, preferred)
  std::cout << "length: " << std::size("sfasdf") << '\n'; // works for non-decayed C-style arrays

  int length{ static_cast<int>(prime3.size()) }; // static_cast return value to int
  std::cout << "length: " << length;

  int length2{ static_cast<int>(std::ssize(prime3)) }; // static_cast return value to int
  auto length4{ std::ssize(prime3) }; // use auto to deduce signed type, as returned by std::ssize()
  std::cout << "length: "
            << std::ssize(prime3); // C++20, returns length as a large signed integral type (usually ptrdiff_t)

  // std::cout << prime3.at(9); // invalid index (throws std::out_of_range exception)

  constexpr int index3{ 3 }; // constexpr, compiler sees that signed to unsigned can be done safely
  int index4{ 3 }; // indexes can be non-const
  std::size_t index5{ 3 };
  std::cout << prime3[index3]
            << '\n'; // okay: constexpr index implicitly converted to std::size_t, not a narrowing conversion
  std::cout << prime3[3] << '\n'; // okay: same
  std::cout << prime3[index4] << '\n'; // possible warning
  std::cout << prime3.data()[index4] << '\n'; // okay: no sign conversion warnings, .data() returns C-style array
  std::cout << prime3[index5] << '\n'; // ok

  std::vector class1{ 84, 92, 76, 81, 56 };
  std::cout << "The class 1 average is: " << calculateAverage(class1) << '\n'; // calc average of 5 ints

  std::vector class2{ 93.2, 88.6, 64.2, 81.0 };
  std::cout << "The class 2 average is: " << calculateAverage(class2) << '\n'; // calc average of 4 doubles

  /*
  There is a class template specialization vector<bool> that's optimized for memory (it holds a collection of bits, but
  has some overhead because it's a vector).
  It's actually not required by the standard to be optimized. In some cases it doesn't behave like a C++ container. It
  is not required to be contiguous in memory.
  It's better to avoid vector<bool> in favor of:
  - constexpr std::bitset if the number of bits is known at compile-time, it's not huge, and bitset operations meet
  requirements;
  - std::vector<char> for a resizable container of Boolean without space savings;
  - 3rd party implementations, like boost:dynamic_bitset.
  */

  return 0;
}