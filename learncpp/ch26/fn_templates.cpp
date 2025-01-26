#include <iostream>

// Here's our primary template (must come first)
template<typename T> void print(const T& t) { std::cout << t << '\n'; }

// A full specialization of primary template print<T> for type double.
// Full specializations are not implicitly inline, so make this inline if put in header file.
template<> // template parameter declaration containing no template parameters
void print<double>(const double& d) // specialized for type double
{
  std::cout << std::scientific << d << '\n';
}

// can be deleted
template<> void print<char>(const char& c) = delete;

// not that with non-template version you don't need the parameter be const ref like in the specialization
void print(double d) { std::cout << std::scientific << d << '\n'; }


int main()
{
  print(5); // generates print<int> and calls it
  print<>(6.7); // calls specialization
  print(6.7); // calls non-template

  // print('c'); // error

  return 0;
}