/*
Header guards are used to prevent including one header multiple times in the same .cpp file. In case there are
definitions in the .h file it will cause compile error (ODR #1 violation).

It's recommended to always have header guards. Modern compilers support `#pragma once` directive that acts like a guard
(except it won't help if there are two identical .h files included) - note that it's not necessarily supported by all
implementions (it's not defined in C++ standard).

It's OK to have .h file included into single .cpp multiple times (e.g. transitively)

If .h file contains definitions there may be a linking error if .h is included into multiple .cpp files (ODR #2
violation). So if possible it's better not to put definitions in .h. But sometimes you want to do this, for example when
defining types (types exempt from ODR #2 rule).
*/
#ifndef ADD_H
#define ADD_H

int add(int x, int y);

#endif
