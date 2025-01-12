#ifndef MAX_H
#define MAX_H

// Templates should be placed in header files and included.
// Templates don't violate ODR (the ODR says that types, templates, inline functions, and inline variables are allowed
// to have identical definitions in different files).
// Instantiated functions are implicitly inline so there is no problem with ODR too.
template<typename T> T max(T x, T y) { return (x < y) ? y : x; }

#endif
