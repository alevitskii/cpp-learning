#ifndef FRACTION_H
#define FRACTION_H

/*
Compiler must see the full definition of the program-defined type in cpp file where it's used to know the size of the
type. Type definitions are partially exempt from the one-definition rule (ODR). They can appear in multiple files (but
can't appear in the same file multiple times, header guards will help with that). All of the type definitions for a
given type must be identical, otherwise undefined behavior will result.

A program-defined type used in only one code file should be defined in that code file as close to the first point of use
as possible.
A program-defined type used in multiple code files should be defined in a header file with the same name as the
program-defined type and then #included into each code file as needed.
*/

// Define a new type named Fraction.
// This only defines what a Fraction looks like, it doesn't create one.
// Note that this is a full definition, not a forward declaration.
struct Fraction
{
  int numerator{};
  int denominator{ 1 };
};

#endif