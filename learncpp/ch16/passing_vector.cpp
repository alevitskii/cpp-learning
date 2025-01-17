#include <iostream>
#include <vector>

// compile error: CTAD can't be used to infer function parameters. But we can use templates
/*
void passByRef(const std::vector& arr)
{
  std::cout << arr[0] << '\n';
}
*/

template<typename T> void passByRef(const std::vector<T>& arr) { std::cout << arr[0] << '\n'; }

// This can support any T that has operator[] (can compile)
template<typename T> void passByRef2(const T& arr) { std::cout << arr[0] << '\n'; }
// or C++20
void passByRef(const auto& arr) { std::cout << arr[0] << '\n'; }

/*
Note that operator[] doesn't do bounds checking. One solution is to assert but it's runtime.
A better solution is to use types that support constexpr arrays (e.g. std::array) when you need to assert on an array's
length. Then you can use static_assert.
*/

int main()
{
  std::vector primes{ 2, 3, 5, 7, 11 };
  passByRef(primes); // ok: compiler will instantiate passByRef(const std::vector<int>&)

  std::vector dbl{ 1.1, 2.2, 3.3 };
  passByRef(dbl); // ok: compiler will instantiate passByRef(const std::vector<double>&)

  return 0;
}