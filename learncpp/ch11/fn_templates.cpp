#include <cmath> // for std::sqrt
#include <iostream>

// If type usage is obvious, it's better to use single capital letter type parameter names.
// If it's not obvious or has specific requirements then a more descriptive name is warranted (e.g. Allocator or
// TAllocator)

template<typename T> // this is the template parameter declaration
T max(T x, T y) // this is the function template definition for max<T>
{
  return (x < y) ? y : x;
}

// This is how the program will look like after instantiations

// A declaration for our function template (we don't need the definition any more).
template<typename T> T max(T x, T y);

// This is specialization (or a function instance).
// The template from which this specialization is produced is called a "primary template"
template<> int max<int>(int x, int y) // the generated function max<int>(int, int)
{
  return (x < y) ? y : x;
}

template<> double max<double>(double x, double y) // the generated function max<double>(double, double)
{
  return (x < y) ? y : x;
}

int max(int x, int y)
{
  std::cout << "called max(int, int)\n";
  return (x < y) ? y : x;
}

// `T` is a type template parameter, `double` is a non-template parameter.
// We don't need to provide names for these parameters since they aren't used.
template<typename T> int someFcn(T, double) { return 5; }

template<typename T> T addSome(T x, int some = 1) { return x + some; }

// Use function template specialization to tell the compiler that addOne(const char*) should emit a compilation error.
// `const char*` will match a string literal
template<> const char* addSome(const char* x, int some) = delete;


// // // // // // // // // // // // // // // // // // // // // // // // // //


// If we specify T or U instead of auto as a return type we may get a narrowing conversion.
// max2(2, 3.5) will produce 3 (?: will convert 2 to 2.0 because it requires non-conditional operands have the same
// type). Then return type `T` (aka int) will result in narrowing conversion.
template<typename T, typename U> auto max2(T x, U y) // ask compiler to figure out what the relevant return type is
{
  return (x < y) ? y : x;
}

// If we need a forward declaration we'll need to use trailing return type suffix (because compiler can't understand
// just auto in forward declaration). It's equivalent to max2. Definition is at the bottom.
template<typename T, typename U> auto max3(T x, U y) -> std::common_type_t<T, U>;

// Add two values with matching types.
template<typename T> auto add(T x, T y) { return x + y; }

// Add two values with non-matching types.
// C++20: we can also use "auto" as a fun parameter type. When it's used the compiler converts the function into a
// template. Each `auto` becomes an independent parameter type.
// This method for creating a function template is called an "abbreviated function template".
auto add(auto x, auto y) { return x + y; }
// Above is equivalent to
// template<typename T, typename U> auto add(T x, U y) { return x + y; }

// Add three values with any type
auto add(auto x, auto y, auto z) { return x + y + z; }


// // // // // // // // // // // // // // // // // // // // // // // // // //


/*
A non-type template parameter is a template parameter with a fixed type that serves as a placeholder for a constexpr
value passed in as a template argument.
A non-type template parameter can be any of the following types:
- An integral type;
- An enumeration type;
- std::nullptr_t;
- A floating point type (since C++20);
- A pointer or reference to an object;
- A pointer or reference to a function;
- A pointer or reference to a member function;
- A literal class type (since C++20).

Function parameters can't be constexpr, thus we can't check it in static_assert during compile-time.
As a workaround (not a good one) we can pass a parameter as a non-type template parameter (std often uses it).
*/

template<double D> // requires C++20 for floating point non-type parameters
double getSqrt()
{
  // this can fail to compile
  static_assert(D >= 0.0, "getSqrt(): D must be non-negative");

  if constexpr (D >= 0) // ignore the constexpr here for this example
    return std::sqrt(D); // strangely, std::sqrt isn't a constexpr function (until C++26)

  return 0.0;
}

template<int N> // int non-type template parameter
void print()
{
  std::cout << N << '\n';
}

// This will cause ambiguity when called for example "print<5>();".
// This is because resolution for fun template params is simpler than for fun parameters (no type conversion).
/*
template<char N> // char non-type template parameter
void print()
{
  std::cout << N << '\n';
}
*/

// C++17, we can use auto.
// This won't cause ambiguity like for templates above because the compiler won't find ambiguous matches (there is only
// one template) and will generate something like this:
// template <> void print<5>() ...
// template <> void print<'c'>() ...
/*
template<auto N> // deduce non-type template parameter from template argument void print()
void print()
{
  std::cout << N << '\n';
}
*/

int main()
{
  // When a function is instantiated due to a function call, it’s called implicit instantiation.
  std::cout << max<int>(1, 2) << '\n'; // instantiates and calls function max<int>(int, int)
  // Arguments conversion will happen here.
  std::cout << max<double>(1, 2) << '\n'; // instantiates and calls function max<double>(double, double)

  // Argument deduction.
  // Here we explicitly tell to use the version generated from the function template.
  std::cout << max<>(1, 2) << '\n';
  // Here we may do a call to a non-template version (if one is defined and it's an exact match, takes precedence) or a
  // call to the function instance. The normal function call syntax is preferred.
  std::cout << max(1, 2) << '\n'; // (preferred)

  someFcn(1, 3.4); // matches someFcn(int, double)
  someFcn(1, 3.4f); // matches someFcn(int, double) -- the float is promoted to a double

  // Syntactically this call is valid and compiler will generate code for this call but semantically this doesn't make
  // sense. Developer should take care of such cases. For example, by disallowing certain template arguments.
  // std::cout << addSome("Hello, world!") << '\n'; // error: this specialization is deleted
  std::cout << addSome(5, 4) << '\n';
  std::cout << addSome(5) << '\n';

  // Note that static local variables in a template will be created for every function instance.
  // The care should be taken if they are non-const.

  // The drawback of templates is the possible code bloat and as a result slow compilation time.

  std::cout << max2(2, 3.5) << '\n'; // defined above
  std::cout << max3(2, 3.5) << '\n'; // forward declared above, defined below

  // Function templates may be overloaded.
  // The rules for determining which of multiple matching function templates should be preferred are called "partial
  // ordering of function templates". Whichever function template is more restrictive/specialized will be preferred.
  // Compiler will issue an ambiguity error if it can't determine which template is more restrictive.

  // Note that the compiler used add<T>(T, T), however it could use add<T, U>(T, U)
  std::cout << add(1.2, 3.4) << '\n'; // instantiates and calls add<double>()
  std::cout << add(5.6, 7) << '\n'; // instantiates and calls add<double, int>()
  std::cout << add(8, 9, 10) << '\n'; // instantiates and calls add<int, int, int>()

  std::cout << getSqrt<5.0>() << '\n';
  // std::cout << getSqrt<-5.0>() << '\n'; // error in static_assert

  // implicit conversion
  print<5>(); // no conversion necessary
  print<'c'>(); // 'c' converted to type int, prints 99

  return 0;
}

// Forward declared above.
template<typename T, typename U> auto max3(T x, U y) -> std::common_type_t<T, U> { return (x < y) ? y : x; }
