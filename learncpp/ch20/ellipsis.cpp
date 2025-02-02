#include <cstdarg> // needed to use ellipsis
#include <iostream>

// The ellipsis must be the last parameter.
// Count is how many additional arguments we're passing.
// Ellipsis doesn't hold type info or the number of arguments passed.
double findAverage(int count, ...)
{
  int sum{ 0 };

  // We access the ellipsis through a va_list, so let's declare one
  std::va_list list;

  // We initialize the va_list using va_start. The first argument is the list to initialize. The second argument is the
  // last non-ellipsis parameter.
  va_start(list, count);

  // Loop through all the ellipsis values
  for (int arg{ 0 }; arg < count; ++arg) {
    // We use va_arg to get values out of our ellipsis. The first argument is the va_list we're using. The second
    // argument is the type of the value.
    sum += va_arg(list, int);
  }

  // Cleanup the va_list when we're done.
  va_end(list);

  return static_cast<double>(sum) / count;
}

// (C++17) Fold expressions. Not sure if it's the right implementation.
template<int N, typename... Args> double findAverage2(Args&&... args)
{
  static_assert(N >= 0, "Must be >= 0");
  if constexpr (N == 0) { return 0; }
  return static_cast<double>((args + ... + 0)) / N;
}

int main()
{
  std::cout << findAverage(5, 1, 2, 3, 4, 5) << '\n';
  std::cout << findAverage(6, 1, 2, 3, 4, 5, 6) << '\n';

  std::cout << findAverage2<6>(5, 1, 2, 3, 4, 5) << '\n';
  std::cout << findAverage2<0>() << '\n';

  // C++17, consider fold expressions https://en.cppreference.com/w/cpp/language/fold

  return 0;
}