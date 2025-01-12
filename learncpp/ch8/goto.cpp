#include <cmath> // for sqrt() function
#include <iostream>

// goto is better avoided.
// goto is sometimes used for exiting nested loops.
// Labels have function scope, they are visible even before labels' appearance in a function.

void printCats(bool skip)
{
  if (skip) goto end; // jump forward; statement label 'end' is visible here due to it having function scope

  std::cout << "cats\n";
end:; // statement labels must be associated with a statement (we place an empty one: `;`)
}

int main()
{
  double x{};
tryAgain: // this is a statement label
  std::cout << "Enter a non-negative number: ";
  std::cin >> x;

  if (x < 0.0) goto tryAgain; // this is the goto statement

  std::cout << "The square root of " << x << " is " << std::sqrt(x) << '\n';

  //   goto skip; // error: this jump is illegal because...
  //   int y{ 5 }; // this initialized variable is still in scope at statement label 'skip'
  // skip:
  //   y += 3; // what would this even evaluate to if x wasn't initialized?
  return 0;
}