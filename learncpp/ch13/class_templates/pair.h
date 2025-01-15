#ifndef PAIR_H
#define PAIR_H

// Class templates are usually placed in header files and included where needed.
// Both template definitions and type definitions are exempt from the one-definition rule.

template<typename T> struct Pair
{
  T first{};
  T second{};
};

template<typename T> constexpr T max(Pair<T> p) { return (p.first < p.second ? p.second : p.first); }

#endif