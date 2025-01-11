#include <iostream>
/*
Static local vars that are zero init or init to constexpr can be init at program start.
Static local vars that don't have initializer or init to non-constexpr are zero-init at program start.
Static local vars that are init to non-constexpr are reinit the first time the variable definition is encountered. The
definition is skipped on subsequent calls

It's recommended to init static local var.
Static local vars are usually prefixed with s_.
Static local vars have a block scope but lifetime of global vars.

They are often used to avoid expensive init each time when a function is called.
They can also be made const or constexpr.
Non-const local vars should generally be avoided. If used, ensure the variable never needs to be reset, and isn’t used
to alter program flow.
*/
void incrementAndPrint()
{
  static int s_value{ 1 }; // static duration via static keyword. This initializer is only executed once.
  ++s_value;
  std::cout << s_value << '\n';
} // s_value is not destroyed here, but becomes inaccessible because it goes out of scope

int main()
{
  incrementAndPrint();
  incrementAndPrint();
  incrementAndPrint();

  return 0;
}