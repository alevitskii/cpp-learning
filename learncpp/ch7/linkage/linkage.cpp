/*
An identifier's linkage determines whether other declarations of that name refer to the same object or not

Local variables have no linkage. Global variables can have internal (internal variables) and external linkage

Identifiers with internal linkage may not be visible to the linker at all. Alternatively, they may be visible to the
linker, but marked for use in a specific translation unit only.
*/

// Non-constant globals have external linkage by default, but can be given internal linkage via the `static` keyword
static int g_x{};
// static keyword is a storage class specifier, it determines both the name's linkage and its storage duration
// C++ supports 4 active storage class specifiers: static, extern, mutable and thread_local

const int g_y{ 1 }; // const globals have internal linkage by default
constexpr int g_z{ 2 }; // constexpr globals have internal linkage by default
// Consts are internally linked because we often want to include consts in headers and include them in multiple files.
// If consts had external linkage this would violate ODR #2 (an object or function can only have one definition).
// In C++17 inline variables were introduced, they can have external linkage and not violate ODR.

// This function is declared as static, and can now be used only within this file.
// Attempts to access it from another file via a function forward declaration will fail during linking.
[[maybe_unused]] static int add(int x, int y) { return x + y; }

/*
Nowadays unnamed namespaces are suited better for giving objects internal linkage, and they can also be used for a
wider range of identifiers

Non-const global variables should be used as little as possible.

There are 2 phases of static variables init:
1. Static initialization - global variables initialized to constexpr values (including zero-init)
2. Dynamic initialization - global variables with non-constexpr initializers are initialized

Within a single file, for each phase, global variables are generally initialized in order of definition (there are a few
exceptions), make sure you don't have init of one global variable be dependent of the other.
The order in which static objects are initialized across different translation units is ambiguous (this is called
"static initialization order fiasco")
*/