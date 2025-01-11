/*
Macroses are usually not processed inside other preprocessor directives (at least one exception is #if/#elif)

`#include` directive includes the content of the target file

File after preprocessing (typically .cpp) is a translation unit, it's then compiled. Translation phases
https://en.cppreference.com/w/cpp/language/translation_phases

Macroses are valid from the point of definition to the end of the file (they are not visible in other files unless
included)
*/

#include <iostream>

// Function-like macros are better avoided
// Object-like macros with substitution text are better avoided
#define MY_NAME "Alex"
// Object-like macros without substitution is OK to use
#define PRINT_JOE

int main()
{
  std::cout << "My name is: " << MY_NAME << '\n';

// also "if defined(PRINT_JOE)"
#ifdef PRINT_JOE
  std::cout << "Joe\n"; // will be compiled since PRINT_JOE is defined
#endif

// also "if !defined(PRINT_JOE)"
#ifndef PRINT_JOE
  std::cout << "Bob\n"; // will be excluded since PRINT_BOB is not defined
#endif

// if 0 can be used for commenting out code with multiline comments inside (nested /**/ are not allowed)
#if 0 // Don't compile anything starting here
    std::cout << "Bob\n";
    /* Some
     * multi-line
     * comment here
     */
    std::cout << "Steve\n";
#endif // until this point

  return 0;
}
