#ifndef PI_H
#define PI_H

/*
When compilers weren't good at understanding what functions could be inlined, inline keyword was used as a hint. Now
compilers are better at analyzing code and usually ignore this hint.

But inline also tells the linker to allow violation of the ODR #2 rule. The reason ODR violation is allowed is because
compiler must see the full definition of the function as part of a translation unit in order to inline the function.
Functions from other translation units are not visible to the compiler.

It's expected that inline functions are defined identically everywhere. Otherwise undefined behavior will occur. That's
why they are usually placed in headers - so we don't have to define them in every cpp file where they're used. The
linker will then deduplicate multiple definitions.

The following functions are implicitly inline:
- Functions defined inside a class, struct, or union type definition
- Constexpr / consteval functions
- Functions implicitly instantiated from function templates
*/

inline double pi() { return 3.14159; }

/*
There 3 ways to make variables inline:
1. Define all variables constexpr and place them in a header file. Then include that file where needed.
pros:
- can be used in constant expressions in any translations unit that includes them.
cons:
- changing the header requires recompilations of all cpp that includes the header;
- each TU gets a copy of variables (constexpr variables have internal linkage). If they can't be optimized away and
they are large, they can take up lots of memory.

2. Place definitions in cpp file (mark constexpr) and declarations in h file (mark const). You can't make declarations
constexpr because constexpr must be initialized.
pros:
- only one copy of each variable is required;
- only one cpp must file must be recompiled.
cons:
- definitions and declarations must be kept in sync;
- variables can't be used in constant expressions because when header file is included those variables are seen to
the compiler as runtime const, not constexpr.

3. (preferable, C++17) place definitions in .h file and make them inline constexpr
pros:
- they can be used in constant expressions;
- only one copy is required (linker will deduplicate definitions).
cons:
- every TU that includes them must be recompiled.

The following variables are implicitly inline:
Static constexpr data members (constexpr variables are not inline by default!).

Inline variables have external linkage by default.
Non-inline constexpr variables have internal linkage.

Constexpr functions are implicitly inline, but constexpr variables are not implicitly inline.
*/

// define your own namespace to hold constants
namespace constants {
  inline constexpr double pi{ 3.14159 };
  inline constexpr double avogadro{ 6.0221413e23 };
  inline constexpr double myGravity{ 9.2 }; // m/s^2 -- gravity is light on this planet
  // ... other related constants
} // namespace constants

#endif
