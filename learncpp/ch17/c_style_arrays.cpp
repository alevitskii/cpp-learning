#include <iostream>
#include <iterator> // for std::size and std::ssize

/*
Avoid C-style arrays whenever practical.
Prefer std::string_view for read-only strings (string literal symbolic constants and string parameters).
Prefer std::string for modifiable strings.
Prefer std::array for non-global constexpr arrays.
Prefer std::vector for non-constexpr arrays.
It is okay to use C-style arrays for global constexpr arrays (or constexpr static local). It's because such arrays can
be accessed directly from anywhere, no need to pass them somewhere and have decay.
It's ok to use C-style arrays as parameters to functions or classes that want to handle non-constexpr C-style string
arguments directly (for performance reasons, e.g. to avoid C-style string -> std::string_view conversion)
*/

void printElementZero(
  // length information is lost during decay
  const int arr[]) // treated the same as const int*, this syntax helps distinguish from a pointer to a single integer
{
  std::cout << arr[0];
}

void printArray(const int* begin, const int* end)
{
  for (; begin != end; ++begin) // iterate from begin up to (but excluding) end
  {
    std::cout << *begin << ' '; // dereference our loop variable to get the current element
  }
  std::cout << '\n';
}

int main()
{
  // length must be constant expression, variable-length arrays (VLAs, C99 feature) are not allowed
  int testScore[30]{}; // Defines a C-style array named testScore that contains 30 value-initialized int elements (no
                       // #include required)
  // int testScore2[0]{}; // compile error

  const int arr[]{ 9, 8, 7, 6, 5 };
  int s{ 2 };
  std::cout << arr[s] << '\n'; // okay to use signed index
  unsigned int u{ 2 };
  std::cout << arr[u] << '\n'; // okay to use unsigned index

  // C-style arrays are aggregates
  int fibonnaci[6] = { 0, 1, 1, 2, 3, 5 }; // copy-list initialization using braced list
  int prime[5]{ 2, 3, 5, 7, 11 }; // list initialization using braced list (preferred)

  int arr1[5]; // Members default initialized (int elements are left uninitialized)
  int arr2[5]{}; // Members value initialized (int elements are zero initialized) (preferred)

  // int a[4]{ 1, 2, 3, 4, 5 }; // compile error: too many initializers
  int b[4]{ 1, 2 }; // arr[2] and arr[3] are value initialized

  // CTAD doesn't work because C-style array is not a class template. Can't use auto too.
  // auto squares[5]{ 1, 4, 9, 16, 25 }; // compile error: can't use type deduction on C-style arrays

  // compiler can deduce length
  const int prime1[5]{ 2, 3, 5, 7, 11 }; // prime1 explicitly defined to have length 5
  const int prime2[]{ 2, 3, 5, 7, 11 }; // (preferred) prime2 deduced by compiler to have length 5
  // int bad[]{}; // error: the compiler will deduce this to be a zero-length array, which is disallowed!

  // can be const and constexpr
  constexpr int squares[]{ 1, 4, 9, 16, 25 }; // an array of constexpr int
  const int prime3[]{ 2, 3, 5, 7, 11 }; // an array of const int

  std::cout << sizeof(prime3); // prints 20 (assuming 4 byte ints), no overhead

  std::cout << std::size(prime3) << '\n'; // C++17, returns unsigned integral value 5
  std::cout << std::ssize(prime3) << '\n'; // C++20, returns signed integral value 5

  int arr3[]{ 1, 2, 3 }; // okay: initialization is fine
  arr3[0] = 4; // assignment to individual elements is fine
  // arr3 = { 5, 6, 7 }; // compile error: array assignment not valid
  int src[]{ 5, 6, 7 };
  std::copy(std::begin(src), std::end(src), std::begin(arr3));

  // // // // // // // // // // // // // // // // // // //

  const int prime4[]{ 2, 3, 5, 7, 11 };
  const int squares4[]{ 1, 4, 9, 25, 36, 49, 64, 81 };

  printElementZero(prime4); // prime decays to a pointer
  printElementZero(squares4); // squares decays to a pointer

  // sizeof a decayed array will give the pointer's size

  // // // // // // // // pointer arithmetic // // // // // // // // //

  int x{};
  const int* ptr{ &x }; // assume 4 byte ints
  std::cout << ptr << '\n';
  ++ptr; // ptr = ptr + 1
  std::cout << ptr << '\n'; // techincally UB, but modern implementations allow arithmetic outside of arrays
  --ptr; // ptr = ptr - 1
  std::cout << ptr << '\n';

  const int arr4[]{ 9, 7, 5, 3, 1 };

  const int* ptr2{ arr4 }; // a normal pointer holding the address of element 0
  // operator[] is shorthand for *((ptr) + (n))
  std::cout << ptr2[2]; // subscript ptr to get element 2, prints 5. `2[ptr2]` is also valid

  // Set ptr to point at element 3
  const int* ptr3{ &arr4[3] };
  std::cout << *(ptr3 - 1) << ptr3[-1] << '\n'; // prints 55

  const int* begin{ arr4 }; // begin points to start element
  const int* end{ arr4 + std::size(arr4) }; // end points to one-past-the-end element

  printArray(begin, end);

  return 0;
}