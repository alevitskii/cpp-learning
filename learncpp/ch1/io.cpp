#include <iostream> // for std::cout

int main()
{
  int x{ 5 };
  std::cout << "x is equal to: " << x << '\n'; // single quoted (by itself) (conventional)
  std::cout << "Yep." << "\n"; // double quoted (by itself) (unconventional but okay)
  std::cout << "And that's all, folks!\n"; // between double quotes in existing text (conventional)
  // std::endl flushes the buffer, '\n' is preferred over endl when outputting text to the console

  std::cout << "Enter 2 numbers: "; // ask user for a number

  int y{}; // define variable to hold user input (and value-initialize it)
  int z{};
  // Values entered should be separated by whitespace (spaces, tabs, or newlines)
  std::cin >> y >> z; // get number from keyboard and store it
  /*
  std::cin is buffered, we can enter input once and then perform multiple extraction requests on it.

  After extraction converted value is copy-assigned to the variable. Leading whitespace is discarded.

  operator>> then extracts as many consecutive characters as it can, until it encounters either a newline character
  (representing the end of the line of input) or a character that is not valid for the variable being extracted to.

  If extraction fails, variable is set to 0 and subsequent exctraction fails too (assigned 0, no exception is raised).

  If an entered number is too big / too small for a variable to hold, it assigns largest positive / negative
  and fails for the subsequent inputs (assigns 0).
  */

  std::cout << "You entered " << y << " and " << z << '\n';

  return 0;
}
