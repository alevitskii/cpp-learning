#include <iostream>

/*
L-value reference           Can be initialized with     Can modify
Modifiable l-values         Yes                         Yes
Non-modifiable l-values     No                          No
R-values                    No                          No

L-value reference to const  Can be initialized with     Can modify
Modifiable l-values         Yes                         No
Non-modifiable l-values     Yes                         No
R-values                    Yes                         No

R-value reference           Can be initialized with     Can modify
Modifiable l-values         No                          No
Non-modifiable l-values     No                          No
R-values                    Yes                         Yes

R-value reference to const  Can be initialized with     Can modify
Modifiable l-values         No                          No
Non-modifiable l-values     No                          No
R-values                    Yes                         No
*/

void fun(const int& lref) // l-value arguments will select this function
{
  std::cout << "l-value reference to const: " << lref << '\n';
}

void fun(int&& rref) // r-value arguments will select this function
{
  std::cout << "r-value reference: " << rref << '\n';
}

int main()
{
  int&& rref{
    5
  }; // because we're initializing an r-value reference with a literal, a temporary with value 5 is created here
  rref = 10;
  std::cout << rref << '\n';

  int x{ 5 };
  fun(x); // l-value argument calls l-value version of function
  fun(5); // r-value argument calls r-value version of function

  int&& ref{ 5 };
  /*
  Although variable ref has type int&&, when used in an expression it is an lvalue (as are all named variables). The
  type of an object and its value category are independent.
  */
  // This calls `fun(const int&)`, because ref is an lvalue of type int&&. Moreover, it does not even match fun(int&&),
  // as rvalue references can't bind to lvalues.
  fun(ref);

  return 0;
}