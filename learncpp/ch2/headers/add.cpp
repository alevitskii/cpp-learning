/*
The order of includes should be:
1. Paired header, e.g. in add.h for add.cpp (to catch errors related to incorrect functions declarations during compile
time, e.g. return type mismatch).
2. Other files from the same project.
3. 3rd party header files.
4. std library files.

The reason for such an order is to catch compile errors in case of accidental transitive includes that result in OK
compilation on one machine but failing on others.
*/

#include "add.h"

int add(int x, int y) { return x + y; }
